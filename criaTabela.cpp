#include <iostream>
#include <pqxx/pqxx> 

using namespace std;
using namespace pqxx;

int main(int argc, char* argv[]) {
   char * sql;
   string dbname, nome, password;
   cout<<"Digite o nome do bd:";
	getline(cin,dbname);
   cout<<"Digite o nome do usuario:";
	getline(cin,nome);
   cout<<"Digite a senha do usuario:";
	getline(cin,password);
   try {
      connection C("dbname =" +dbname + " user = "+ nome +" password = "+password+" \
      hostaddr = 127.0.0.1 port = 5432");
      if (C.is_open()) {
         cout << "Opened database successfully: " << C.dbname() << endl;
      } else {
         cout << "Can't open database" << endl;
         return 1;
      }

      /* Create a transactional object. */
      work W(C);
      
      /* Create the SQL query */
      sql = "CREATE TABLE Produtos("  \
      "id INT PRIMARY KEY     NOT NULL," \
      "asin           TEXT    NOT NULL," \
      "title          TEXT    NOT NULL," \
      "grupo          TEXT    NOT NULL," \
      "sales_rank     INT     NOT NULL);";

      /* Execute SQL query */
      W.exec( sql );
     // W.commit();
      cout << "Table Produtos created successfully" << endl;

      /* Create the SQL query */
      sql = "CREATE TABLE Similares("  \
      "id INT PRIMARY KEY     NOT NULL," \
      "id_Produto     INT     NOT NULL," \
      "similares        text    NOT NULL);";

      /* Execute SQL query */
      W.exec( sql );
      //W.commit();
      cout << "Table Similares created successfully" << endl;

      /* Create the SQL query */
      sql = "CREATE TABLE Comentarios("  \
      "id_comentario  INT PRIMARY KEY     NOT NULL," \
      "id_produto     TEXT    NOT NULL," \
      "data           TEXT    NOT NULL," \
      "cliente        TEXT    NOT NULL," \
      "nota           INT     NOT NULL," \
      "votos          INT     NOT NULL," \
      "util           INT     NOT NULL);";

      /* Execute SQL query */
      W.exec( sql );
      //W.commit();
      cout << "Table Comentarios created successfully" << endl;

      /* Create the SQL query */
      sql = "CREATE TABLE Cliente("  \
      "id_cliente INT PRIMARY KEY     NOT NULL," \
      "id_produto     TEXT    NOT NULL);";

      /* Execute SQL query */
      W.exec( sql );
      //W.commit();
      cout << "Table cliente created successfully" << endl;

      /* Create the SQL query */
      sql = "CREATE TABLE Grupos("  \
      "id_grupo INT PRIMARY KEY     NOT NULL," \
      "nome     TEXT    NOT NULL);";

      /* Execute SQL query */
      W.exec( sql );
      W.commit();
      cout << "Table Grupos created successfully" << endl;



      C.disconnect ();
   } catch (const std::exception &e) {
      cerr << e.what() << std::endl;
      return 1;
   }

   return 0;
}
