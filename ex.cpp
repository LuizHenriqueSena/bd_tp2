#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;

int main(){

 	string b = "dsakjdsajka/r/n sad sad /n saddasdsasdadsa";
	if (b.find("/r") != -1) {
		b = b.substr(0, b.find("/r"));
}
	if (b.find("/n") != -1) {
		b = b.substr(0, b.find("/n")1);
}
	cout << b <<endl;
	return 1;
}





/*string b,c,d;
	string a = "id: the girls isn't that nice ";
	int pos = a.find("id: ");
	string teste = "nao funcionou";
	if (pos == -1){
	cout << "problema" <<endl;
	return 1;
}
	else{
	teste = a.substr(pos + 4);

	if (teste.find("'")){
	b = teste.substr(0, teste.find("'"));
	c = teste.substr(teste.find("'"));
	d = b + "'" + c;
}

	cout << d <<endl;
return 0;
} */
