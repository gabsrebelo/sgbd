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
    char atualizacao[20]; // "XX-XX-XXXX XX:XX:XX\0"
    char snippet[1024];

    Registro(){
        vazio = true;
    }
    
    Registro(std::vector< std::string > &tupla){
        // setVazio
        vazio = false;

        // setId
        if(!null_atribute(tupla.at(0)))
            id = stoi(tupla.at(0));
        else
            id = 0;

        // setTitulo
        if(!null_atribute(tupla.at(1)))
            copy_string_to_char(tupla.at(1), titulo);
        else
            copy_string_to_char("", titulo);

        // setAno
        if(!null_atribute(tupla.at(2)))
            ano = stoi(tupla.at(2));
        else
            ano = 0;

        // setAutores
        if(!null_atribute(tupla.at(3)))
            copy_string_to_char(tupla.at(3), autores);
        else 
            copy_string_to_char("", autores);
        
        // setCitacoes
        if(!null_atribute(tupla.at(4)))
            citacoes = stoi(tupla.at(4));
        else 
            citacoes = 0;
        
        
        // setAtualizacao
        if(!null_atribute(tupla.at(5)))
            copy_string_to_char(tupla.at(5), atualizacao);
        else
            copy_string_to_char("", atualizacao);
        
        if(tupla.at(6).length() > 1023){
            tupla.at(6) = tupla.at(6).substr(0, 1022);
        }

        // setSnippet
        if(!null_atribute(tupla.at(6)))
            copy_string_to_char(tupla.at(6), snippet);
        else
            copy_string_to_char("", snippet);
    }

    void copy_string_to_char(std::string str, char * charArray){
        str.copy(charArray, str.size() + 1);
        charArray[str.size()] = '\0';
    }

    bool null_atribute(std::string &atributo){
        return atributo == "NULL";
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