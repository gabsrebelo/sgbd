#include "hash.h"
#include "../data_types/bloco.h"
#include "../data_types/registro.h"
#include "parser.h"
#include <iostream>
#include <fstream>
#include <cstdio>

/*

    BUCKET: 4 blocos
    N_BUCKETS: 196.613 buckets
    N_BLOCOS: 786.452 blocos
    N_MAX_REGISTERS: 1.572.904

    HASH_FILE_SIZE: 3.24 GB

*/

#define N_BUCKETS 196613 
#define TAM_BUCKET 16384 // 4 * 4096
#define TAM_BLOCO 4096 
#define BLOCOS_POR_BUCKET 4
#define N_TOTAL_BLOCOS 786452 // 4 * N_BUCKETS
#define HASH_FILE_PATH "files/hash.bin" 

void init_hash_file(){
    std::ifstream cursor_teste;

    // Abre o arquivo `hash.bin` para leitura apenas pra testar se ele existe.
    cursor_teste.open(HASH_FILE_PATH, std::ios::in);

    // Se o arquivo não existir, cria.
    if(!cursor_teste.is_open()){
        std::cout << "[HASH] Criando arquivo de hash vazio..." << std::endl;

        // Cria o arquivo binário
        std::ofstream cursor_binario;
        cursor_binario.open(HASH_FILE_PATH, std::ios::binary);

        // Aloca um bloco mas não o preenche
        Bloco bloco_vazio;

        // Escreve N_TOTAL_BLOCOS [vazios] no arquivo de hash
        for(int i = 0; i < N_TOTAL_BLOCOS; i++){
            cursor_binario.write((char*) &bloco_vazio, sizeof(Bloco));
        }   
    }
}

void findrec(int id){
    Bloco bloco;
    Registro registro;
    long bucket_byte = get_bucket_byte(id);
    int count_blocks = 0;
    int i = 0;
    int found = 0;

    std::ifstream cursor_leitura(HASH_FILE_PATH, std::ios::binary);

    if(cursor_leitura.is_open()){
        cursor_leitura.seekg(bucket_byte, std::ios::beg);

        while(i < BLOCOS_POR_BUCKET){
            cursor_leitura.read((char *) &bloco, sizeof(Bloco));

            if(bloco.not_null()){
                registro = bloco.registros[0];

                if(registro.id == id){
                    found = 1;
                    break;
                }

                registro = bloco.registros[1];
                if(!registro.vazio && registro.id == id){
                    found = 1;
                    break;
                }
            }

            i++;
        }

        cursor_leitura.close();        

        if(found){
            std::cout << "[FINDREC] Leu " << i << " blocos para encontrar o registro com id " << id << std::endl;
        }
        else{
            std::cout << "[FINDREC] Leu " << i << " blocos e NAO ENCONTROU o registro com id " << id << std::endl;
        }

        std::cout << "[FINDREC] Numero total de blocos no arquivo de dados: " << N_TOTAL_BLOCOS << std::endl;
    }
    else{
        std::cout << "[FINDREC] Erro ao tentar abrir arquivo de dados." << std::endl;
    }
}

long get_bucket(int id){
    return id % N_BUCKETS;
}

long get_bucket_byte(int id){
    return get_bucket(id) * TAM_BUCKET;
}

void place_on_hash(Registro registro){

    Bloco bloco;
    long bucket_byte = get_bucket_byte(registro.id);
    int i = 0;

    std::ifstream cursor_leitura(HASH_FILE_PATH, std::ios::binary);
    std::ofstream cursor_escrita(HASH_FILE_PATH, std::ios::binary | std::ios::app);

    if(cursor_leitura.is_open()){
        cursor_leitura.seekg(bucket_byte, std::ios::beg);

        while(i < BLOCOS_POR_BUCKET){
            cursor_leitura.read((char *) &bloco, sizeof(Bloco));

            if(!bloco.full()){
                bloco.push_registro(registro);
                // std::cout << registro.id << " inseriu com sucesso no bloco " << i << "do bucket "<< get_bucket(registro.id) << std::endl << std::endl;
                cursor_escrita.seekp(bucket_byte, std::ios::beg); 
                cursor_escrita.write((char *) &bloco, sizeof(Bloco));
                break;
            }

            i++;
        }
        
        cursor_leitura.close();
    }
    else{
        std::cout << "error ao abrir " << HASH_FILE_PATH << std::endl;
    }
    cursor_escrita.close();
}

void read_hash_file(){
    std::ifstream cursor_binario(HASH_FILE_PATH, std::ios::binary);
    
    int bucket = 0;
    int blo = 1;
    Bloco bloco;

    if(cursor_binario.is_open()){
        while(!cursor_binario.eof()){
            if(blo == 1){
                bucket++;
                std::cout << "-------------------------------- [BUCKET "<< bucket << "] " << std::endl;
            }

            std::cout << "[BLOCO " << blo << "]" << std::endl;
            bloco.print();

            cursor_binario.read((char *) &bloco, sizeof(Bloco));

            blo++;
            if(blo == 5) blo = 1;
        }
    }
    else{
        std::cout << "Erro ao abrir arquivo de hash." << std::endl;
    }

    cursor_binario.close();
}