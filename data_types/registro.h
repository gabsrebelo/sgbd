#include <iostream>
#include <vector>
#include <string>

#ifndef REGISTRO_CLASS
#define REGISTRO_CLASS

class Registro
{
public:
    bool vazio;
    int id;
    char titulo[300];
    int ano;
    char autores[150];
    int citacoes;
    char atualizacao[19]; // "XX-XX-XXXX XX:XX:XX"
    char snippet[1024];

    Registro(){
        vazio = true;
    }
    
    // Registro(std::vector< std::string > tupla){
    //     std::string str;
        
    //     vazio = false;

    //     id = stoi(tupla.at(0));

    //     str = tupla.at(1);
    //     str.copy(titulo, str.size() + 1);
    //     titulo[str.size()] = '\0';

    //     ano = stoi(tupla.at(2));
        
    //     str = tupla.at(3);
    //     str.copy(autores, str.size() + 1);
    //     autores[str.size()] = '\0';
        
    //     citacoes = stoi(tupla.at(4));
        
    //     str = tupla.at(5);
    //     str.copy(atualizacao, str.size() + 1);
    //     atualizacao[str.size()] = '\0';
        
    //     str = tupla.at(6);
    //     str.copy(snippet, str.size() + 1);
    //     snippet[str.size()] = '\0';
    // }

    void print(){
        std::cout << vazio << id << titulo << ano << autores << citacoes << atualizacao << snippet << std::endl;
    }
};

#endif