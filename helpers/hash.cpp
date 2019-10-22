#include "hash.h"
#include "../data_types/bloco.h"
#include "../data_types/registro.h"
#include <iostream>
#include <fstream>

/*

    BUCKET: 4 blocos
    N_BUCKETS: 196.613 buckets
    N_BLOCOS: 786.452 blocos
    N_MAX_REGISTERS: 1.572.904

    HASH_FILE_SIZE: 3.24 GB

*/

#define N_BUCKETS 196613
#define TAM_BUCKET 16384
#define TAM_BLOCO 4096
#define BLOCOS_POR_BUCKET 4
#define N_TOTAL_BLOCOS 786452 // 4 * N_BUCKETS
#define HASH_FILE_PATH "files/hash.bin"

void init_hash_file(){
    std::fstream cursor_teste;

    // Abre o arquivo `hash.bin` para leitura apenas pra testar se ele existe.
    cursor_teste.open(HASH_FILE_PATH, std::ios::in);

    // Se o arquivo não existir, cria.
    if(!cursor_teste.is_open()){
        std::cout << "[INIT] Criando arquivo de hash" << std::endl;

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

int get_bucket(int id){
    return id % N_BUCKETS; 
}

int get_bucket_byte(int id){
    return get_bucket(id) * TAM_BUCKET + 1;
}

void place_on_hash(Registro registro){
    int bucket_byte = get_bucket_byte(registro.id);

    // std::cout << "[hash_bucket_byte] " << bucket_byte << std::endl << std::endl; 
    // std::cout << "--------------------" << std::endl << std::endl;

    Bloco bloco;    

    std::ifstream cursor_binario(HASH_FILE_PATH, std::ios::binary);
    if(cursor_binario.is_open()){
        cursor_binario.read((char *) &bloco, sizeof(Bloco));
    }

    // bloco.print();

    if(bloco.push_registro(registro)){
        std::cout << "inseriu com sucesso no bloco. " << std::endl << std::endl;
    }
    else{
        std::cout << "[COLISÃO] não foi possível inserir no bloco" << std::endl << std::endl;
    }
}