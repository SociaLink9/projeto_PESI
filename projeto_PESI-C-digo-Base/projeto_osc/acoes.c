#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "acoes.h"
#include "usuarios.h"
#include "oscs.h"

// Define o tamanho máximo de um campo em listadevoluntarios.txt
#define TAM_CAMPO 100
#define MAX_LINHA 512

void lerTodasAcoes()
{
    FILE *arquivoNome = fopen("listadeacoes.txt", "r");
    char linha[MAX_LINHA];

    if (!arquivoNome)
    {
        printf("Não foi possível abrir o arquivo.\n");
        return;
    }

    printf("\nAções cadastradas:\n");
    while (fgets(linha, sizeof(linha), arquivoNome))
    {
        // Assume que o arquivo já contém quebras de linha no formato correto
        printf("%s", linha);
    }

    fclose(arquivoNome);
}

// Função auxiliar para leitura robusta de string (garante limpeza do buffer)
void lerStringAcoes(char *buffer, int tamanho, const char *prompt)
{
    do
    {
        printf("%s", prompt);
        if (fgets(buffer, tamanho, stdin) == NULL)
        {
            buffer[0] = '\0';
            limparBuffer();
            break;
        }

        if (buffer[strlen(buffer) - 1] != '\n')
        {
            limparBuffer();
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        if (strlen(buffer) == 0)
        {
            printf("Campo vazio, tente novamente!\n");
        }
    } while (strlen(buffer) == 0);
}

void cadastrarVoluntarioInterativo()
{
    char cpf[TAM_CPF], nome[TAM_NOME], funcao[TAM_NOME], nomeAcao[TAM_NOME];

    // 1. Solicita e valida o CPF (contra o arquivo de voluntários)
    lerStringAcoes(cpf, TAM_CPF, "Digite o CPF do voluntário: ");

    
    if (jaCadastrado("dados.txt", cpf))
    {
        printf("Voluntário não cadastrado! Por favor, cadastre o usuário (Opção 2) antes de inscrevê-lo em uma ação.\n");
        return;
    }

    // 2. Coleta os demais dados
    lerStringAcoes(nome, TAM_NOME, "Digite o nome do voluntário: ");
    lerStringAcoes(funcao, TAM_NOME, "Digite a função do voluntário na ação: ");
    lerStringAcoes(nomeAcao, TAM_NOME, "Digite o nome da ação: ");

    // 3. Salva os dados no arquivo
    FILE *fp = fopen("listadevoluntarios.txt", "a");
    if (!fp)
    {
        perror("Erro ao abrir listadevoluntarios.txt");
        return;
    }

    // Salva o CPF como identificador, pois o ID não foi persistido aqui
    fprintf(fp, "CPF:%s | Nome:%s | Funcao:%s | NomeAcao:%s\n", cpf, nome, funcao, nomeAcao);
    fclose(fp);

    printf("\nVoluntário %s cadastrado na ação '%s' como '%s'.\n", nome, nomeAcao, funcao);
}

// Mostra todos os voluntários cadastrados em uma ação específica
void mostrarUsuariosPorAcao()
{
    char nomeAcaoBusca[TAM_NOME];

    // Solicita ao usuário o nome da ação
    lerStringAcoes(nomeAcaoBusca, TAM_NOME, "Digite o nome da ação que deseja visualizar: ");

    FILE *fp = fopen("listadevoluntarios.txt", "r");
    if (!fp)
    {
        perror("Erro ao abrir listadevoluntarios.txt");
        return;
    }

    char linha[MAX_LINHA];
    int encontrados = 0;

    printf("\n Voluntários na ação '%s':\n", nomeAcaoBusca);
    printf("--------------------------------------------------\n");

    while (fgets(linha, sizeof(linha), fp))
    {
        linha[strcspn(linha, "\n")] = '\0';

        // Verifica se a linha contém a ação buscada
        if (strstr(linha, nomeAcaoBusca))
        {
            char cpf[TAM_CPF], nome[TAM_NOME], funcao[TAM_NOME];

            // Posições de início dos campos (para usar sscanf de forma segura)
            char *ptr_cpf = strstr(linha, "CPF:");
            char *ptr_nome = strstr(linha, "Nome:");
            char *ptr_funcao = strstr(linha, "Funcao:");

            if (ptr_cpf && ptr_nome && ptr_funcao)
            {
                // Note: sscanf com [^|] é usado para ler até o próximo '|'
                // A leitura é feita a partir dos ponteiros encontrados
                sscanf(ptr_cpf, "CPF:%[^|]", cpf);
                sscanf(ptr_nome, "Nome:%[^|]", nome);
                sscanf(ptr_funcao, "Funcao:%[^|]", funcao);

                // Formata a saída, removendo espaços iniciais que podem ter sido lidos
                // (O formato de salvamento com espaços ao redor do '|' deve ser mantido)
                printf("CPF: %s\n", cpf);
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