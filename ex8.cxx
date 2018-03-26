#include<iostream>
#include<vector>
#include<algorithm>
#include<sstream>
#include<map>
#include<cctype>
#include<algorithm>
#include<stack>
#include<deque>
#include<iomanip>

std::map <char,std::vector<std::string>> productions;
std::map <std::string,char> rev_prod;
char start;




std::vector<std::string> Parse(std::string prod){

	std::istringstream parser(prod);
	std::string p;
	std::vector<std::string> prods;

	while(std::getline(parser, p, '/'))
    			prods.push_back(p);

	return prods;

}

bool terminal(char a){return std::islower(a);}
bool non_terminal(char a){return std::isupper(a);}


void Update(std::vector<char> &vec, char a){
	if(std::find(vec.begin(),vec.end(),a)==vec.end())
		vec.push_back(a);
}


class ShiftReduce{
public:
    std::deque<char> input;
    std::deque<char> stk;

    ShiftReduce(std::string inp){
        input.push_back('$');
        for(auto s:inp)
            input.push_back(s);

        stk.push_back('$');



    }

    void shift(){

    if(input.back()=='$')
        return;

    display("Shift");
    char t = input.back(); input.pop_back();
    stk.push_back(t);

    }

    void display(){
    std::string temp1 (stk.begin(),stk.end());
    std::string temp2 (input.begin(),input.end());
    std::reverse (temp2.begin(),temp2.end());
    std::cout<< std::setw(10)<< std::left << temp1;
    std::cout<< std::setw(10)<< std::right << temp2 << "\n";

    }

    void display(std::string msg){
    std::string temp1 (stk.begin(),stk.end());
    std::string temp2 (input.begin(),input.end());
    std::reverse (temp2.begin(),temp2.end());
    std::cout<< std::setw(10)<< std::left << temp1;
    std::cout<< std::setw(10)<< std::right << temp2;
    std::cout<< std::setw(10)<< std::right << msg << "\n";

    }

    void reduce(){
    std::string handle (stk.begin()+1,stk.end());


    for(int i=0;i<=handle.size();i++){
        std::string hand = handle.substr(i,handle.size());

        for(auto r:rev_prod){

            if(r.first==hand){
                display("Reduce");
                for(int j=0;j<r.first.size();j++)
                    stk.pop_back();
                    stk.push_back(r.second);
                    return;

            }
        }
    }


    }

};



int main(){


	int n;
	std::string prod;
	std::string inp;

	inp = "x*x";
	start = 'B';
	productions['B'] = Parse("B+T/T");
	productions['T'] = Parse("T*F/F");
	productions['F'] = Parse("(B)/x");

	std::cout<<"Productions,\n";

	for(auto m: productions){
		std::cout<<m.first<<"->";
		for(std::string k:m.second){
            rev_prod[k]=m.first;
			std::cout<<k<<"/";}
		std::cout<<"\n";
	}

    std::cout<<"\n\nReverse Productions,\n";

	for(auto m: rev_prod)
		std::cout<<m.first<<" -> "<<m.second<<"\n";


    std::cout<<"\n\nParser,\n\n";
    std::cout<< std::setw(10)<< std::left << "STACK";
    std::cout<< std::setw(10)<< std::right << "INPUT";
    std::cout<< std::setw(10)<< std::right << "ACTION" << "\n\n";

    ShiftReduce parser(inp);
    parser.shift();
    parser.reduce();
    parser.reduce();
    parser.shift();
    parser.shift();
    parser.reduce();
    parser.reduce();
    parser.reduce();




	return 0;

}

