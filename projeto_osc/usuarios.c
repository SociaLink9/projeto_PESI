#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuarios.h"

int fazerLogin(const char* email, const char* senha) {
    FILE* arquivo = fopen("dados.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura!\n");
        return 0;
    }

    char linha[500];  // declara  variavel "linha" para salvar uma linha inteira do arquivo "dados.txt"
    while (fgets(linha, sizeof(linha), arquivo)) { /* fgets é uma funçao quer vai ler linha 
                                                    por linha e a mesma coloca na variavel "linha" criada. */
        /* abaixo sao as variaveis temporarias criadas para analisar as linhas do arquivo e consequetemente fazer a comparaçao abaixo do
        email e senha do usuario para login */
        int id_temp;
        char nome_temp[100], email_temp[100], senha_temp[50];
        char telefone_temp[20], cidade_temp[50], area_temp[50];
        int idade_temp;
          
        // Abaixo o sscanf vai ler as linhas dos arquivo e vai preencher as variaveis de a cordo com o formato
        if (sscanf(linha, "%d,%99[^,],%99[^,],%49[^,],%19[^,],%49[^,],%d,%49[^\n]",/* %99[^,] lê até 99 caracteres, qualquer coisa exceto vírgula. 
                                                                                    quando chegar  na virgula ele para e vai pra outra informação dps da virgula.*/

                   &id_temp, nome_temp, email_temp, senha_temp,
                   telefone_temp, cidade_temp, &idade_temp, area_temp) == 8) {// sscanf verifica se ele leu exatamente 8 campos . Se sim (==8), entra no bloco { }. 
            if (strcmp(email_temp, email) == 0 && strcmp(senha_temp, senha) == 0) {/* strcmp é uma Função que compara duas strings, email_temp que foi lido do arquivo (dados.txt) 
                                                                                 e o email vindo do usuario. se for == 0 ai deu certo o login*/ 
                                                                                 //assim vale a mesma coisa para a senha
                fclose(arquivo);
                return 1;  // Login bem-sucedido
            }
        }
    }

    fclose(arquivo);
    return 0;  // Não encontrado
}

int cadastro_voluntario() {
    Voluntario novoVol;
    
    // A funçao inicia criando uma ficha vazia e atribuindo ao voluntário um novo ID, obtido ao ler o maior ID já presente em *dados.txt*.
    // tipo, ele vai ler o dados.txt e se o maior ID do voluntario for 7, ele vai gerar um novo id "8" para o novo voluntario cadastrado.

    int max_id = 0;
    FILE* f = fopen("dados.txt", "r"); // aqui abre o arquivo para leitura apenas "r"
    if (f != NULL) {
        char linha[500];
        while (fgets(linha, sizeof(linha), f)) { // aqui ele lê uma linha e coloca em linha(igual ao login).
            int id_temp;
            if (sscanf(linha, "%d,", &id_temp) == 1 && id_temp > max_id) { //O código lê o ID inicial da linha e, se válido e maior que max_id, atualiza o maior ID encontrado.
                max_id = id_temp; //  aqui faz a alteraçao do novo id
            }
        }
        fclose(f);
    }
    novoVol.id = max_id + 1;
    
    printf("\n=== CADASTRO DE VOLUNTÁRIO ===\n");
    printf("ID gerado automaticamente: %d\n", novoVol.id); // aqui o novo cadastro ja recebe seu proprio ID pela funçaom acima

    printf("Nome: ");
    scanf(" %99[^\n]", novoVol.nome);  // Lê string com espaços (José antonio)

    printf("Email: ");
    scanf(" %99s", novoVol.email);  // %s para email sem espaços (unibra@gmail.comm)
    if (strlen(novoVol.email) == 0) { // aqui vai verificar se o email estar vazio 
        printf("Email não pode ser vazio!\n");
        return 0;  // Falha no cadastro
    }

    printf("Senha: ");
    scanf(" %49s", novoVol.senha);
    if (strlen(novoVol.senha) == 0) { // aqui vai verificar se a senha estar vazia
        printf("Senha não pode ser vazia!\n");
        return 0;
    }

    printf("Telefone: ");
    scanf(" %19s", novoVol.telefone);  // %s para telefone (assume sem espaços)

    printf("Cidade: ");
    scanf(" %49[^\n]", novoVol.cidade);  // [^\n] Lê com espaços (ex: "São Paulo")

    printf("Idade: ");
    scanf("%d", &novoVol.idade);
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer de entrada após scanf da idade
    
    if (novoVol.idade < 0 || novoVol.idade > 150) {
        printf("Idade inválida!\n");
        return 0;
    }

    printf("Área de Atuação (ex: limpeza de praia): ");
    scanf(" %49[^\n]", novoVol.area_atuacao);  // Lê com espaços

    // Adicionar ao arquivo (modo append)
    FILE* arquivo = fopen("dados.txt", "a");  // "a" = append (adiciona no final)
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return 0;
    }

     /*Escreve todos os dados do voluntário em uma linha no arquivo,
      seguindo o formato: ID,nome,email,senha,telefone,cidade,idade,área.*/

    fprintf(arquivo, "%d,%s,%s,%s,%s,%s,%d,%s\n",
            novoVol.id, novoVol.nome, novoVol.email, novoVol.senha,
            novoVol.telefone, novoVol.cidade, novoVol.idade, novoVol.area_atuacao);

    if (fclose(arquivo) != 0) {
        printf("Erro ao fechar o arquivo!\n");
        return 0;
    }
    
    printf("Voluntário cadastrado com sucesso! ID: %d\n", novoVol.id);
    return 1;  // Sucesso
}

int main() {
    int opcao;
    char email[100];
    char senha[50];
    
    printf("=== SISTEMA DE VOLUNTÁRIOS ===\n");
    printf("1 - Cadastrar Voluntário\n");
    printf("2 - Fazer Login\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    
    // Limpa buffer após scanf de int
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    if (opcao == 1) {
        if (cadastro_voluntario()) {
            printf("Cadastro concluído. Você pode agora fazer login.\n");
        } else {
            printf("Falha no cadastro.\n");
        }
    } else if (opcao == 2) {
        printf("Digite seu email: ");
        scanf(" %99s", email);
        // Limpa buffer
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Digite sua senha: ");
        scanf(" %49s", senha);
        // Limpa buffer
        while ((c = getchar()) != '\n' && c != EOF);
        
        if (fazerLogin(email, senha)) {
            printf("Acesso concedido.\n");
        } else {
            printf("Acesso negado. Verifique email e senha.\n");
        }
    } else {
        printf("Opção inválida!\n");
    }

    return 0;
}
