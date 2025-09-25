#include <stdio.h>


// Ler todas as acoes criadas em oscs.c (Função)

//Indentificar usuarios cadastrados como voluntario e suas respectivas funções (funçÃo)


void ler_acoes{


    FILE *arquivo; 
    char linha[256];

    // Abre o arquivo em modo leitura
    arquivo = fopen("dados.txt", "r");

    // Verifica se o arquivo foi aberto corretamente
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Lê linha por linha até o final do arquivo
    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s", linha);
    }

    // Fecha o arquivo
    fclose(arquivo);

}