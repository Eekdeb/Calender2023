#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

#include <memory>
#include <type_traits>


struct packet
{
    std::string sender;
    std::string receiver;
    bool pulse;
};


class Module{
    protected:
        std::string id;
        
    public:
        std::vector<std::string> subs;

        Module(std::string thisId, std::vector<std::string> sendTo) {     // Constructor
            id = thisId;
            for (auto st : sendTo)
            {
                 subs.push_back(st);
            }           
        }
        virtual void send(packet,std::vector<packet>&) =0;
        virtual std::string toString(){
            std::string str = id;
            str += " senders {";
            for (auto s : subs)
            {
                str += s;
                str += " ";
            }
            str += "}";
            return str;
        };
};

class Broadcaster: public Module{
    public:
        Broadcaster(std::string thisId, std::vector<std::string> ids):Module(thisId,ids){};
        void send(packet received,std::vector<packet>& queue){
            for (auto s : subs)
            {
                queue.push_back({id,s,0});
            }
        }
};

/*
Flip-flop modules (prefix %) are either on or off; they are initially off.
If a flip-flop module receives a high pulse, it is ignored and nothing happens.
However, if a flip-flop module receives a low pulse, it flips between 
on and off. If it was off, it turns on and sends a high pulse. If it was on,
it turns off and sends a low pulse.
*/
class FlipFlop: public Module{
    private:
        bool state = 0;
    public:
        FlipFlop(std::string thisId,std::vector<std::string> ids) : Module(thisId,ids){
            
        }
        void send(packet received, std::vector<packet>& queue){
            if(received.pulse == 0){
                state = state==0 ? 1:0;
                for (std::string s : subs)
                {
                    queue.push_back({id,s,state});
                }
            }
        }
};
/*
Conjunction modules (prefix &) remember the type of the most recent pulse received 
from each of their connected input modules; they initially default to remembering a 
low pulse for each input. When a pulse is received, the conjunction module first 
updates its memory for that input. Then, if it remembers high pulses for all inputs, 
it sends a low pulse; otherwise, it sends a high pulse.*/

class Conjunction: public Module{
    private:
        std::map<std::string,bool> memory;
    public:
        Conjunction(std::string thisId, std::vector<std::string> ids) :Module(thisId,ids){

        }
        void send(packet received, std::vector<packet>& queue){
            memory[received.sender] = received.pulse;
            bool all1 = true;
            for (auto p : memory)
            {
                if(p.second == 0){
                    all1 = false;
                    break;
                }
            }
            if(all1){
                for (auto s : subs)
                {
                    queue.push_back({id,s,0});
                }
            } else{
                for (auto s : subs)
                {
                    queue.push_back({id,s,1});
                }
            }
        }
        void addReceiver(std::string id){
            memory[id] = 0;
        }
        std::string toString(){
            std::string str = Module::toString();
            str += " Receives from {";
            for (auto i : memory)
            {
                str += i.first + " ";
            }
            str += "}";
            return str;
        }
};

void printPacket(packet p){
    std::cout << p.sender << " -" << p.pulse << "> " << p.receiver << std::endl;
}

void pushButton(std::vector<packet>& queue){
    queue.push_back({"Button","roadcaster",0});
}

void getLineModule(std::fstream& input,std::map<std::string,std::shared_ptr<Module>>& idToModule, std::vector<std::string>& conIds){
    char type;
    std::string buff,id;
    std::vector<std::string> receivers;
    std::stringstream ss;

    input >> buff;
    type = buff[0];
    id = buff.substr(1,buff.length());
    //remove a thing 
    input >> buff;

    std::getline(input,buff); //gers id1, id2, id3
    ss = std::stringstream(buff);
    while (!ss.eof())
    {
        std::getline(ss,buff,','); //gets  id1
        receivers.push_back(buff.substr(1,buff.length()));
    }

    if(type == '%'){
        std::shared_ptr<FlipFlop> flip = std::make_shared<FlipFlop>(id,receivers);
        idToModule[id] = flip;
    }
    if(type == 'b'){
        std::shared_ptr<Broadcaster> bro = std::make_shared<Broadcaster>(id,receivers);
        idToModule[id] = bro;
    }
    if(type == '&'){
        std::shared_ptr<Conjunction> con = std::make_shared<Conjunction>(id,receivers);
        idToModule[id] = con;
        conIds.push_back(id);
    }
}

int main(){
    std::fstream input("input.txt");
    std::map<std::string,std::shared_ptr<Module>> idToModule;
    std::vector<std::string> allConIds;
    std::vector<packet> queue;
    while (!input.eof())
    {
        getLineModule(input,idToModule,allConIds);
    }

    for (auto m : idToModule) //for all modules
    {
        for (auto sub : m.second->subs) //For all subs on each module
        {
            for (auto conId : allConIds) //check if a con is a reciver to that module
            {
                if(conId == sub){
                    if (auto conPtr = std::dynamic_pointer_cast<Conjunction>(idToModule[conId])) {
                        conPtr->addReceiver(m.first);
                    }
                }
            }
            
        }
        
    }
    
    int highPulses = 0, lowPulses = 0;
    for (int i = 0; i < 1000; i++)
    {
        pushButton(queue);
        while (!queue.empty())
        {
            //printPacket(queue[0]);
            if(idToModule[queue[0].receiver].use_count() != 0)
                idToModule[queue[0].receiver]->send(queue[0],queue);
            if(queue[0].pulse == 0){
                lowPulses++;
            }else
                highPulses++;
            queue.erase(queue.begin(),queue.begin()+1);
        }
        std::cout << i << " " << lowPulses << " " << highPulses << std::endl;
    }
    std::cout << highPulses*lowPulses << std::endl;
}