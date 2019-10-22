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

// std::string remove_quotes(std::string str){
//     str.erase(str.begin());
//     str.erase(str.end() - 1);

//     return str;
// }

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
    // for(auto &atrib : tupla){
    //     atrib = remove_quotes(atrib);
    // }

    // check_badformat_erros(tupla);

    // Registro novo_registro(tupla);
    // novo_registro.print();
    // std::cout << novo_registro.id << std::endl;
    // place_on_hash(novo_registro);
}

bool atributo_null(std::string atributo){
    return (atributo.find("NULL") != std::string::npos) || (atributo.find(";;") != std::string::npos);
}

void read_file2(){
    std::fstream cursor;
    cursor.open("files/entrada.csv", std::ios::in);

    std::vector< std::string > tupla;
    std::string linha, temp, token;
    int len_delimiter;
    std::string delimiter = "\";\"";
    std::string delimiter2 = "\";";
    size_t pos = 0;

    if(cursor.is_open()){
        while(getline(cursor, linha)){

            // tokeniza do 1o ao penúltimo atributo, se guiando pelo delimitador ";"
            while(linha.length()){
                len_delimiter = 0;

                if((pos = linha.find(delimiter)) != std::string::npos){
                    len_delimiter = delimiter.length();
                }
                else if((pos = linha.find(delimiter2)) != std::string::npos){
                    len_delimiter = delimiter2.length();
                }   

                if(len_delimiter){
                    token = linha.substr(0, pos);

                    if(atributo_null(token)){
                        tupla.push_back("");
                    }
                    else{
                        tupla.push_back(token);
                    }

                    linha.erase(0, pos + len_delimiter);
                }
                else{
                    break;
                }
            }

            // adiciona o último
            token = linha.substr(0, linha.length() - 1);
            if(atributo_null(token)){
                tupla.push_back("");
            }
            //caso o último não seja nulo e nem termine com \" (há quebra de linha no texto)
            else if(!atributo_null(token) && token.at(token.length() - 1) != '\"'){
                std::cout << tupla.at(0) << std::endl;
                continue;
            }
            else{
                tupla.push_back(token);
            }

            std::string * token_ptr;

            // tira as aspas da primeira entrada da tupla
            token_ptr = &tupla.at(0);
            token_ptr->erase(token_ptr->begin()); 

            // tira as aspas da última entrada da tupla (se n for nula)
            token_ptr = &tupla.at(tupla.size() - 1);
            if((*token_ptr).length()){
                token_ptr->erase(token_ptr->end() - 1);
            }

            for(auto &atrib : tupla){
                std::cout << atrib << std::endl;
            }

            if(tupla.size() != 7){
                std::cout << "TAMANHO \n" << tupla.size() << std::endl;        
            }
            
            tupla.clear();
        }
    }
}

void read_file(){
    std::fstream cursor;

    cursor.open("files/entrada.csv", std::ios::in); 
    // cursor.open("files/entrada10.csv", std::ios::in); 
    // cursor.open("files/entrada200.csv", std::ios::in); 

    std::vector< std::string > tupla;
    std::string linha, atributo, temp;
    int i = 0;

    if (cursor.is_open()){
        // while(getline(cursor, linha)){

        //     // Inicializa variáveis auxiliares
        //     i = 0;
        //     tupla.clear();

        //     // Cria stream pra linha
        //     std::stringstream s(linha);

        //     // Dá um split na linha pela caractere \"
        //     while(getline(s, atributo, "\";\"")){

        //         // As strings de índice par são o conteúdo entre os pares de aspas ("..." x "..."), que podem ser um indicador de que o atributo é nulo
        //         if(i % 2 == 0){
        //             if(i > 0 && atributo_null(atributo)){
        //                 tupla.push_back("NULL");
        //             }
        //         }

        //         // Só dá push sem verificação nos elementos ímpares do split, que são o que tem propriamente entre as aspas.
        //         else if(i % 2 == 1)
        //             tupla.push_back(atributo);
                
        //         i++;
        //     }

        //     // for(auto &atrib : tupla){
        //     //     std::cout << atrib << std::endl;
        //     // }

        //     if(tupla.size() != 7){
        //         std::cout << tupla.at(0) << " - " << tupla.size() << std::endl;
        //     }

        //     // create_registro(tupla);
        // }
    }
    else {
        std::cout << "nao abriu" << std::endl;
    }
}
