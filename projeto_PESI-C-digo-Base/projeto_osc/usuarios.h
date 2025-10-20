#ifndef USUARIO_H
#define USUARIO_H

#include <stdio.h>

// Definições de tamanho
#define TAM_NOME 100
#define TAM_CPF 13
#define TAM_EMAIL 100
#define TAM_TELEFONE 20
#define TAM_CIDADE 50
#define TAM_AREA_ATUACAO 50

typedef struct
{
    int id;
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char email[TAM_EMAIL];
    char telefone[TAM_TELEFONE];
    char cidade[TAM_CIDADE];
    char area_atuacao[TAM_AREA_ATUACAO];
} Voluntario;

// Função de cadastro de voluntário
int cadastro_voluntario(void);

#endif