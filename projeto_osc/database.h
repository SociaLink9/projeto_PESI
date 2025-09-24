#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h> 
#include <stdio.h>
#include <stdlib.h>

// aqui ele estar criando ou abrindo uma conexão com o banco de dados 
sqlite3* abrir_conexao(const char* nome_banco);

// Fecha a conexão
void fechar_conexao(sqlite3* db);

// Executa uma query SQL simples
int executar_sql(sqlite3* db, const char* sql);

#endif
