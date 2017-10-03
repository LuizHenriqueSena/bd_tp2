#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <pqxx/pqxx>
using namespace std;
using namespace pqxx;

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
	int flacat = 0;
	int flagrev = 0;
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

	if((line.find("title: ") != -1)&&(flagrev ==0)){
		if(line.find("'") == -1) {
	title = line.substr(line.find("title: ") + 7);
	title = removeQuebraLinha(title);
	cout << "bd_title = " + title<<endl;
}
		else {
			title = "Titulo com defeito";
			cout << "bd_title = " + title<<endl;
}
}
	else if(line.find("ASIN: ") != -1){
	asin = line.substr(line.find("ASIN: ") + 6);
	asin = removeQuebraLinha(asin);
	cout << "bd_asin = " + asin<<endl;
}

	else if(line.find("group: ") != -1){
	grupo = line.substr(line.find("group: ") + 7);
	grupo = removeQuebraLinha(grupo);
	cout << "bd_od = " + grupo<<endl;
}
	else if (line.find("Id: ")!= -1){
	id = atoi(line.substr(line.find("Id: ") + 3).c_str());
	cout << "bd_Id = " + to_string(id)<<endl;
	flagrev = 0;
}
	else if(line.find("salesrank: ") != -1){
	salesrank = atoi(line.substr(line.find("salesrank: ") + 11).c_str());
	cout <<" bd_salesrank = " + to_string(salesrank) <<endl;

	 sql = "INSERT INTO Produtos (id,asin,title,grupo,sales_rank) "  \
         "VALUES (" + to_string(id) + ", '" + asin + "','" + title+ "', '" + grupo+ "', " + to_string(salesrank) + "); ";  
      /* Execute SQL query */
      	 W.exec( sql );
}
	else if (line.find("similar: ") != -1) {
		if (line.find("similar: 0") == -1) {
		line = removeQuebraLinha(line);
		string line2 = line.substr(line.find("similar: ") + 12, line.size() -1);
		int tamanho = atoi(line.substr(line.find("similar: ") + 9,3).c_str());
		for(int i = 0; i < tamanho; i++){
			string similar = line2.substr(i*12,10);
			sql = "INSERT INTO Similares (id,id_produto,similares) VALUES (default, "+to_string(id)+", '" + similar+ "');" ;
      /* Execute SQL query */
      	 W.exec( sql );
		
		
}
}
}
	if ((line.find("reviews: total: ") != -1) && (flagrev == 0)) {
		if (line.find("reviews: total: 0") == -1) {
			flagrev = 1;
}
}
	else if((flagrev == 1) && (line.find ("cutomer: ") != -1)) {
		string data, cliente, grupo;
		int nota, votos, util;
		line = removeQuebraLinha(line);
		data = line.substr(4,10);
		cliente = line.substr(line.find("cutomer: ") + 9, 14);
		nota = atoi(line.substr(line.find("rating: ") + 8, 1).c_str());
		votos = atoi(line.substr(line.find("votes: ") + 8, 3).c_str());
		util = atoi(line.substr(line.find("helpful: ") + 9, 3).c_str());

		sql = "INSERT INTO Comentarios (id_comentario,id_produto,titulo_prod,data,cliente,grupo,nota,votos,util) VALUES(default,"+to_string(id)+ ",'"+title+"', '"+data+"','"+cliente+"','"+grupo+"',"+to_string(nota)+","+to_string(votos)+","+to_string(util)+");";
		W.exec(sql);
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




