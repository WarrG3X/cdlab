#include <bits/stdc++.h>



std::map<int,std::string> powerset;
std::map<std::string,int> powerset2;
std::vector<char> symbols;

void Update(std::vector<char> &vec, char a){
	if(std::find(vec.begin(),vec.end(),a)==vec.end())
		vec.push_back(a);
}

std::vector<std::string> Parse(std::string prod){

	std::istringstream parser(prod);
	std::string p;
	std::vector<std::string> prods;

	while(std::getline(parser, p, '/'))
    			prods.push_back(p);

	return prods;

}


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
		trans = "";
	}

	void add_trans(std::string trans){
		this->trans += trans;
	}

};

std::string get_trans(std::string S, char sym,std::vector<std::string> transition){

	std::string trans = "";
	for(char s:S){
		for(std::string t: transition){
			if (t[0]==s && t[1]==sym)
				trans.push_back(t[2]);
		}
	}


	//std::cout<<S<<">"<<sym<<"> "<<trans<<"\n";
	if(trans=="")
		return "0/";
	else
		return std::to_string(powerset2[trans])+"/";


}

int main()
{
	int n = 3;
	int N = pow(2, n);
	int start = 1;

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
		Update(symbols,t[1]);
	}


	for(char sym:symbols){

		for(State &st:states){
			
			st.add_trans(get_trans(st.name,sym,transitions));

		}
	}



	std::cout<<"\n\nIntermediate Form from Subset Construction,\n";
	for(int i=0;i<N;i++)
		std::cout<<i<<"->"<<states[i].trans<<"\n";

	std::vector<int> final;
	std::deque<int> buffer;
	buffer.push_back(start);
	while(!buffer.empty()){
		int b = buffer.front();
		buffer.pop_front();
		if(std::find(final.begin(),final.end(),b)==final.end()){
			final.push_back(b);
			std::vector<std::string> trans = Parse(states[b].trans);
			for(auto t:trans){
				buffer.push_back(std::stoi(t));
			}
		}
	}

	std::cout<<"\n\nFinal DFA,\n";

	for(auto i:final){
		for(int j=0;j<symbols.size();j++){
			std::vector<std::string> trans = Parse(states[i].trans);
			std::cout<<i<<" -- "<<symbols[j]<<" --> "<<trans[j]<<"\n";
		}
	}


return 0;

}
