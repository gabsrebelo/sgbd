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
    
    Registro(std::vector< std::string > tupla){

        // for(auto &atrib : tupla){
        //     std::cout << atrib << std::endl;
        // }

        // // setVazio
        // vazio = false;

        // // setId
        // std::cout << tupla.at(0) << std::endl;
        // id = stoi(tupla.at(0));

        // // setTitulo
        // std::cout << tupla.at(1) << std::endl;
        // copy_string_to_char(tupla.at(1), titulo);

        // // setAno
        // std::cout << tupla.at(2) << std::endl;
        // ano = stoi(tupla.at(2));

        // // setAutores
        // std::cout << tupla.at(3) << std::endl;
        // copy_string_to_char(tupla.at(3), autores);
        
        // // setCitacoes
        // std::cout << tupla.at(4) << std::endl;
        // citacoes = stoi(tupla.at(4));
        
        // // setAtualizacao
        // std::cout << tupla.at(5) << std::endl;
        // copy_string_to_char(tupla.at(5), atualizacao);
        
        // // setSnippet
        // std::cout << tupla.at(6) << std::endl;
        // copy_string_to_char(tupla.at(6), snippet);
    }

    void copy_string_to_char(std::string str, char * charArray){
        str.copy(charArray, str.size() + 1);
        charArray[str.size()] = '\0';
    }

    void print(){
        std::cout << "[vazio] " << vazio << std::endl << std::endl;
        std::cout << "[id] " << id << std::endl << std::endl;
        std::cout << "[titulo] " << titulo << std::endl << std::endl;
        std::cout << "[ano] " << ano << std::endl << std::endl;
        std::cout << "[autores] " << autores << std::endl << std::endl;
        std::cout << "[citacoes] " << citacoes << std::endl << std::endl;
        std::cout << "[atualizacao] " << atualizacao << std::endl << std::endl;
        std::cout << "[snippet] " << snippet << std::endl << std::endl;
        std::cout << "--------------------" << std::endl << std::endl;
    }
};

#endif