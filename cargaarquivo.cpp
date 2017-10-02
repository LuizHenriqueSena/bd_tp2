#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <pqxx/pqxx>
using namespace std;
using namespace pqxx;

int main () {

try {
      connection C("dbname = luiz user = luiz password = luiz \
      hostaddr =127.0.0.1 port =5432");
      if (C.is_open()) {
         cout << "Opened database successfully: " << C.dbname() << endl;
      } else {
         cout << "Can't open database" << endl;
      }
 /* Create a transactional object. */
      	work W(C);
	string sql;
	int id, salesrank;
	string asin, title, grupo;
  string line;
  ifstream myfile ("/home/luiz/Downloads/amazon-meta.txt"); // ifstream = padrão ios:in
  if (myfile.is_open())
  {
    while (! myfile.eof() ) //enquanto end of file for false continua
    {
      getline (myfile,line); // como foi aberto em modo texto(padrão)
                             //e não binário(ios::bin) pega cada linha

      if (line.find("Id: ")!= -1){
	id = atoi(line.substr(line.find("Id: ") + 3).c_str());
}
	else if(line.find("ASIN: ") != -1){
	asin = line.substr(line.find("ASIN: ") + 6);
}
	else if(line.find("title: ") != -1){
	title = line.substr(line.find("title: ") + 7);
}
	else if(line.find("group: ") != -1){
	grupo = line.substr(line.find("group: ") + 7);
}
	else if(line.find("salesrank: ") != -1){
	salesrank = atoi(line.substr(line.find("salesrank: ") + 11).c_str());
	cout << "bd_id = " + to_string(id) + " bd_asin = " + asin + " bd_title = '"+ title + " bd_group = " + grupo +
	" bd_salesrank = " + to_string(salesrank) <<endl;

	 sql = "INSERT INTO Produtos (id,asin,title,grupo,sales_rank) "  \
         "VALUES (" + to_string(id) + ", '" + asin + "','" + title+ "', '" + grupo+ "', " + to_string(salesrank) + "); ";  
      /* Execute SQL query */
      	 W.exec( sql );
}
	else{	
 
    }
}
    myfile.close();
  }

  else { 
cout << "Unable to open file"; 
}

	W.commit();
      	cout << "Records created successfully" << endl;
      	C.disconnect ();
   } catch (const std::exception &e) {
      cerr << e.what() << std::endl;

  return 0;
}

















}

