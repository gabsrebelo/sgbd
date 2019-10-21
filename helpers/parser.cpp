#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "parser.h"
#include "../data_types/registro.h"

#define N_ATRIBUTOS 7

std::string remove_quotes(std::string str){
    str.erase(str.begin());
    str.erase(str.end() - 1);

    return str;
}

void create_registro(std::vector< std::string > tupla){
    for(auto atrib : tupla){
        atrib = remove_quotes(atrib);
    }

    // Registro novo_registro(tupla);
    // novo_registro.print();
}

void read_file(){
    std::fstream cursor;

    // TODO: descomentar prox linha e comentar a outra

    // cursor.open("files/entrada.csv", std::ios::in); 
    cursor.open("files/entrada10.csv", std::ios::in); 

    std::vector< std::string > tupla;
    std::string linha, atributo, temp;
    int count_atributos = 0;

    if (cursor.is_open()){
        while(getline(cursor, linha)){
            tupla.clear();
            count_atributos = 0;

            std::stringstream s(linha);

            while(count_atributos < N_ATRIBUTOS){
                getline(s, atributo, ';');
                tupla.push_back(atributo);
                count_atributos++;
            }

            create_registro(tupla);
        }
    }
    else {
        std::cout << "nao abriu" << std::endl;
    }
}
