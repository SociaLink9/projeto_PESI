#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuarios.h"
int cadastro_voluntario()
{
    Voluntario novoVol;
    // A funçao inicia criando uma ficha vazia e atribuindo ao voluntário um novo ID, obtido ao ler o maior ID já presente em *dados.txt*.
    // tipo, ele vai ler o dados.txt e se o maior ID do voluntario for 7, ele vai gerar um novo id "8" para o novo voluntario cadastrado.
    int max_id = 0;
    FILE *f = fopen("dados.txt", "r"); // aqui abre o arquivo para leitura apenas "r"
    if (f != NULL)
    {
        char linha[500];
        while (fgets(linha, sizeof(linha), f))
        { // aqui ele lê uma linha e coloca em linha(igual ao login).
            int id_temp;
            if (sscanf(linha, "%d,", &id_temp) == 1 && id_temp > max_id)
            {                     // O código lê o ID inicial da linha e, se válido e maior que max_id, atualiza o maior ID encontrado.
                max_id = id_temp; //  aqui faz a alteraçao do novo id
            }
        }
        fclose(f);
    }
    novoVol.id = max_id + 1;
    printf("\n=== CADASTRO DE VOLUNTÁRIO ===\n");
    printf("ID gerado automaticamente: %d\n", novoVol.id); // aqui o novo cadastro ja recebe seu proprio ID pela funçaom acima
   do
   {
      printf("Nome: ");
      fgets(novoVol.nome, sizeof(novoVol.nome), stdin);
      novoVol.nome[strcspn(novoVol.nome, "\n")] = 0;
      if (strlen(novoVol.nome) == 0){
        printf("Campo vazio, tente novamente!");
      }
      
   } while (strlen(novoVol.nome) == 0);
  do {
    printf("CPF (11 dígitos): ");
    fgets(novoVol.cpf, sizeof(novoVol.cpf), stdin);
    novoVol.cpf[strcspn(novoVol.cpf, "\n")] = 0;
    if (strlen(novoVol.cpf) == 0 || strlen(novoVol.cpf) > 11) {
        printf("*CPF inválido. Tente novamente.*\n");
    }
} while (strlen(novoVol.cpf) != 10);
    
    do{
    printf("Email: ");
    fgets(novoVol.email,sizeof(novoVol.email),stdin);
    novoVol.email[strcspn(novoVol.email, "\n")] = 0;
    if (strlen(novoVol.email) == 0)
    { // aqui vai verificar se o email estar vazio
        printf("Campo vazio, tente novamente\n");
        
    }
    }while(strlen(novoVol.email) == 0);
    
     do {
        printf("Telefone (11 dígitos): ");
        fgets(novoVol.telefone, 11, stdin);
        novoVol.telefone[strcspn(novoVol.telefone, "\n")] = 0;
        if (strlen(novoVol.telefone) == 0) {
            printf("*Telefone inválido. Tente novamente.*\n");
        }
    } while (strlen(novoVol.telefone) != 10);
   
    do{
    printf("Cidade: ");
    fgets(novoVol.cidade,sizeof(novoVol.cidade),stdin);
    novoVol.cidade[strcspn(novoVol.cidade, "\n")] = 0;
    if(strlen(novoVol.cidade) == 0){
        printf("Campo vazio, tente novamente!\n");
    }
    }while(strlen(novoVol.cidade) == 0);
    
    printf("Área de Atuação (ex: limpeza de praia): ");
    fgets(novoVol.area_atuacao,sizeof(novoVol.area_atuacao),stdin);
    novoVol.area_atuacao[strcspn(novoVol.area_atuacao, "\n")] = 0;
    // Adicionar ao arquivo (modo append)
    FILE *arquivo = fopen("dados.txt", "a"); // "a" = append (adiciona no final)
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return 0;
    }
    /*Escreve todos os dados do voluntário em uma linha no arquivo,
     seguindo o formato: ID,nome,email,CPF,telefone,cidade,área.*/
    fprintf(arquivo, "%d,%s,%s,%s,%s,%s,%s\n",
        novoVol.id, novoVol.nome, novoVol.email,novoVol.cpf,novoVol.telefone, novoVol.cidade, novoVol.area_atuacao);
    if (fclose(arquivo) != 0)
    {
        printf("Erro ao fechar o arquivo!\n");
        return 0;
    }
    printf("Voluntário cadastrado com sucesso! ID: %d\n", novoVol.id);
    return 1; // Sucesso
}