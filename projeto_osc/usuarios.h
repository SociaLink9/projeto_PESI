#ifndef USUARIOS_H
#define USUARIOS_H

#include "database.h"

typedef struct {
    int id;
    char nome[50];
    char email[50];
    char senha[50];
} Usuario;

//Deletar??
int criar_tabela_usuarios(sqlite3* db);


//Revisar
int cadastrar_usuario(sqlite3* db, Usuario u);
int login_usuario(sqlite3* db, const char* email, const char* senha);

#endif
