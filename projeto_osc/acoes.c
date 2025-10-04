#include <stdio.h>
#include <string.h>
#include "acoes.h"
#include "usuarios.h"

void lerTodasAcoes(const char *arquivoNome) {
    FILE *arquivo = fopen(arquivoNome, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char linha[256];
    Acao acao;
    int contador = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0';

        if (strncmp(linha, "NomeAcao:", 9) == 0) {
            strcpy(acao.nome, linha + 9);
            while (fgets(linha, sizeof(linha), arquivo)) {
                linha[strcspn(linha, "\n")] = '\0';

                if (strncmp(linha, "Descricao:", 10) == 0) {
                    strcpy(acao.descricao, linha + 10);
                } 
            }

            printf("Ação %d:\n", ++contador);
            printf("  Nome: %s\n", acao.nome);
            printf("  Descrição: %s\n", acao.descricao);
           
        }
    }

    fclose(arquivo);
}
int varificar_voluntario(char *cpf ){

    FILE *arquivo = fopen("dados.txt","r");
    
    char cpf_v[11];

    while(fgets(cpf_v,sizeof(cpf_v), arquivo) != NULL){

        if(strcmp(cpf,cpf_v)){

            return 1;
        }

    }
    return 0;
}
