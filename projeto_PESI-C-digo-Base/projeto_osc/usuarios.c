#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "usuarios.h"
#include "oscs.h" // Para usar somenteNumeros e limparBuffer

// Simulação de gerador de ID (deveria ser persistente)
int gerar_novo_id() {
    // Para simplificar, gera um ID sequencial baseado em um arquivo, se existir
    FILE *fp = fopen("dados.txt", "r");
    int id_counter = 1;
    if (fp) {
        char linha[512];
        while (fgets(linha, sizeof(linha), fp)) {
            // Conta o número de linhas para simular o ID
            id_counter++;
        }
        fclose(fp);
    }
    return id_counter;
}

// Função auxiliar para leitura robusta de string (copiada de oscs.c para garantir o funcionamento)
void lerStringVoluntario(char *buffer, int tamanho, const char *prompt) {
    do {
        printf("%s", prompt);
        if (fgets(buffer, tamanho, stdin) == NULL) {
            buffer[0] = '\0';
            limparBuffer();
            break; 
        }

        if (buffer[strlen(buffer) - 1] != '\n') {
            limparBuffer();
        }
        
        buffer[strcspn(buffer, "\n")] = '\0';
        
        if (strlen(buffer) == 0) {
            printf("Campo vazio, tente novamente!\n");
        }
    } while (strlen(buffer) == 0);
}


int cadastro_voluntario(void)
{
    Voluntario v;

    printf("\n=== CADASTRO DE VOLUNTÁRIO ===\n");

    v.id = gerar_novo_id();
    printf("ID gerado automaticamente: %d\n", v.id);

    lerStringVoluntario(v.nome, TAM_NOME, "Nome: ");

    // Validação de CPF
    do {
        lerStringVoluntario(v.cpf, TAM_CPF, "CPF (11 dígitos): ");

        if (strlen(v.cpf) != 11 || !somenteNumeros(v.cpf)) {
            printf("*CPF inválido. Tente novamente.*\n");
        } else if (jaCadastrado("listadevoluntarios.txt", v.cpf)) { // Verifica em um arquivo específico
            printf("CPF já cadastrado como voluntário!\n");
            return 0;
        }
    } while (strlen(v.cpf) != 11 || !somenteNumeros(v.cpf));

    lerStringVoluntario(v.email, TAM_EMAIL, "Email: ");
    
    // Validação de Telefone
    do {
        lerStringVoluntario(v.telefone, TAM_TELEFONE, "Telefone (máx. 11 dígitos): ");
        if (!somenteNumeros(v.telefone)) {
            printf("*Telefone inválido. Apenas números. Tente novamente.*\n");
        }
    } while (!somenteNumeros(v.telefone));

    lerStringVoluntario(v.cidade, TAM_CIDADE, "Cidade: ");
    lerStringVoluntario(v.area_atuacao, TAM_AREA_ATUACAO, "Área de Atuação (ex: limpeza de praia): ");

    FILE *arquivo = fopen("dados.txt", "a");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return 0;
    }

    // Formato de salvamento (usado para listagem de participantes)
    fprintf(arquivo,
            "Id:%d | Nome:%s | CPF:%s | Email:%s | Telefone:%s | Cidade:%s | AreaAtuacao:%s\n",
            v.id, v.nome, v.cpf, v.email, v.telefone, v.cidade, v.area_atuacao);

    fclose(arquivo);

    printf("\nVoluntário cadastrado com sucesso!\n");
    printf("ID: %d\n", v.id);
    return 1;
}