#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "parser.h"

#define N_ATRIBUTOS 7

void read_file(){
    std::fstream cursor;

    // TODO: descomentar prox linha e comentar a outra

    // cursor.open("files/entrada.csv", std::ios::in); 
    cursor.open("files/entrada10.csv", std::ios::in); 

    std::vector< std::string > tupla;
    std::string linha, atributo, temp;

    int i; 

    if (cursor.is_open()){
        while(cursor >> temp){
            tupla.clear();

            getline(cursor, linha);
            std::cout << "linha: " << linha << std::endl;

            std::stringstream s(linha);

            while(getline(s, atributo, ';')){
                std::cout << "atributo: " << atributo << std::endl;
                tupla.push_back(atributo);
            }
        }
    }
    else {
        std::cout << "nao abriu" << std::endl;
    }
}
