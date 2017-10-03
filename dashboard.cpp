#include <iostream>
#include <string>
#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

int main (int argc, char* argv[]) {
	
	string opcaoEscolhida;

	// Listando opcoes que o usuario pode escolher
	cout << "(a) Dado produto, listar os 5 comentários mais úteis e com maior avaliação e os 5 comentários mais úteis e com menor avaliação" << endl;
	cout << "(b) Dado um produto, listar os produtos similares com maiores vendas do que ele" << endl;
	cout << "(c) Dado um produto, mostrar a evolução diária das médias de avaliação ao longo do intervalo de tempo coberto no arquivo de entrada" << endl;
	cout << "(d) Listar os 10 produtos lideres de venda em cada grupo de produtos" << endl;
	cout << "(e) Listar os 10 produtos com a maior média de avaliações úteis positivas por produto" << endl;
	cout << "(f) Listar a 5 categorias de produto com a maior média de avaliações úteis positivas por produto" << endl;
	cout << "(g) Listar os 10 clientes que mais fizeram comentários por grupo de produto" << endl;

	cout << "Digite a letra correspondente à opção desejada" << endl;

	getline(cin, opcaoEscolhida);

	try {
		connection C("dbname = luiz user = luiz password = luiz \
      hostaddr = 127.0.0.1 port = 5432");
      if (C.is_open()) {
         cout << "Opened database successfully: " << C.dbname() << endl;
      } else {
         cout << "Can't open database" << endl;
         return 1;
      }

	if (opcaoEscolhida == "a") {
		cout << "A escolhida!" << endl;

		string produto, sql;

		cout << "Digite o produto que deseja consultar?" << endl;
		getline(cin, produto);

		sql = "SELECT * FROM Comentarios WHERE id_produto ='" + produto + "' AND nota = 5 ORDER BY util DESC LIMIT 5;";
		
		/* Create a non-transactional object. */
      nontransaction N(C);
      
      /* Execute SQL query */
      result R( N.exec( sql ));
      
		cout << "\n\nExibindo resultados com melhor avaliação\n\n" << endl;  

      /* List down all the records */
      for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
         cout << "Título = " << c[2].as<string>() << endl;
         cout << "Data = " << c[3].as<string>() << endl;
		 cout << "Cliente = " << c[4].as<string>() << endl;
		 cout << "Nota = " << c[6].as<string>() << endl;
		 cout << "Útil = " << c[8].as<string>() << endl;
      }

		cout << "----------------------------------------" << endl;

		cout << "\n\nExibindo resultados com pior avaliação\n\n" << endl; 

		sql = "SELECT * FROM Comentarios WHERE id_produto ='" + produto + "' AND nota = 1 ORDER BY util DESC LIMIT 5;";
      
      /* Execute SQL query */
      result A( N.exec( sql ));
      
      /* List down all the records */
      for (result::const_iterator c = A.begin(); c != A.end(); ++c) {
         cout << "Título = " << c[2].as<string>() << endl;
         cout << "Data = " << c[3].as<string>() << endl;
		 cout << "Cliente = " << c[4].as<string>() << endl;
		 cout << "Nota = " << c[6].as<string>() << endl;
		 cout << "Útil = " << c[8].as<string>() << endl;
      }

	} else if (opcaoEscolhida == "b") {
		cout << "B escolhida!" << endl;

		string produto, sql, sqlToProduct;

		cout << "Digite o produto que deseja consultar?" << endl;
		getline(cin, produto);

		sql = "select * from Similares INNER JOIN Produtos ON Similares.similares = Produtos.asin where id_produto =" + produto + " AND sales_rank > (SELECT sales_rank from Produtos where id = " + produto + ");";
		
		sqlToProduct = "select * from Produtos where id =" + produto +";";

		/* Create a non-transactional object. */
      nontransaction N(C);
      
      /* Execute SQL query */
      result R( N.exec( sql ));
      
	  result B( N.exec( sqlToProduct));

	  for (result::const_iterator c = B.begin(); c != B.end(); ++c) {
         cout << "\n\nProdutos similares com maior venda que o produto " + produto + ", que possui sales rank = " + to_string(c[4]) +  "\n\n" << endl;
      }

      /* List down all the records */
      for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
         cout << "Título = " << c[6].as<string>() << endl;
         cout << "Grupo = " << c[7].as<string>() << endl;
		 cout << "Rank de vendas = " << c[8].as<string>() << endl;
      }

	} else if (opcaoEscolhida == "c") {
		cout << "C escolhida!" << endl;

		


	} else if (opcaoEscolhida == "d") {

		cout << "D escolhida!" << endl;

		string sqlBooks, sqlDVD, sqlCD, sqlVHS;

		cout << "\n\nListando Top 10 produtos líderes em venda por categoria\n\n" << endl;

		sqlBooks = "select * from Produtos where grupo = 'Book' order by sales_rank desc limit 10;";

		sqlDVD = "select * from Produtos where grupo = 'DVD' order by sales_rank desc limit 10;";

		sqlCD = "select * from Produtos where grupo = 'Music' order by sales_rank desc limit 10;";

		sqlVHS = "select * from Produtos where grupo = 'Video' order by sales_rank desc limit 10;";

		nontransaction N(C);
      
      /* Execute SQL query */
      result Book( N.exec( sqlBooks ));
      
	  result DVD( N.exec( sqlDVD));

	  result CD( N.exec( sqlCD));

	  result VHS( N.exec( sqlVHS)); 

	cout << "----------------Books----------------\n\n" << endl;

      /* List down all the records */
      for (result::const_iterator c = Book.begin(); c != Book.end(); ++c) {
         cout << "Título = " << c[2].as<string>() << endl;
         cout << "Sales Rank = " << c[4].as<string>() << endl;
      }

	cout << "\n\n----------------DVDs----------------\n\n" << endl;

	for (result::const_iterator c = DVD.begin(); c != DVD.end(); ++c) {
         cout << "Título = " << c[2].as<string>() << endl;
         cout << "Sales Rank = " << c[4].as<string>() << endl;
      }

	cout << "\n\n----------------CDs----------------\n\n" << endl;

for (result::const_iterator c = CD.begin(); c != CD.end(); ++c) {
         cout << "Título = " << c[2].as<string>() << endl;
         cout << "Sales Rank = " << c[4].as<string>() << endl;
      }

	cout << "\n\n----------------VHS'----------------\n\n" << endl;

for (result::const_iterator c = VHS.begin(); c != VHS.end(); ++c) {
         cout << "Título = " << c[2].as<string>() << endl;
         cout << "Sales Rank = " << c[4].as<string>() << endl;
      }

	} else if (opcaoEscolhida == "e") {
		cout << "E escolhida!" << endl;

		string sql;

		sql = "select titulo_prod, AVG(util) as Media from Comentarios GROUP BY comentarios.titulo_prod order by Media DESC limit 10;";
		
		/* Create a non-transactional object. */
      nontransaction N(C);
      
      /* Execute SQL query */
      result R( N.exec( sql ));
      
		cout << "\n\nTop 10 Produtos com Maiores médias de avaliações úteis\n\n" << endl;  

      /* List down all the records */
      for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
         cout << "Título = " << c[0].as<string>() << endl;
         cout << "Média = " << c[1].as<string>() << endl;
      }

	} else if (opcaoEscolhida == "f") {
		cout << "F escolhida!" << endl;
	} else if (opcaoEscolhida == "g") {

		string sqlBook, sqlDVD, sqlCD, sqlVHS;

		sqlBook = "select cliente, count(*) AS conta from Comentarios where grupo = 'Book' GROUP BY cliente ORDER BY conta DESC LIMIT 10;";

		sqlDVD = "select cliente, count(*) AS conta from Comentarios where grupo = 'DVD' GROUP BY cliente ORDER BY conta DESC LIMIT 10;";

		sqlCD = "select cliente, count(*) AS conta from Comentarios where grupo = 'Music' GROUP BY cliente ORDER BY conta DESC LIMIT 10;";

		sqlVHS = "select cliente, count(*) AS conta from Comentarios where grupo = 'Video' GROUP BY cliente ORDER BY conta DESC LIMIT 10;";
		
		/* Create a non-transactional object. */
      nontransaction N(C);
      
      /* Execute SQL query */
      result Book( N.exec( sqlBook ));

	  result DVD( N.exec( sqlDVD ));

      result CD( N.exec( sqlCD ));
 
      result VHS( N.exec( sqlVHS ));
      
		cout << "\n\nTop 10 Clientes que mais comentaram por Grupos\n\n" << endl;  

		cout << "----------------Books----------------\n\n" << endl;

      /* List down all the records */
      for (result::const_iterator c = Book.begin(); c != Book.end(); ++c) {
         cout << "Cliente = " << c[0].as<string>() << endl;
         cout << "Comentários Feitos = " << c[1].as<string>() << endl;
      }

		cout << "\n\n----------------DVDs----------------\n\n" << endl;

for (result::const_iterator c = DVD.begin(); c != DVD.end(); ++c) {
         cout << "Cliente = " << c[0].as<string>() << endl;
         cout << "Comentários Feitos = " << c[1].as<string>() << endl;
      }

		cout << "\n\n----------------CDs----------------\n\n" << endl;

for (result::const_iterator c = CD.begin(); c != CD.end(); ++c) {
         cout << "Cliente = " << c[0].as<string>() << endl;
         cout << "Comentários Feitos = " << c[1].as<string>() << endl;
      }

cout << "\n\n----------------VHS'----------------\n\n" << endl;

for (result::const_iterator c = VHS.begin(); c != VHS.end(); ++c) {
         cout << "Cliente = " << c[0].as<string>() << endl;
         cout << "Comentários Feitos = " << c[1].as<string>() << endl;
      }

		cout << "G escolhida!" << endl;
	} else {
		cout << "Opção inválida!" << endl; 	
	}

      	C.disconnect ();
} catch (const std::exception &e) {
      cerr << e.what() << std::endl;
}
}
