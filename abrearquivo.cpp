#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <pqxx/pqxx>
using namespace std;
using namespace pqxx;

int main () {
	string sql;
	int id, salesrank;
	string asin, title, grupo;
  string line;
  ifstream myfile ("amazon-meta.txt"); // ifstream = padrão ios:in
///home/luiz/Downloads/amazon-meta.txt
  if (myfile.is_open())
  {
    while (! myfile.eof() ) //enquanto end of file for false continua
    {
      getline (myfile,line); // como foi aberto em modo texto(padrão)
                             //e não binário(ios::bin) pega cada linha

	if(line.find("ASIN: ") != -1){
	asin = line.substr(line.find("ASIN: ") + 6);
	cout << "bd_asin = " + asin<<endl;
}
	else if(line.find("title: ") != -1){
	title = line.substr(line.find("title: ") + 7);
	cout << "bd_title = " + title<<endl;
}
	else if(line.find("group: ") != -1){
	grupo = line.substr(line.find("group: ") + 7);
	cout << "bd_od = " + grupo<<endl;
}
	else if(line.find("salesrank: ") != -1){
	salesrank = atoi(line.substr(line.find("salesrank: ") + 11).c_str());
	cout << " bd_salesrank = " + to_string(salesrank) <<endl;
}
	else if (line.find("Id: ")!= -1){
	id = atoi(line.substr(line.find("Id: ") + 4).c_str());
	cout << "bd_od = " + to_string(id)<<endl;
}
	else{	
 
    }
}
    myfile.close();
  }

  else  
cout << "Unable to open file"; 

  return 0;
}


