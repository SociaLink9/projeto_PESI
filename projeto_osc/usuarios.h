#ifndef USUARIO_H
#define USUARIO_H

#include <stdio.h>

typedef struct {
    int id;
    char nome[100];
    char email[100];
    char senha[50];
    char telefone[20];
    char cidade[50];
    int idade;
    char area_atuacao[50];
} Voluntario;

int fazerLogin(const char* email, const char* senha);

int cadastro_voluntario(void);

#endif  
