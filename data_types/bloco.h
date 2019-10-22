#include <iostream>
#include <string>
#include <vector>
#include "registro.h"

#ifndef BLOCO_CLASS
#define BLOCO_CLASS

class Bloco {
public:
    Registro registros[2]; // size = 3024
    char lixo[1072]; // usado para completar os 4k do bloco (4096 - 3024 = 1072)

    void print(){
        if(!registros[0].vazio){
            std::cout << "1o registro do bloco" << std::endl << std::endl;
            registros[0].print();
        }
        else{
            std::cout << "1o registro do bloco está vazio" << std::endl << std::endl;
        }

        if(!registros[1].vazio){
            std::cout << "2o registro do bloco" << std::endl << std::endl;
            registros[1].print();
        }
        else{
            std::cout << "2o registro do bloco está vazio" << std::endl << std::endl;
        }
        
        std::cout << "----------------------------------------" << std::endl << std::endl;
    }

    bool push_registro(Registro registro){
        if(registros[0].vazio){
            registros[0] = registro;
        }
        else if(registros[1].vazio){
            registros[1] = registro;
        }
        else {
            return false;
        }

        return true;
    }
};

#endif
