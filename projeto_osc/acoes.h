#ifndef ACOES_H
#define ACOES_H

typedef struct {
    char nome[100];
    char descricao[200];
} Acao;

// Função que lê todas as ações do arquivo
void lerTodasAcoes(const char *arquivoNome);

#endif