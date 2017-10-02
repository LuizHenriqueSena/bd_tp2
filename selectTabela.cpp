#include <iostream>
#include <pqxx/pqxx> 

using namespace std;
using namespace pqxx;

int main(int argc, char* argv[]) {
   string sql;
   string dbname, nome, password;
   string tabela;
   cout<<"Digite o nome do bd:";
	getline(cin,dbname);
   cout<<"Digite o nome do usuario:";
	getline(cin,nome);
   cout<<"Digite a senha do usuario:";
	getline(cin,password);
   cout<<"Digite a senha da tabela:";
	getline(cin,tabela);
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
      
      /* Create SQL statement */
      sql = "SELECT * from " + tabela;

      /* Create a non-transactional object. */
      nontransaction N(C);
      
      /* Execute SQL query */
      result R( N.exec( sql ));
      
      /* List down all the records */
      for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
         cout << "ID = " << c[0].as<int>() << endl;
         cout << "texto = " << c[1].as<string>() << endl;
      }
      cout << "Operation done successfully" << endl;
      C.disconnect ();
   } catch (const std::exception &e) {
      cerr << e.what() << std::endl;
      return 1;
   }

   return 0;
}
