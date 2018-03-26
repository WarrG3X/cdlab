#include<iostream>
#include<vector>
#include<algorithm>
#include<sstream>
#include<map>
#include<cctype>
#include<algorithm>

std::map <char,std::vector<std::string>> productions;
std::map <char,std::vector<char>> leads;
std::map <char,std::vector<char>> trails;


std::vector<std::string> Parse(std::string prod){

	std::istringstream parser(prod);
	std::string p;
	std::vector<std::string> prods;

	while(std::getline(parser, p, '/'))
    			prods.push_back(p);

	return prods;

}

bool terminal(char a){return (std::islower(a)|std::ispunct(a));}
bool non_terminal(char a){return std::isupper(a);}


void Update(std::vector<char> &vec, char a){
	if(std::find(vec.begin(),vec.end(),a)==vec.end())
		vec.push_back(a);
}


std::vector<char> Lead(char A){

	std::vector<std::string> prods = productions[A];
	std::vector<char> leads;

	for(std::string prod:prods){

		if(terminal(prod[0]))
			Update(leads,prod[0]);
		else if(non_terminal(prod[0]) && terminal(prod[1]))
			Update(leads,prod[1]);
		else if(non_terminal(prod[0]) && prod[0]!=A){
			
			std::vector<char> temp = Lead(prod[0]);
			for(char t:temp)
				Update(leads,t);
		}	



	}





	return leads;
}


std::vector<char> Trail(char A){

	std::vector<std::string> prods = productions[A];
	std::vector<char> trails;

	for(std::string prod:prods){
		int len = prod.size()-1;

		if(terminal(prod[len]))
			Update(trails,prod[len]);
		else if(non_terminal(prod[len]) && terminal(prod[len-1]))
			Update(trails,prod[len-1]);
		else if(non_terminal(prod[len]) && prod[len]!=A){
			
			std::vector<char> temp = Trail(prod[len]);
			for(char t:temp)
				Update(trails,t);
		}	



	}





	return trails;
}


int main(){


	int n;
	std::string prod;	

	/*
	std::cout<<"Enter No. of Productions - ";
	std::cin>>n;

	for(int i=0;i<n;i++){
		std::cin>>prod;
		char non_term = prod[0];
		if(i==0)
			start = non_term;
		prod.erase(0,3);
		productions[non_term] = Parse(prod);

	}
	

	*/


	n = 3;	
	productions['E'] = Parse("E+T/T");
	productions['T'] = Parse("T*F/F");
	productions['F'] = Parse("(E)/i");

	std::cout<<"Productions,\n";

	for(auto m: productions){
		std::cout<<m.first<<"->";
		for(std::string k:m.second)
			std::cout<<k<<"/";
		std::cout<<"\n";

		leads[m.first] = Lead(m.first);
		trails[m.first] = Trail(m.first);


	}

		
	std::cout<<"\n\nLeads,\n";

	for(auto m: leads){
		std::cout<<m.first<<"={";
		for(char k:m.second)
			std::cout<<k<<",";
		std::cout<<"}\n";

	}


	std::cout<<"\n\nTrails,\n";

	for(auto m: trails){
		std::cout<<m.first<<"={";
		for(char k:m.second)
			std::cout<<k<<",";
		std::cout<<"}\n";

	}

	return 0;

}

