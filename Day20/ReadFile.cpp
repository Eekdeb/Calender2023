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
        std::vector<std::string> receiving;
        Module(std::string thisId, std::vector<std::string> sendTo) {     // Constructor
            id = thisId;
            for (auto st : sendTo)
            {
                 subs.push_back(st);
            }           
        }
        virtual void send(packet,std::vector<packet>&) =0;
        
        void addReceiver(std::string resId){
            receiving.push_back(resId);
        }

        virtual std::string toString(){
            std::string str = id;
            str += " senders {";
            for (auto s : subs)
            {
                str += s;
                str += " ";
            }
            str += "} R:{";
            for (auto s : receiving)
            {
                str += s;
                str += " ";
            }
            str += "}";
            return str;
        };
};

class SingleLow: public Module{
    private:
        
    public:
        bool lowPacket = false;
        //int nrOfReceivedPackets = 1;
        SingleLow(std::string thisId, std::vector<std::string> ids):Module(thisId,ids){};
        void resetButton(){
            lowPacket = false;
            //nrOfReceivedPackets = 0;
        }
        void send(packet received,std::vector<packet>& sending){
            //nrOfReceivedPackets++;
            if(received.pulse == 0){
                lowPacket = true;
            }
        };
        bool oneLowPulse(){
            return lowPacket;
            //if(nrOfReceivedPackets == 1 && lowPacket){
            //    return true;
            //}
            //return false;
        }
        std::string toString(){
           
            std::string str =  Module::toString();
            //str += std::to_string(nrOfReceivedPackets);
            return str;
        }
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
    
    std::shared_ptr<SingleLow> low = std::make_shared<SingleLow>("rx",std::vector<std::string>());
    idToModule["rx"] = low;

    for (auto m : idToModule) //for all modules
    {
        for (auto sub : m.second->subs) //For all subs on each module
        {
            idToModule[sub]->addReceiver(m.first);
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

    
    long long counter = 0;
    while (true)
    {
        counter++;
        pushButton(queue);
        while (!queue.empty())
        {
            //printPacket(queue[0]);
            if(queue[0].sender == "vn"){
                if(queue[0].pulse == 1){
                    printPacket(queue[0]);
                    std::cout << counter << std::endl;
                }
                
            }
            if(idToModule[queue[0].receiver].use_count() != 0)
                idToModule[queue[0].receiver]->send(queue[0],queue);
            queue.erase(queue.begin(),queue.begin()+1);
        }
        auto singPtr = std::dynamic_pointer_cast<SingleLow>(idToModule["rx"]);
        if(singPtr->oneLowPulse()){
            std::cout << counter;
            break;
        }
    }
}

/**
 * Manually found the the right answer.
 * First got the graph that made it clear that there where 4 different groups
 *  that all ended on one Conjunction each. There merge paths where (ph,kt,vn,hn).
 *  When all of them are sending 1 the "rx" module is getting 0 therefor complete.
 *  They all had a period that made them 1. (listed below)
 * ph sends 1 every 3907 (prime)
 * kt 4093 (prime)
 * vn 3797 prime
 * hn 4021 prime
 *  To get the least number of times pressing the button is multiplying them
 *  together becaus all of them are prime
 *  Finale result is 244 151 741 342 687
 * ________________________________________
 * 
 * How to make this automatically.
 * Begin from the final module "rx" take a step back to the previous modules.
 * Remember what this module needs for value and run the machine for 2s or something.
 * If you can find a consistant loop remember it else go back one more step.
 * Do so until all modules connected to rx has a loop. then find the lowest common nominate
 * and you got the answer.
 * 
*/