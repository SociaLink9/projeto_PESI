#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "oscs.h"

// ======= FUNÇÕES DE APOIO =======
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
        if (strstr(linha, documento) != NULL)
        {
            fclose(arq);
            return 1;
        }
    }
    fclose(arq);
    return 0;
}

// ======= CADASTROS =======
void cadastrarPessoaFisica(const char *arquivoNome)
{
    PessoaFisica pf;

    printf("\n--- Cadastro de Pessoa Fisica ---\n");
    printf("Nome: ");
    fgets(pf.nome, TAM_NOME, stdin);
    pf.nome[strcspn(pf.nome, "\n")] = 0;

    printf("Data de nascimento (dd/mm/aaaa): ");
    fgets(pf.dataNascimento, TAM_DATA, stdin);
    pf.dataNascimento[strcspn(pf.dataNascimento, "\n")] = 0;

    do
    {
        printf("CPF (11 dígitos, apenas números): ");
        fgets(pf.cpf, TAM_CPF, stdin);
        pf.cpf[strcspn(pf.cpf, "\n")] = 0;

        // limpa excesso de caracteres
        if (strlen(pf.cpf) == TAM_CPF - 1 && pf.cpf[TAM_CPF - 2] != '\0')
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        }

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

    printf("Email: ");
    fgets(pf.email, TAM_EMAIL, stdin);
    pf.email[strcspn(pf.email, "\n")] = 0;

    printf("\n--- Endereço ---\n");
    printf("Cidade: ");
    fgets(pf.endereco.cidade, TAM_CIDADE, stdin);
    pf.endereco.cidade[strcspn(pf.endereco.cidade, "\n")] = 0;

    printf("Bairro: ");
    fgets(pf.endereco.bairro, TAM_BAIRRO, stdin);
    pf.endereco.bairro[strcspn(pf.endereco.bairro, "\n")] = 0;

    printf("Rua: ");
    fgets(pf.endereco.rua, TAM_RUA, stdin);
    pf.endereco.rua[strcspn(pf.endereco.rua, "\n")] = 0;

    printf("Número: ");
    fgets(pf.endereco.numero, TAM_NUMERO, stdin);
    pf.endereco.numero[strcspn(pf.endereco.numero, "\n")] = 0;

    printf("CEP: ");
    fgets(pf.endereco.cep, TAM_CEP, stdin);
    pf.endereco.cep[strcspn(pf.endereco.cep, "\n")] = 0;

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
    printf("Razão Social: ");
    fgets(pj.razaoSocial, TAM_NOME, stdin);
    pj.razaoSocial[strcspn(pj.razaoSocial, "\n")] = 0;

    do
    {
        printf("CNPJ (14 dígitos, apenas números): ");
        fgets(pj.cnpj, TAM_CNPJ, stdin);
        pj.cnpj[strcspn(pj.cnpj, "\n")] = 0;

        // limpa excesso de caracteres
        if (strlen(pj.cnpj) == TAM_CNPJ - 1 && pj.cnpj[TAM_CNPJ - 2] != '\0')
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        }

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

    printf("Email: ");
    fgets(pj.email, TAM_EMAIL, stdin);
    pj.email[strcspn(pj.email, "\n")] = 0;

    printf("\n--- Endereço da Empresa ---\n");
    printf("Cidade: ");
    fgets(pj.endereco.cidade, TAM_CIDADE, stdin);
    pj.endereco.cidade[strcspn(pj.endereco.cidade, "\n")] = 0;

    printf("Bairro: ");
    fgets(pj.endereco.bairro, TAM_BAIRRO, stdin);
    pj.endereco.bairro[strcspn(pj.endereco.bairro, "\n")] = 0;

    printf("Rua: ");
    fgets(pj.endereco.rua, TAM_RUA, stdin);
    pj.endereco.rua[strcspn(pj.endereco.rua, "\n")] = 0;

    printf("Número: ");
    fgets(pj.endereco.numero, TAM_NUMERO, stdin);
    pj.endereco.numero[strcspn(pj.endereco.numero, "\n")] = 0;

    printf("CEP: ");
    fgets(pj.endereco.cep, TAM_CEP, stdin);
    pj.endereco.cep[strcspn(pj.endereco.cep, "\n")] = 0;

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

// ======= PROBLEMA NA FUNÇÃO ABAIXO =======
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
        return 0;

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

    printf("Digite seu CPF ou CNPJ: ");
    fgets(NovaAc.cpf_cnpj, sizeof(NovaAc.cpf_cnpj), stdin);
    NovaAc.cpf_cnpj[strcspn(NovaAc.cpf_cnpj, "\n")] = 0;
    getchar();

    if (!verificarCadastro(NovaAc.cpf_cnpj))
    {
        printf("Cadastro não encontrado. Apenas PF ou PJ registrados podem cadastrar ações.\n");
        return;
    }

    printf("Nome da ação: ");
    fgets(NovaAc.nomeAcao, sizeof(NovaAc.nomeAcao), stdin);
    NovaAc.nomeAcao[strcspn(NovaAc.nomeAcao, "\n")] = 0;
    

    printf("Local da ação: ");
    fgets(NovaAc.localAcao, sizeof(NovaAc.localAcao), stdin);
    NovaAc.localAcao[strcspn(NovaAc.localAcao, "\n")] = 0;
    

    printf("Descrição da ação: ");
    fgets(NovaAc.descricao, sizeof(NovaAc.descricao), stdin);
    NovaAc.descricao[strcspn(NovaAc.descricao, "\n")] = 0;
   

    FILE *arquivo = fopen("dados.txt", "a");
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
