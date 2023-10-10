#include <iostream>
#include <conio.h>
#include <fstream>
#include <vector>

using namespace std;

int main(){
	
	
	
	vector <string> vocabolario;
	vocabolario.clear();
	
	string line = "";
	int tutti = 0;
	int non_validi = 0;
	
	ifstream myfile ("words_italian.txt");
	if (myfile.is_open())
	    while ( myfile.good() ){
	        getline (myfile,line);
	        
	        tutti++;
	        
	        if(line == ""){ cout<<line<<endl; non_validi++; continue; }
	        if(line.find('j') != std::string::npos){ cout<<line<<endl; non_validi++; continue; }
	        if(line.find('k') != std::string::npos){ cout<<line<<endl; non_validi++; continue; }
	        if(line.find('w') != std::string::npos){ cout<<line<<endl; non_validi++; continue; }
	        if(line.find('x') != std::string::npos){ cout<<line<<endl; non_validi++; continue; }
	        if(line.find('y') != std::string::npos){ cout<<line<<endl; non_validi++; continue; }
	        if(line.size() < 3){ cout<<line<<endl; non_validi++; continue; }
	        if(line.size() > 10){ cout<<line<<endl; non_validi++; continue; }
	        
	        vocabolario.push_back(line);
		}
	myfile.close();
	
	cout<<"Tutti\t\t"<<tutti<<endl;
	cout<<"Validi\t\t"<<vocabolario.size()<<endl;
	cout<<"Non Validi\t"<<non_validi<<endl;
	
	
	{
	ofstream out("words_italian.dat", ios::trunc);
	out << "";
	out.close();
	}
	
	for(int s = 0; s < vocabolario.size(); s++){
		ofstream out("words_italian.dat", ios::app);
		out << vocabolario.at(s) << endl;
		out.close();
	}
	
	cout<<"FINE"<<endl;
	
}
