#include "database.h"
//ESSA FUNÇAO ABRE A CONEXÂO COM O BANCO E EM CASO DE ERRO MOSTRA UMA MENSAGEM
sqlite3* abrir_conexao(const char* nome_banco) {
    sqlite3* db;
    int rc = sqlite3_open(nome_banco, &db);
    if(rc != SQLITE_OK) // SE RC FOR DIFERENTE DE (SQLITE_OK "CONEXÃO ABERTA" ELE EXIBI UMA MENSAGEM DE ERRO! )
       {
        fprintf(stderr, "Erro ao abrir banco de dados: %s\n", sqlite3_errmsg(db));
        return NULL;
    }
    return db;
}

void fechar_conexao(sqlite3* db) {
    if(db) sqlite3_close(db);
}

int executar_sql(sqlite3* db, const char* sql) {
    char* erro_msg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &erro_msg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "Erro SQL: %s\n", erro_msg);
        sqlite3_free(erro_msg);
    }
    return rc;
}

