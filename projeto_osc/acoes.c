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

#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char titulo[100];
    char descricao[255];
    char data[11];   // "DD/MM/AAAA"
    char local[100];
    int id_ong;
} Acao; 

int main() {
    int n, i;

    printf("Quantas acoes deseja cadastrar? ");
    scanf("%d", &n);

    Acao acoes[n]; // vetor de ações

    // Entrada de dados
    for(i = 0; i < n; i++) {
        printf("\nCadastro da acao %d\n", i + 1);
        acoes[i].id = i + 1;

        printf("Titulo: ");
        scanf(" %[^\n]", acoes[i].titulo);

        printf("Descricao: ");
        scanf(" %[^\n]", acoes[i].descricao);

        printf("Data (DD/MM/AAAA): ");
        scanf(" %[^\n]", acoes[i].data);

        printf("Local: ");
        scanf(" %[^\n]", acoes[i].local);

        printf("ID da ONG responsavel: ");
        scanf("%d", &acoes[i].id_ong);
    }

    // Exibindo os dados cadastrados
    printf("\n=== Lista de Acoes ===\n");
    for(i = 0; i < n; i++) {
        printf("\nAcao %d\n", acoes[i].id);
        printf("Titulo: %s\n", acoes[i].titulo);
        printf("Descricao: %s\n", acoes[i].descricao);
        printf("Data: %s\n", acoes[i].data);
        printf("Local: %s\n", acoes[i].local);
        printf("ID ONG: %d\n", acoes[i].id_ong);
    }

    return 0;
}