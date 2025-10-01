#ifndef OSCS_H
#define OSCS_H

#define TAM_NOME 100
#define TAM_CPF 13
#define TAM_CNPJ 16
#define TAM_EMAIL 100
#define TAM_DATA 12
#define TAM_CEP 10
#define TAM_CIDADE 50
#define TAM_BAIRRO 50
#define TAM_RUA 100
#define TAM_NUMERO 10

typedef struct {
    char cidade[TAM_CIDADE];
    char bairro[TAM_BAIRRO];
    char rua[TAM_RUA];
    char numero[TAM_NUMERO];
    char cep[TAM_CEP];
} Endereco;

typedef struct {
    char nome[TAM_NOME];
    char dataNascimento[TAM_DATA];
    char cpf[TAM_CPF];
    char email[TAM_EMAIL];
    Endereco endereco;
} PessoaFisica;

typedef struct {
    char razaoSocial[TAM_NOME];
    char cnpj[TAM_CNPJ];
    char email[TAM_EMAIL];
    Endereco endereco;
} PessoaJuridica;

// Funções de apoio
int somenteNumeros(char *str);
int jaCadastrado(const char *arquivoNome, const char *documento);

// Funções de cadastro
void cadastrarPessoaFisica(const char *arquivoNome);
void cadastrarPessoaJuridica(const char *arquivoNome);

#endif