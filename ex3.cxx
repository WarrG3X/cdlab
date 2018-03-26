#include <bits/stdc++.h>



std::map<int,std::string> powerset;
std::map<std::string,int> powerset2;
std::vector<char> symbols;


void findPowerSet(std::vector<int> const S, int n)
{
	int N = pow(2, n);
	for (int i = 0; i < N; i++)
    	{
		std::string str = "N";
        	for (int j = 0; j < n; j++)
        	{
           	 if (i & (1 << j)){
                	 str.push_back(S[j]);
		 }
        	}
		if(str[0]=='N' && str.size()>1)
			str.erase(0,1);
        	powerset[i]=str;
        	powerset2[str]=i;
		}
}


class State{
public:
	std::string name;
	std::string trans;

	State(std::string name){
		this->name = name;
	}

	void add_trans(std::string trans){
		this->trans = trans;
	}

};

std::string get_trans(char S, char sym){

	std::string trans;
}

int main()
{
	int n = 3;
	int N = pow(2, n);

	std::vector<int> s;
	for(char i=48;i<48+n;i++)
		s.push_back(i);
	findPowerSet(s, n);


	std::vector<State> states;

	for(int i=0;i<N;i++)
		states.push_back(State(powerset[i]));

	
	std::vector<std::string> transitions;
	transitions.push_back("0a0");
	transitions.push_back("0a1");
	transitions.push_back("0b0");
	transitions.push_back("1b2");

	std::cout<<"NFA,\n";
	for(auto t:transitions){
		std::cout<<t[0]<<" -- "<<t[1]<<" --> "<<t[2]<<"\n";
		symbols.push_back(t[1]);
	}







	



}
