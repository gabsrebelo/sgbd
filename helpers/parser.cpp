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

void create_registro(std::vector< std::string > &tupla){
    Registro novo_registro(tupla);
    novo_registro.print();

    // place_on_hash(novo_registro);
}

void teste(std::vector<std::string> &tupla){
    std::ofstream cursor;
    cursor.open("files/teste.txt", std::ios::out | std::ios::app);

    int i = 0;

    for(i = 0; i < 6; i++){
        std::cout << tupla.at(i) << std::endl;
        cursor << tupla.at(i) << std::endl;
    }

    std::cout << tupla.at(6) << std::endl;
    cursor << tupla.at(6) << std::endl;

    cursor.close();
}

void preprocess_linha(std::string &linha){
    std::string null_indicator1 = "NULL"; 
    std::string null_indicator2 = "\";;\"";
    
    int len1 = null_indicator1.length();
    int len2 = null_indicator2.length();

    std::string replace1 = "\"NULL\"";
    std::string replace2 = "\";\"NULL\";\"";

    int rep_len1 = replace1.length();
    int rep_len2 = replace2.length();

    size_t pos = 0;

    while((pos = linha.find(null_indicator1, pos)) != std::string::npos){
        linha.replace(pos, len1, replace1);
        pos += rep_len1;
    }

    pos = 0;

    while((pos = linha.find(null_indicator2, pos)) != std::string::npos){
        linha.replace(pos, len2, replace2);
        pos += rep_len2;
    }
}

void process_content(std::fstream &cursor){

    std::vector< std::string > tupla;
    std::string linha, token;
    std::string delimiter = "\";\"";
    std::string delimiter2 = "\";";
    int len_delimiter;
    size_t pos;

    pos = 0;
    token = "";

    while(getline(cursor, linha)){

        preprocess_linha(linha);

        // tokeniza do 1o ao penúltimo atributo, se guiando pelo delimitador ";"
        while(linha.length()){
            len_delimiter = 0;

            // se há, na linha, um \";\", então esse é o delimitador
            if((pos = linha.find(delimiter)) != std::string::npos){
                len_delimiter = delimiter.length();
            }

            // se há na verdade um \"; na linha, então esse é o delimitador
            else if((pos = linha.find(delimiter2)) != std::string::npos){
                len_delimiter = delimiter2.length();
            }   

            // se ainda há algum delimiter na linha pra fazer divisão
            if(len_delimiter){
                if(token.length()){
                    token += linha.substr(0, pos);
                }
                else{
                    token = linha.substr(0, pos);
                }

                tupla.push_back(token);

                linha.erase(0, pos + len_delimiter);
                token = "";
            }

            // esse caso é quando já se está no último atributo e, portanto, não tem mais
            // nenhum dos dois delimitadores na linha.
            else{
                break;
            }
        }

        // tokeniza o último atributo
        token = linha.substr(0, linha.length() - 1);

        // quando algum atributo quebra na metáde (contém '\n') e é necessário continuar processando a 
        // mesma tupla só que com a outra linha, vai pro próximo passo do loop sem limpar a tupla
        // e nem o token.
        if(tupla.size() < 6){
            continue;
        }

        tupla.push_back(token);

        std::string * token_ptr;

        // tira as aspas da primeira entrada da tupla
        token_ptr = &tupla.at(0);
        token_ptr->erase(token_ptr->begin()); 

        // tira as aspas da última entrada da tupla (se n for nula)
        token_ptr = &tupla.at(tupla.size() - 1);
        if((*token_ptr).length()){
            token_ptr->erase(token_ptr->end() - 1);
        }

        // std::cout << tupla.at(0) << std::endl;

        // if(tupla.size() != 7){
        //     std::cout << tupla.at(0) << std::endl;
        // }

        // teste(tupla);

        create_registro(tupla);
        
        token = "";
        tupla.clear();
    }
}

void read_file(){
    std::fstream cursor;
    cursor.open("files/entrada.csv", std::ios::in);

    if(cursor.is_open()){
        process_content(cursor);
    }
    else{
        std::cout << "Erro ao abrir arquivo." << std::endl;
    }
}