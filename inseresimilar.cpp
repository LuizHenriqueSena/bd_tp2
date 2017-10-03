#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;

string removeQuebraLinha(string a)
{ 
 	string b = a;
	if (b.find("\n") != -1) {
		b = b.substr(0, b.find("\n"));
}
	if (b.find("\r") != -1) {
		b = b.substr(0, b.find("\r"));
}
	return b;
}

int main () {
string line;
int flag = 0;
  ifstream myfile("exemplo.txt"); // ifstream = padrão ios:in
  if (myfile.is_open())
  {
    while (! myfile.eof() ) //enquanto end of file for false continua
    {
      getline (myfile,line); // como foi aberto em modo texto(padrão)
                             //e não binário(ios::bin) pega cada linha
	if ((line.find("reviews: total: ") != -1) && (flag == 0)) {
		if (line.find("reviews: total: 0") == -1) {
			flag = 1;
}
}
	else if((flag == 1) && (line.find ("cutomer: ") != -1)) {
		string data, cliente, grupo;
		int nota, votos, util;
		line = removeQuebraLinha(line);
		cout << line << endl;
		data = line.substr(4,10);
		cliente = line.substr(line.find("cutomer: ") + 9, 14);
		nota = atoi(line.substr(line.find("rating: ") + 8, 1).c_str());
		votos = atoi(line.substr(line.find("votes: ") + 8, 3).c_str());
		util = atoi(line.substr(line.find("helpful: ") + 9, 3).c_str());

		cout <<"DATA: "+data + ".cliente: " + cliente + ". NOTA: "+to_string(nota)+".votos: "+
to_string(votos)+".util: "+to_string(util) + "." <<endl;

			//sql = "INSERT INTO Similares (id,id_produto,similares) VALUES (default, "+id+", '" + similar "');" ;
      /* Execute SQL query */
      //	 W.exec( sql );
		
		
}
}
}
myfile.close();
}

