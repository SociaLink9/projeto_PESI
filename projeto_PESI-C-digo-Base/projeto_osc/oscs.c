#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "oscs.h"

// ======= FUNÇÕES DE APOIO =======

// Limpa o buffer de entrada lendo até o '\n' ou EOF
void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int somenteNumeros(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
        {
            return 0;
        }
    }
    return 1;
}

// Verifica se documento já existe
int jaCadastrado(const char *arquivoNome, const char *documento)
{
    FILE *arq = fopen(arquivoNome, "r");
    if (arq == NULL)
    {
        return 0;
    }

    char linha[500];
    while (fgets(linha, sizeof(linha), arq))
    {
        // Usa o formato de salvamento (ex: "CPF: XXXXX") para busca precisa
        char busca[30];
        if (strlen(documento) == 11)
            sprintf(busca, "CPF: %s", documento);
        else if (strlen(documento) == 14)
            sprintf(busca, "CNPJ: %s", documento);
        else
            continue; // Documento inválido

        if (strstr(linha, busca) != NULL)
        {
            fclose(arq);
            return 1;
        }
    }
    fclose(arq);
    return 0;
}

// Função auxiliar para leitura robusta de string
void lerString(char *buffer, int tamanho, const char *prompt) {
    do {
        printf("%s", prompt);
        if (fgets(buffer, tamanho, stdin) == NULL) {
            // Em caso de erro de leitura
            buffer[0] = '\0';
            break; 
        }

        // Verifica se o buffer está cheio e o '\n' não foi lido (input muito longo)
        if (buffer[strlen(buffer) - 1] != '\n') {
            limparBuffer();
            if (strlen(buffer) == tamanho - 1) {
                // A entrada foi truncada, mas o buffer está limpo para a próxima iteração
                printf("Entrada muito longa! Tente novamente.\n");
            }
        }
        
        // Remove a quebra de linha
        buffer[strcspn(buffer, "\n")] = '\0';
        
        if (strlen(buffer) == 0) {
            printf("*Campo não pode estar vazio. Tente novamente.*\n");
        }
    } while (strlen(buffer) == 0);
}


// ======= CADASTROS =======
void cadastrarPessoaFisica(const char *arquivoNome)
{
    PessoaFisica pf;

    printf("\n--- Cadastro de Pessoa Fisica ---\n");
    lerString(pf.nome, TAM_NOME, "Nome: ");
    lerString(pf.dataNascimento, TAM_DATA, "Data de nascimento (dd/mm/aaaa): ");

    // CPF com validação
    do
    {
        printf("CPF (11 dígitos, apenas números): ");
        if (fgets(pf.cpf, TAM_CPF, stdin) == NULL) {
            pf.cpf[0] = '\0';
            limparBuffer();
            break;
        }
        if (pf.cpf[strlen(pf.cpf) - 1] != '\n') {
            limparBuffer();
        }
        pf.cpf[strcspn(pf.cpf, "\n")] = 0;

        if (strlen(pf.cpf) != 11 || !somenteNumeros(pf.cpf))
        {
            printf("CPF inválido! Tente novamente.\n");
        }
        else if (jaCadastrado(arquivoNome, pf.cpf))
        {
            printf("CPF já cadastrado no sistema!\n");
            return;
        }
    } while (strlen(pf.cpf) != 11 || !somenteNumeros(pf.cpf));
    
    // Se o CPF não foi preenchido (erro ou EOF), retorna
    if (strlen(pf.cpf) == 0) return;

    lerString(pf.email, TAM_EMAIL, "Email: ");

    printf("\n--- Endereço ---\n");
    lerString(pf.endereco.cidade, TAM_CIDADE, "Cidade: ");
    lerString(pf.endereco.bairro, TAM_BAIRRO, "Bairro: ");
    lerString(pf.endereco.rua, TAM_RUA, "Rua: ");
    lerString(pf.endereco.numero, TAM_NUMERO, "Número: ");
    lerString(pf.endereco.cep, TAM_CEP, "CEP: ");

    FILE *arquivo = fopen(arquivoNome, "a");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    fprintf(arquivo,
            "Pessoa Fisica | Nome: %s | Data Nasc.: %s | CPF: %s | Email: %s | "
            "Endereco: %s, %s, %s, Nº %s, CEP %s\n",
            pf.nome, pf.dataNascimento, pf.cpf, pf.email,
            pf.endereco.cidade, pf.endereco.bairro, pf.endereco.rua,
            pf.endereco.numero, pf.endereco.cep);

    fclose(arquivo);
    printf("? Cadastro realizado com sucesso!\n");
}

void cadastrarPessoaJuridica(const char *arquivoNome)
{
    PessoaJuridica pj;

    printf("\n--- Cadastro de Pessoa Juridica ---\n");
    lerString(pj.razaoSocial, TAM_NOME, "Razão Social: ");

    // CNPJ com validação
    do
    {
        printf("CNPJ (14 dígitos, apenas números): ");
        if (fgets(pj.cnpj, TAM_CNPJ, stdin) == NULL) {
            pj.cnpj[0] = '\0';
            limparBuffer();
            break;
        }
        if (pj.cnpj[strlen(pj.cnpj) - 1] != '\n') {
            limparBuffer();
        }
        pj.cnpj[strcspn(pj.cnpj, "\n")] = 0;

        if (strlen(pj.cnpj) != 14 || !somenteNumeros(pj.cnpj))
        {
            printf("CNPJ inválido! Tente novamente.\n");
        }
        else if (jaCadastrado(arquivoNome, pj.cnpj))
        {
            printf("CNPJ já cadastrado no sistema!\n");
            return;
        }
    } while (strlen(pj.cnpj) != 14 || !somenteNumeros(pj.cnpj));
    
    if (strlen(pj.cnpj) == 0) return;

    lerString(pj.email, TAM_EMAIL, "Email: ");

    printf("\n--- Endereço da Empresa ---\n");
    lerString(pj.endereco.cidade, TAM_CIDADE, "Cidade: ");
    lerString(pj.endereco.bairro, TAM_BAIRRO, "Bairro: ");
    lerString(pj.endereco.rua, TAM_RUA, "Rua: ");
    lerString(pj.endereco.numero, TAM_NUMERO, "Número: ");
    lerString(pj.endereco.cep, TAM_CEP, "CEP: ");
    
    FILE *arquivo = fopen(arquivoNome, "a");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    fprintf(arquivo,
            "Pessoa Juridica | Razao Social: %s | CNPJ: %s | Email: %s | "
            "Endereco: %s, %s, %s, Nº %s, CEP %s\n",
            pj.razaoSocial, pj.cnpj, pj.email,
            pj.endereco.cidade, pj.endereco.bairro, pj.endereco.rua,
            pj.endereco.numero, pj.endereco.cep);

    fclose(arquivo);
    printf("? Cadastro realizado com sucesso!\n");
}

// Verifica se PF/PJ já tem cadastro
int verificarCadastro(const char *cpf_cnpj)
{
    FILE *arquivo = fopen("dados.txt", "r");
    if (!arquivo)
    {
        printf("Erro ao abrir o arquivo de cadastros.\n");
        return 0;
    }
    char linha[500];
    char busca[30];

    // Monta a string de busca
    if (strlen(cpf_cnpj) == 11)
        sprintf(busca, "CPF: %s", cpf_cnpj);
    else if (strlen(cpf_cnpj) == 14)
        sprintf(busca, "CNPJ: %s", cpf_cnpj);
    else
    {
        fclose(arquivo);
        return 0;
    }

    while (fgets(linha, sizeof(linha), arquivo))
    {
        if (strstr(linha, busca))
        {
            fclose(arquivo);
            return 1;
        }
    }
    fclose(arquivo);
    return 0;
}

void cadastrarAcao()
{
    NovaAcao NovaAc;
    
    // Leitura e validação de CPF/CNPJ
    do
    {
        printf("Digite seu CPF ou CNPJ: ");
        if (fgets(NovaAc.cpf_cnpj, sizeof(NovaAc.cpf_cnpj), stdin) == NULL) {
            NovaAc.cpf_cnpj[0] = '\0';
            limparBuffer();
            break;
        }
        if (NovaAc.cpf_cnpj[strlen(NovaAc.cpf_cnpj) - 1] != '\n') {
            limparBuffer();
        }
        NovaAc.cpf_cnpj[strcspn(NovaAc.cpf_cnpj, "\n")] = 0;
        
        if (strlen(NovaAc.cpf_cnpj) == 0) {
             printf("Campo vazio, tente novamente!\n");
        } else if (strlen(NovaAc.cpf_cnpj) != 11 && strlen(NovaAc.cpf_cnpj) != 14) {
            printf("CPF/CNPJ com tamanho inválido. Tente novamente!\n");
        } else if (!somenteNumeros(NovaAc.cpf_cnpj)) {
            printf("CPF/CNPJ deve conter apenas números. Tente novamente!\n");
        }
        
    } while (strlen(NovaAc.cpf_cnpj) == 0 || (strlen(NovaAc.cpf_cnpj) != 11 && strlen(NovaAc.cpf_cnpj) != 14) || !somenteNumeros(NovaAc.cpf_cnpj));
    
    if (strlen(NovaAc.cpf_cnpj) == 0) return;

    if (!verificarCadastro(NovaAc.cpf_cnpj))
    {
        printf("Cadastro não encontrado. Apenas PF ou PJ registrados podem cadastrar ações.\n");
        return;
    }

    lerString(NovaAc.nomeAcao, TAM_NOME, "Nome da ação: ");
    lerString(NovaAc.localAcao, TAM_CIDADE, "Local da ação: ");
    lerString(NovaAc.descricao, MAX, "Descrição da ação: ");

    FILE *arquivo = fopen("listadeacoes.txt", "a");
    if (!arquivo)
    {
        printf("Erro ao salvar a ação.\n");
        return;
    }

    fprintf(arquivo, "CPF/CNPJAcao: %s\nNomeAcao: %s\nLocalAcao: %s\nDescriçãoAcao: %s\n---\n",
            NovaAc.cpf_cnpj, NovaAc.nomeAcao, NovaAc.localAcao, NovaAc.descricao);
    fclose(arquivo);

    printf("Ação cadastrada com sucesso!\n");

    return;
}