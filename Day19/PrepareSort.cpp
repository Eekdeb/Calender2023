#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

struct rule
{
    char variable;
    char operation;
    int value;
    string id;
};

struct maxMin
{
    int xMax = 4000,xMin = 1;
    int mMax = 4000,mMin = 1;
    int aMax = 4000,aMin = 1;
    int sMax = 4000,sMin = 1;
    string id;
};

void adv_tokenizer(string s, char del,vector<rule>& output);
void getRuleLine(fstream& input, map<string,vector<rule>>& output);
rule createRule(string des);

void printMaxMin(maxMin p){
    cout << "x: " << p.xMax << " " << p.xMin << " m: " << p.mMax << " " << p.mMin << " a: " << p.aMax << " " << p.aMin << " s: " << p.sMax << " " << p.sMin << " id: " << p.id << endl;

}

void printRule(rule r){
    cout << r.variable << " " << r.operation << " " << r.value << " : " << r.id << endl;
}

void getRuleLine(fstream& input, map<string,vector<rule>>& output){
    string id, buff;
    vector<rule> rules;
    getline(input,id,'{'); //get id
    getline(input,buff); //get the rest of the line
    adv_tokenizer(buff,',',rules); //convert it to a vector of rules
    output.insert({id,rules}); // add it to the map
}

rule createRule(string des){
    int index = 2;
    for (index; index < des.length(); index++)
    {
        if(des[index] == ':')
            break;
    }
    rule newRule;
    newRule.variable = des[0];
    newRule.operation = des[1];
    newRule.value = stoi(des.substr(2,index));
    newRule.id = des.substr(index+1,des.back());
    //printRule(newRule);
    return newRule;
}

void adv_tokenizer(string s, char del,vector<rule>& output){
    stringstream ss(s);
    string word;
    
    while (!ss.eof()) {
        getline(ss, word, del);
        if(word.back() != '}'){
            output.push_back(createRule(word));
        }else{
            output.push_back({' ','T',0,word.substr(0,word.length()-1)});
        }
    }
}

bool ifCharStatement(int part, int rule, char operation){
    if(operation == '>'){
        return part > rule;
    }
    if(operation == '<'){
        return part < rule;
    }
    return true;
}

string nextId(string id, map<char,int> part, map<string,vector<rule>> rules){
    //for each rule with id
    for (auto r : rules[id])
    {
        if(ifCharStatement(part[r.variable],r.value,r.operation)){
            return r.id;
        }
    }
    return "Not gud";
}

void findNextEdge(maxMin edge, map<string,vector<rule>> idRules, vector<maxMin>& edges){
    maxMin ruleFalse = edge,ruleTrue; 
    for (auto r : idRules[edge.id])
    {
        ruleTrue = ruleFalse;
        ruleTrue.id = r.id;
        //x>200
        if(r.operation == '>'){
            switch (r.variable)
            {
            case 'x':
                if(ruleTrue.xMin < r.value+1){
                    ruleTrue.xMin = r.value+1;
                    ruleFalse.xMax = r.value;
                }
                break;
            case 'm':
                if(ruleTrue.mMin < r.value+1){
                    ruleTrue.mMin = r.value+1;
                    ruleFalse.mMax = r.value;
                }
                break;
            case 'a':
                if(ruleTrue.aMin < r.value+1){
                    ruleTrue.aMin = r.value+1;
                    ruleFalse.aMax = r.value;
                }
                break;
            case 's':
                if(ruleTrue.sMin < r.value+1){
                    ruleTrue.sMin = r.value+1;
                    ruleFalse.sMax = r.value;
                }
                break;         
            default:
                break;
            }
        }
        if(r.operation == '<'){
            //x<200
            switch (r.variable)
            {
            case 'x':
                if(ruleTrue.xMax > r.value-1){
                    ruleTrue.xMax = r.value-1;
                    ruleFalse.xMin = r.value;
                }
                break;
            case 'm':
                if(ruleTrue.mMax > r.value-1){
                    ruleTrue.mMax = r.value-1;
                    ruleFalse.mMin = r.value;
                }
                break;
            case 'a':
                if(ruleTrue.aMax > r.value-1){
                    ruleTrue.aMax = r.value-1;
                    ruleFalse.aMin = r.value;
                }
                break;
            case 's':
                if(ruleTrue.sMax > r.value-1){
                    ruleTrue.sMax = r.value-1;
                    ruleFalse.sMin = r.value;
                }
                break;         
            default:
                break;
            }
        }
        if(r.operation == 'T'){
            ruleFalse.id = r.id;
            edges.push_back(ruleFalse);
        }
        else{
            edges.push_back(ruleTrue);
        }
    }
}

int main(){
    //general rule
    //zrc{m>2535:A,x<2119:xnp,x>2452:sxk,bq}
    //id{condition:id,condition:id,id}
    //save as map<string,vector<condition>>
    
    fstream input("input.txt");
    
    map<string,vector<rule>> idRules;
    map<char,int> part;
    part.insert({'x',0});
    part.insert({'m',0});
    part.insert({'a',0});
    part.insert({'s',0});
    while (input.peek() != '\n'){
        getRuleLine(input,idRules);
    }

    
    maxMin start,last;
    start.id = "in";
    vector<maxMin> edges,done;


    
    findNextEdge(start,idRules,edges);
    
    while(!edges.empty()){
        start = edges.back();
        edges.pop_back();
        if(start.id == "R" || start.id == "A"){
            done.push_back(start);
        }else{
            findNextEdge(start,idRules,edges);
        }
    }
    
    //RISK 0 is a problem
    long long combo = 0, comboR = 0;
    for (auto e : done)
    {
        //printMaxMin(e);
        if(e.id == "A"){
            combo += long((e.xMax-e.xMin+1))*long((e.mMax-e.mMin+1))*long((e.aMax-e.aMin+1))*long((e.sMax-e.sMin+1));
        }
        if(e.id == "R"){
            comboR += long((e.xMax-e.xMin+1))*long((e.mMax-e.mMin+1))*long((e.aMax-e.aMin+1))*long((e.sMax-e.sMin+1));
        }
    }
    cout << "Accepted: "<< combo << " Rejected: " << comboR << " Total: " << combo+comboR<< endl;

    input.close();
}