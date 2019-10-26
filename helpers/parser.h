#include <iostream>
#include <vector>
#include <string>

#ifndef PARSER
#define PARSER

void create_registro(std::vector< std::string > &tupla);
void preprocess_linha(std::string &linha);
void process_content(std::fstream &cursor);
void parse_file();

#endif