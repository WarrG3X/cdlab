#include<iostream>
#include<string>
#include<sstream>
#include<map>
#include<stack>
#include<queue>
#include<vector>
#include<ctype.h>



class State{
public:
    int id;
    bool accepting;
    std::multimap<char,State*> trans;

    State(int id){
    this->id = id;
    this->accepting = false;
    }


    std::string name(){
        std::stringstream ss;
        if(accepting)
            ss << "(s" << id << ")";
        else
            ss << "s" << id;
        return ss.str();
        }

    void add_transition(char c,State* S){

        trans.insert(std::pair<char,State*> (c,S));
    }

    void setFinal(){
        accepting = true;
    }

    void display(){

        std::multimap<char,State*>::iterator itr;

	for(std::pair<char,State*> x:trans){
            	std::cout<<name()<<" -- "<<x.first<<" --> "<<x.second->name()<<std::endl;

        }

    }

    bool operator <(State s2) const{

    return (id < s2.id);

    }

};


class Automata{
public:

    std::deque<State*> states;

    void display(){

	int i;
	for(i=0;i<states.size();i++)
		states[i] -> display();

    }

};


class RegexParser{
public:

    std::string regx;
    std::stack<Automata> fastack;
    std::stack<char> opstack;
    int statecount;


    RegexParser(std::string regx){
    this->regx = Preprocess(regx);
    statecount = 0;
    }

    void stateupdate()
    {
        statecount += 1;
    }

    std::string Preprocess(std::string regx){

        std::vector<char> v;
        int n = regx.length();
        int key;


        for(int i=0;i<n-1;i++){
                v.push_back(regx[i]);
                key = 10*OpKey(regx[i])+OpKey(regx[i+1]);
                if(concatUpdate(key))
                    v.push_back('`');


        }
        v.push_back(regx[n-1]);
        std::string processed(v.begin(),v.end());
        return processed;


}

    int OpKey(char s){

        char oplist[4]=  {'*','|','(',')'};
        for(int i=0;i<4;i++){
                if(oplist[i]==s)
                return i+1;
        }

        return 0;
    }

    bool concatUpdate(int key){
        int cases[6] = {0,3,40,10,13,43};

        for(int c:cases){
                if(c==key)
                return true;
        }

        return false;
    }

    bool Precedence(char a,char b){
        std::map<char,int> prec = {{'(',4},{')',4},{'*',3},{'`',2},{'|',1}};

        if (prec[a] < prec[b])
            return true;

        return false;
    }


void parse(){


    for(int i=0;i<regx.size();i++){

        char r = regx[i];

        if(isalnum(r))
            push(r);
        else if(r=='(')
            opstack.push(r);

        else if(opstack.empty())
            opstack.push(r);
        else if(r==')'){
            while(opstack.top()!='(')
                    evaluate_stack(opstack.top());
            opstack.pop(); //Remove remaining Left Para
        }

        else{

            while(!opstack.empty() && Precedence(r,opstack.top()))
                evaluate_stack(opstack.top());

            opstack.push(r);

        }



    }

    while(!opstack.empty())
        evaluate_stack(opstack.top());



}

void disp(){

        	Automata a = fastack.top();
            a.states[a.states.size()-1]->setFinal();
            a.display();
        	fastack.pop();
	}



void push(char r){

    State *s0 = new State(statecount++);
    State *s1 = new State(statecount++);

    Automata FA;


    s0->add_transition(r,s1);

    FA.states.push_back(s0);
    FA.states.push_back(s1);


    fastack.push(FA);
}

bool concat(){

Automata a,b;
if (fastack.empty())
    return false;

b = fastack.top(); fastack.pop();

if (fastack.empty())
    return false;

a = fastack.top(); fastack.pop();


a.states[a.states.size()-1]->add_transition('e',b.states[0]);
a.states.insert(a.states.end(),b.states.begin(),b.states.end());

fastack.push(a);

return true;

}

bool alternation(){

Automata a,b;
if (fastack.empty())
    return false;

b = fastack.top(); fastack.pop();

if (fastack.empty())
    return false;

a = fastack.top(); fastack.pop();


State *s0 = new State(statecount++);
State *s1 = new State(statecount++);

s0->add_transition('e',a.states[0]);
s0->add_transition('e',b.states[0]);
a.states[a.states.size()-1]->add_transition('e',s0);
b.states[b.states.size()-1]->add_transition('e',s1);

b.states.push_back(s1);
a.states.push_front(s0);

a.states.insert(a.states.end(),b.states.begin(),b.states.end());

fastack.push(a);
return true;



}

bool star(){

Automata a;
if (fastack.empty())
    return false;

a = fastack.top(); fastack.pop();


State *s0 = new State(statecount++);
State *s1 = new State(statecount++);

s0->add_transition('e',a.states[0]);
s0->add_transition('e',s1);

a.states[a.states.size()-1]->add_transition('e',a.states[0]);
a.states[a.states.size()-1]->add_transition('e',s1);



a.states.push_back(s1);
a.states.push_front(s0);

fastack.push(a);
return true;



}

void evaluate_stack(char sym){

opstack.pop();

if (sym == '`')
        {std::cout<<"`\n";
        concat();}
else if (sym == '|')
        {std::cout<<"|\n";
        alternation();}
else if (sym == '*')
        {std::cout<<"*\n";
        star();}

}

};

int main(){

std::string reg = "a*|b";
//std::string reg = "abc*|bc";
RegexParser Parser(reg);

Parser.parse();
Parser.disp();

return 0;
}

