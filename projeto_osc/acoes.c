#include <stdio.h>
#include <string.h>
#include "acoes.h"
#include "usuarios.h"
#include "oscs.h"

void lerTodasAcoes()
{
    FILE *arquivoNome = fopen("listadeacoes.txt", "r");
    char linha[256];

    if (!arquivoNome) {
        printf("Não foi possível abrir o arquivo.\n");
        return;
    }

    printf("Ações cadastradas:\n");
    while (fgets(linha, sizeof(linha), arquivoNome)) {
        printf("\n%s", linha);
    }

    fclose(arquivoNome);
}


// Retorna 1 se o CPF estiver cadastrado, 0 caso contrário
int cpf_cadastrado(const char *arquivo, const char *cpf_busca)
{
    FILE *fp = fopen(arquivo, "r");
    if (!fp)
    {
        perror("Erro ao abrir dados.txt");
        return 0;
    }

    char linha[512];
    while (fgets(linha, sizeof(linha), fp))
    {
        if (strstr(linha, "Pessoa Fisica"))
        {
            char *ptr_cpf = strstr(linha, "CPF:");
            if (ptr_cpf)
            {
                char cpf_lido[20];
                sscanf(ptr_cpf, "CPF: %s", cpf_lido);

                // Remove possíveis quebras de linha
                cpf_lido[strcspn(cpf_lido, "\n")] = '\0';

                if (strcmp(cpf_lido, cpf_busca) == 0)
                {
                    fclose(fp);
                    return 1;
                }
            }
        }
    }

    fclose(fp);
    return 0;
}
void cadastrarVoluntarioInterativo()
{
    FILE *arquivo = fopen("dados.txt", "r");
    if (!arquivo)
    {
        perror("Erro ao abrir dados.txt");
        return;
    }

    char cpf[20], nome[100], funcao[100], nomeAcao[100];
    
    // Solicita os dados ao usuário
    printf("Digite o CPF do voluntário: ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = '\0'; // Remove quebra de linha
    if(!jaCadastrado(arquivo,cpf)){
        printf("Voluntario não cadastrado!");
        return;
    }

    printf("Digite o nome do voluntário: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Digite a função do voluntário na ação: ");
    fgets(funcao, sizeof(funcao), stdin);
    funcao[strcspn(funcao, "\n")] = '\0';

    printf("Digite o nome da ação: ");
    fgets(nomeAcao, sizeof(nomeAcao), stdin);
    nomeAcao[strcspn(nomeAcao, "\n")] = '\0';

    // Salva os dados no arquivo
    FILE *fp = fopen("listadevoluntarios.txt", "a");
    if (!fp)
    {
        perror("Erro ao abrir listadevoluntarios.txt");
        return;
    }

    fprintf(fp, "CPF:%s | Nome:%s | Funcao:%s | NomeAcao:%s\n", cpf, nome, funcao, nomeAcao);
    fclose(fp);

    printf("\nVoluntário %s cadastrado na ação '%s' como '%s'.\n", nome, nomeAcao, funcao);
}



// Mostra todos os voluntários cadastrados em uma ação específica
void mostrarUsuariosPorAcao()
{
    char nomeAcaoBusca[100];

    // Solicita ao usuário o nome da ação
    printf("Digite o nome da ação que deseja visualizar: ");
    fgets(nomeAcaoBusca, sizeof(nomeAcaoBusca), stdin);
    nomeAcaoBusca[strcspn(nomeAcaoBusca, "\n")] = '\0'; // Remove quebra de linha

    FILE *fp = fopen("listadevoluntarios.txt", "r");
    if (!fp)
    {
        perror("Erro ao abrir listadevoluntarios.txt");
        return;
    }

    char linha[512];
    int encontrados = 0;

    printf("\n Voluntários na ação '%s':\n", nomeAcaoBusca);
    printf("--------------------------------------------------\n");

    while (fgets(linha, sizeof(linha), fp))
    {
        linha[strcspn(linha, "\n")] = '\0';

        // Verifica se a linha contém a ação buscada
        if (strstr(linha, nomeAcaoBusca))
        {
            char nome[100], funcao[100];
            char id[100];

            // Extrai nome e função
            char *ptr_id = strstr(linha,"Id:");
            char *ptr_nome = strstr(linha, "Nome:");
            char *ptr_funcao = strstr(linha, "Funcao:");

            if (ptr_id && ptr_nome && ptr_funcao)
            {
                sscanf(ptr_id, "Id:%[^|]", id);
                sscanf(ptr_nome, "Nome:%[^|]", nome);
                sscanf(ptr_funcao, "Funcao:%[^|]", funcao);
                
                printf("Id: %s\n", id);
                printf("Nome: %s\n", nome);
                printf("Função: %s\n", funcao);
                printf("--------------------------------------------------\n");
                encontrados++;
            }
        }
    }

    fclose(fp);

    if (encontrados == 0)
    {
        printf("Nenhum voluntário encontrado para essa ação.\n");
    }
    else
    {
        printf("Total de voluntários encontrados: %d\n", encontrados);
    }
}
