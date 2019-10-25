#include <iostream>
#include <stdio.h>
#include "data_types/registro.h"
#include "data_types/bloco.h"
#include "helpers/hash.h"
#include "helpers/parser.h"

int main(int argc, char *argv[]){
    init_hash_file();
    // read_file();

    // Registro registro;
    // // std::cout << sizeof(registro.vazio) << std::endl;
    // // std::cout << sizeof(registro.id) << std::endl;
    // // std::cout << sizeof(registro.titulo) << std::endl;
    // // std::cout << sizeof(registro.ano) << std::endl;
    // // std::cout << sizeof(registro.autores) << std::endl;
    // // std::cout << sizeof(registro.citacoes) << std::endl;
    // // std::cout << sizeof(registro.atualizacao) << std::endl;
    // // std::cout << sizeof(registro.snippet) << std::endl;

    // // std::cout << "----------------------\n" << std::endl;
    // // std::cout << "Registro "<< sizeof(Registro) << std::endl;

    // // std::cout << "----------------------\n" << std::endl;
    // // std::cout << "Bloco "<< sizeof(Bloco) << std::endl;
    
    // findrec(atoi(argv[1]));

    // parse_file();
    read_hash_file();

    // init_mini_teste();
    // mini_teste();
    
    return 0;
}