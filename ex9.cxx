#include<iostream>
#include<vector>
#include<algorithm>
#include<sstream>
#include<map>
#include<cctype>
#include<algorithm>
#include<iomanip>

std::map <char,std::vector<std::string>> productions;
std::map <char,std::vector<char>> firsts;
std::map <char,std::vector<char>> follows;
std::vector<char> symbols;
std::vector<char> terminals;
char start;

bool terminal(char a){return (std::islower(a)|| std::ispunct(a));}
bool non_terminal(char a){return std::isupper(a);}

void Update(std::vector<char> &vec, char a){
	if(std::find(vec.begin(),vec.end(),a)==vec.end())
		vec.push_back(a);
}


std::vector<std::string> Parse(std::string prod){

	std::istringstream parser(prod);
	std::string p;
	std::vector<std::string> prods;

	while(std::getline(parser, p, '/')){
    			prods.push_back(p);
                    for(char c:p){
                        if(terminal(c) && c!='e')
                            Update(terminals,c);
                    }
	}

	return prods;

}

std::map<char,std::string> default_map(){

    std::map<char,std::string> ret;

    for(char c:symbols)
        ret[c] = "";

    return ret;


}






std::vector<char> First(char A){

	std::vector<std::string> prods = productions[A];
	std::vector<char> first;

	bool eps = false; //Whether to add epsilon

	for(std::string p: prods){
		int pc = 0;

		while(true){
			if (!isalpha(p[pc])){
				eps = true;
				break;
			}
			if(terminal(p[pc])){
				first.push_back(p[pc]);
				break;
			}
			else{

				bool repeat = false;
				std::vector<char> temp = First(p[pc]);
				for(char t:temp){
					if(t!='e')
						Update(first,t);
					else
						repeat = true;

				}

				if(repeat)
					pc +=1;
				else
					break;

			}


		}

	}

	if(eps)
	first.push_back('e');

	return first;

}


std::vector<char> Follow(char A){

	std::vector<char> follow;

	if(A==start)
		Update(follow,'$');


	for(char S:symbols){

		std::vector<std::string> prods = productions[S];
		for(std::string prod: prods){
			auto pos = std::find(prod.begin(),prod.end(),A);
			if(pos==prod.end())
				continue;

			while(true){
				pos++;
				bool repeat = false;

				if(terminal(*pos)){
					Update(follow,*pos);
					break;
				}
				else if(non_terminal(*pos)){
					std::vector<char> temp = First(*pos);
					for(char t:temp){
						if(t!='e')
							Update(follow,t);
						else
							repeat = true;
					}

				}

				else{
					std::vector<char> temp = Follow(S);
					for(char t:temp)
						Update(follow,t);

					repeat = false;



				}

				if(!repeat)
					break;



			}

		}

	}


	return follow;

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

	/*
	n = 3;
	start = 'S';
	productions['S'] = Parse("Bb/Cd");
	productions['B'] = Parse("aB/e");
	productions['C'] = Parse("cC/e");
	*/

	/*
	start = 'S';
	productions['S'] = Parse("ABCDF");
	productions['A'] = Parse("a/e");
	productions['B'] = Parse("b/e");
	productions['C'] = Parse("c");
	productions['D'] = Parse("d/e");
	productions['F'] = Parse("f/e");

	start = 'S';
	productions['S'] = Parse("ACB/CbB/Ba");
	productions['A'] = Parse("da/BC");
	productions['B'] = Parse("g/e");
	productions['C'] = Parse("h/e");
	*/


    start = 'S';
	productions['S'] = Parse("ACB/CbB/Ba");
	productions['A'] = Parse("da/BC");
	productions['B'] = Parse("g/e");
	productions['C'] = Parse("h/e");


	std::cout<<"Productions,\n";

	for(auto m: productions){
		std::cout<<m.first<<"->";
		Update(symbols,m.first);
		for(std::string k:m.second)
			std::cout<<k<<"/";
		std::cout<<"\n";

		firsts[m.first] = First(m.first);

	}

	std::cout<<"\n\nFirsts,\n";

	for(auto m: firsts){
		std::cout<<m.first<<"={";
		for(char k:m.second)
			std::cout<<k<<",";
		std::cout<<"}\n";

	}

	follows[start] = Follow(start);

	for(auto m: productions){
		follows[m.first] = Follow(m.first);

	}

	std::cout<<"\n\nFollows,\n";

	for(auto m: follows){
		std::cout<<m.first<<"={";
		for(char k:m.second)
			std::cout<<k<<",";
		std::cout<<"}\n";

	}



    std::map<char,std::map<char,std::string>> pptable;
    pptable[' '] = default_map();
    for(char s:symbols)
        pptable[s] = default_map();


    std::cout<<"\n\nProductions,\n";

	for(auto m: productions){
		for(std::string k:m.second){
			std::cout<<m.first<<"->"<<k<<"\n";
			std::vector<char> fs = First(k[0]);
			bool eps = false;
			for(char f:fs){
                if(f=='e'){
                    eps = true;
                    continue;}
			    std::string emb = "->" ;
                emb.insert(0,1,m.first);
                emb = emb+k;
                pptable[m.first][f] = emb;
			}
			if(eps){
                std::vector<char> fs = Follow(m.first);
                for(char f:fs){
                    std::string emb = "->" ;
                    emb.insert(0,1,m.first);
                    emb = emb+k;
                    pptable[m.first][f] = emb;
                }

			}
		}

	}



	std::cout<<"\n\nPredictive Parse Table,\n\n";
	std::cout<< std::setw(10) << std::left << " ";
    for(char t: terminals)
		std::cout<< std::setw(10) <<std::right <<t;

    std::cout << "\n\n";
	for(char s:symbols){
        std::cout<< std::setw(10) << std::left << s;
        for(char t:terminals)
            std::cout<< std::setw(10) << std::right << pptable[s][t];
        std::cout << "\n\n";
	}


	return 0;
}

