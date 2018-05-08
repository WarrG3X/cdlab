#include<iostream>
#include<vector>
#include<algorithm>
#include<sstream>


int main(){

	std::string prod;	
	//std::cout<<"Enter Production - ";
	//std::cin>>prod;
	//prod = "A->ABc/Aa/a";
	prod = "A->AC/Aad/bd/c";
	std::vector<std::string> v= {"sdds","dsgsd"};
	
	char non_term = prod[0];
	prod.erase(0,3);

	std::istringstream parser(prod);
	std::string p;
	std::vector<std::string> prods;
	std::vector<std::string> alphas;
	std::vector<std::string> betas;

	while(std::getline(parser, p, '/')){
		
		if(p[0]==non_term)
    			alphas.push_back(p.substr(1,p.size()));
		else
			betas.push_back(p);

	}

	std::cout<<"Removing Left Recursions,\n";
	std::cout<<non_term<<"->";
	
	int b = betas.size();
	for(int i=0;i<b-1;i++)
		std::cout<<betas[i]<<non_term<<"'"<<"/";


	std::cout<<betas[b-1]<<non_term<<"'"<<"\n";


	std::cout<<non_term<<"'->";
	
	int a = alphas.size();
	for(int i=0;i<a-1;i++)
		std::cout<<alphas[i]<<non_term<<"'"<<"/";


	std::cout<<alphas[a-1]<<non_term<<"'"<<"/\u03B5\n";


	return 0;

}

