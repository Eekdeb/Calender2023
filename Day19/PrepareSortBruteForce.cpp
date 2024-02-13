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

void adv_tokenizer(string s, char del,vector<rule>& output);
void getRuleLine(fstream& input, map<string,vector<rule>>& output);
rule createRule(string des);

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

void getToolLine(fstream& input, map<char,int>& output){
    output.clear();
    string buff;
    string one;
    getline(input,buff); 
    stringstream ss(buff);
    while (!ss.eof()) {
        getline(ss, one, ',');
        if(one[0] == '{'){
            output.insert({one[1],stoi(one.substr(3,one.back()))});
        }else if(one[one.length()-1] == '}'){
             output.insert({one[0],stoi(one.substr(2,one[one.length()-1]))});;
        } else{
             output.insert({one[0],stoi(one.substr(2,one.back()))});
        }
    }
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

void nextPart(map<char,int>& part){
    //x m a s
    part['x']++;
    if(part['x'] == 4000){
        part['x'] = 0;
        part['m']++;
        cout << part['m'] << endl;
    }
    if(part['m'] == 4000){
        part['m'] = 0;
        part['a']++;
        cout << part['a'] << endl;
    }
    if(part['a'] == 4000){
        part['a'] = 0;
        part['s']++;
        cout << part['s'] << endl;
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

    string id = "in";
    long long aCount = 0, rCount = 0;
    while(part['s'] <= 4000){
        id = "in";
        nextPart(part);
        while(id != "A" && id != "R"){
            id = nextId(id,part,idRules);
        }
        if(id == "A"){
            aCount++;
        } 
        else rCount++;
    }
    cout << "A: " << aCount << " R: " << rCount << endl;

    input.close();
}