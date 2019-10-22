#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include "parser.h"
#include "hash.h"
#include "../data_types/registro.h"

#define N_ATRIBUTOS 7

std::string remove_quotes(std::string str){
    str.erase(str.begin());
    str.erase(str.end() - 1);

    return str;
}

void check_badformat_erros(std::vector< std::string > &tupla){
    std::string id = tupla.at(0);

    if(id == "4" || id == "12" || id == "20"){
        tupla.at(3) += tupla.at(4);
        tupla.erase(tupla.begin() + 4);
    }
    if(id == "20"){
        tupla.at(3) += tupla.at(4);
        tupla.erase(tupla.begin() + 4);
    }
}

void create_registro(std::vector< std::string > tupla){
    for(auto &atrib : tupla){
        atrib = remove_quotes(atrib);
    }

    check_badformat_erros(tupla);

    Registro novo_registro(tupla);
    // novo_registro.print();
    std::cout << novo_registro.id << std::endl;
    place_on_hash(novo_registro);
}

void read_file(){
    std::fstream cursor;

    // TODO: descomentar prox linha e comentar a outra

    cursor.open("files/entrada.csv", std::ios::in); 
    // cursor.open("files/entrada10.csv", std::ios::in); 

    std::vector< std::string > tupla;
    std::string linha, atributo, temp;
    int i = 0;

    if (cursor.is_open()){
        while(getline(cursor, linha)){

            // Inicializa variáveis auxiliares
            i = 0;
            tupla.clear();

            // Cria stream pra linha
            std::stringstream s(linha);

            // Dá um split na linha pela caractere \"
            while(getline(s, atributo, '\"')){

                // Só dá push nos elemntos pares do split, porque nos outros não tem nada (é o que tem entre um atrib e outro)
                if(i % 2 == 1)
                    tupla.push_back(atributo);
                i++;
            }

            // for(auto &atrib : tupla){
            //     std::cout << atrib << std::endl;
            // }

            // std::cout << "-------" << tupla.size() << std::endl;

            create_registro(tupla);
        }
    }
    else {
        std::cout << "nao abriu" << std::endl;
    }
}
