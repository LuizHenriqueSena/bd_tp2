#include <iostream>

using namespace std;

int main(){
	string a = "id: parapapapasdp sadpl dsap ldsapl dapsl ";
	int pos = a.find("id: ");
	string teste = "nao funcionou";
	if (pos == -1){
	cout << teste <<endl;
	return 1;
}
	else{
	teste = a.substr(pos + 2);
}

	cout << teste <<endl;
return 0;
}

