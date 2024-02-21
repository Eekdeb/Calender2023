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
        std::vector<std::string> subs;
    public:
        Module(std::string thisId, std::vector<std::string> sendTo) {     // Constructor
            id = thisId;
            for (auto st : sendTo)
            {
                 subs.push_back(st);
            }           
        }
        
        virtual void send(packet,std::vector<packet>&) =0;
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
        Conjunction(std::string thisId, std::vector<std::string> ids, std::vector<std::string> reivers) :Module(thisId,ids){
            for (auto r : reivers)
            {
                memory[r] = 0;
            }
            
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

};

void printPacket(packet p){
    std::cout << "S: " << p.sender << " P:" << p.pulse << " R:" << p.receiver << std::endl;
}

void pushButton(std::vector<packet>& queue){
    queue.push_back({"broadcaster",0});
}

int main(){
    std::vector<packet> queue; //The queue with packets that are sent
    std::map<std::string,std::shared_ptr<Module>> idToModule; //all Modules

    std::vector<std::string> receivers;
    std::vector<std::string> senders;
    receivers.push_back("Eek");
    receivers.push_back("Dap");
    receivers.push_back("Tim");
    std::shared_ptr<Broadcaster> bro = std::make_shared<Broadcaster>("broadcaster",receivers);
    idToModule["broadcaster"] = bro;
    
    receivers.clear();
    receivers.push_back("Dap");
    std::shared_ptr<FlipFlop> flip = std::make_shared<FlipFlop>("Eek",receivers);
    idToModule["Eek"] = flip;
    
    receivers.clear();
    receivers.push_back("Tim");
    flip = std::make_shared<FlipFlop>("Dap",receivers);
    idToModule["Dap"] = flip;

    receivers.clear();
    receivers.push_back("Wout");
    flip = std::make_shared<FlipFlop>("Tim",receivers);
    idToModule["Tim"] = flip;

    receivers.clear();
    receivers.push_back("Eek");
    senders.push_back("Tim");
    std::shared_ptr<Conjunction> con = std::make_shared<Conjunction>("Wout",receivers,senders);
    idToModule["Wout"] = con;

    idToModule["broadcaster"]->send({"","",0},queue);
    while (!queue.empty())
    {
        idToModule[queue[0].receiver]->send(queue[0],queue);
        printPacket(queue[0]);
        queue.erase(queue.begin(),queue.begin()+1);
    }
}