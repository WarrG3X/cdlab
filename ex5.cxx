#include<iostream>
#include<vector>
#include<algorithm>
#include<sstream>


std::string prefixFinder(std::vector<std::string> prods){

	if(prods.size()==0)
		return "";

	if(prods.size()==1)
		return prods[0];


	int min = prods[0].size();

	for(int i=1;i<prods.size();i++){

		if(prods[i].size() < min)
			min = prods[i].size();
	}


	for(int i=0;i<min;i++){

		for(int j=1; j<prods.size();j++){

			if(prods[j][i]!=prods[j-1][i])
				return prods[0].substr(0,i);
		}
	}


	return prods[0].substr(0,min);


}





int main(){

	std::string prod;
	
	//std::cout<<"Enter Production - ";
	//std::cin>>prod;
	//prod = "A->bcd/bcf";
	prod = "A->abbb/abc/abac";
	
	char non_term = prod[0];
	prod.erase(0,3);

	std::istringstream parser(prod);
	std::string p;
	std::vector<std::string> prods;

	while(std::getline(parser, p, '/'))
    		prods.push_back(p);

	p = prefixFinder(prods);

	std::cout<<"Removing Left Factoring,\n";
	std::cout<<non_term<<"->"<<p<<"X\n";
	std::cout<<"X->";

	int len = p.size();
	std::string s;

	for(int i=0;i<prods.size()-1;i++){
		s = prods[i];
		int q = s.size();
		std::cout<<s.substr(len,q)<<"/";
	}

	std::cout<<prods[prods.size()-1].substr(len,prods.size())<<"\n";
	return 0;

}

