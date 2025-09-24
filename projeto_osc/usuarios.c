#include "usuarios.h"
#include <stdio.h>
#include <string.h>

int criar_tabela_usuarios(sqlite3* db) {
    const char* sql = "CREATE TABLE IF NOT EXISTS usuarios("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "nome TEXT NOT NULL, "
                      "email TEXT NOT NULL UNIQUE, "
                      "senha TEXT NOT NULL);";
    return executar_sql(db, sql);
}
;
int cadastrar_usuario(sqlite3* db, Usuario u) {
    char sql[256];
    snprintf(sql, sizeof(sql),
             "INSERT INTO usuarios (nome,email,senha) VALUES('%s','%s','%s');",
             u.nome, u.email, u.senha);
    
    
             return executar_sql(db, sql);
}

int login_usuario(sqlite3* db, const char* email, const char* senha) /*CONST CHAR É UMA STRING PARA INSERIR O EMAIL/SENHA DO USUARIO */ {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT id FROM usuarios WHERE email=? AND senha=?";
    if(sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) return 0;
    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, senha, -1, SQLITE_STATIC);
    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_ROW;
}

/* difinir se é PF ou PJ
   Fazer o cadastro "Salvo em .txt"
  */
