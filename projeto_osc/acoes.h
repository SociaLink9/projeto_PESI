#ifndef ACOES_H
#define ACOES_H

typedef struct
{
    char nome[100];
    char descricao[200];
} Acao;

// Função que lê todas as ações do arquivo
void lerTodasAcoes();
int cpf_cadastrado(const char *arquivo, const char *cpf_busca);
void cadastrarVoluntarioInterativo();
void mostrarUsuariosPorAcao();

#endif