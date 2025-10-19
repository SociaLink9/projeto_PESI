#ifndef USUARIO_H
#define USUARIO_H

#include <stdio.h>

typedef struct
{
    int id;
    char nome[100];
    char cpf[11];
    char email[100];
    char telefone[20];
    char cidade[50];
    char area_atuacao[50];
} Voluntario;

// Login não ira ser usado no momento.(Projetar para implementação futura).
// int fazerLogin(const char* email, const char* senha);

int cadastro_voluntario(void);

#endif
