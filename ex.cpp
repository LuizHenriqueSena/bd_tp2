#include <iostream>

using namespace std;

int main(){
string b,c,d;
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
}
}

