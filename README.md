# bd_tp2
Trabalho pratico 2 de bd

Para conseguir compilar os arquivos cpp presente neste repositorio e necessario:
-Linux
-Postgresql
-libpqxx (conector de c++ com postgresql)

arquivos devem ser compilados desta maneira:
g++ criaTabela.cpp -o cria -std=c++11 -lpqxx -lpq
g++ cargaarquivo.cpp -o carga -std=c++11 -lpqxx -lpq
g++ dashboard.cpp -o dashboard -std=c++11 -lpqxx -lpq

e devem ser executados os binarios na seguinte ordem:
./cria
./carga
./dashboard



