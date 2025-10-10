#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>

#define MAX_NOME 100
#define MAX_LINHA 512

// ========== Funções utilitárias ==========
void removeNewline(char *str) {
    str[strcspn(str, "\n")] = 0;
}

// ========== Novas funções estáticas ==========
void sobreNos() {
    system("cls"); // use "clear" no Linux/macOS
    printf("\n--- Sobre Nós ---\n");
    printf("Somos uma plataforma voltada ao engajamento social.\n");
    printf("Conectamos pessoas, ideias e causas para um mundo melhor.\n");
}

void equipe() {
    system("cls");
    printf("\n--- Equipe ---\n");
    printf("1. Breno Feitosa Bandeira de Abreu\n");
    printf("2. Gabriel Albuquerque Nascimento de Oliveira\n");
    printf("3. Luan Santos Alves Pequeno Da Silva\n");
    printf("4. Pedro Caio Francisco da Silva\n");
    printf("5. David Richard Lima de Souza\n");
    printf("6. João Vitor Santos Silva\n");
    printf("7. Vinicius da Silva Ramos\n");
    printf("8. Yago Vinicius de Freitas Silva\n");
    printf("9. Geovane Alves da Silva Filho\n");
    printf("10. Gabriela Torres Guerra da Fonte\n");
    printf("11. Guilherme Morais Cavalcante\n");
}

void contato() {
    system("cls");
    printf("\n--- Contato ---\n");
    printf("Email: secretaria@grupounibra.com\n");
    printf("Telefone: 81 3036-0001\n");
    printf("Endereço: Rua Padre Inglês, 257, R. Padre Inglês, 356 - Boa Vista, Recife - PE, 50050-230\n");
}

// ========== Funções de cadastro e listagem ==========
void cadastrarPessoaFisica(const char *arquivo) {
    char nome[MAX_NOME], cpf[15], dataNascimento[12], telefone[20], email[100];
    printf("Cadastro Pessoa Física:\n");
    printf("Nome: ");
    fgets(nome, MAX_NOME, stdin);
    removeNewline(nome);

    printf("CPF: ");
    fgets(cpf, 15, stdin);
    removeNewline(cpf);

    printf("Data de nascimento (dd/mm/aaaa): ");
    fgets(dataNascimento, 12, stdin);
    removeNewline(dataNascimento);

    printf("Telefone: ");
    fgets(telefone, 20, stdin);
    removeNewline(telefone);

    printf("E-mail: ");
    fgets(email, 100, stdin);
    removeNewline(email);

    FILE *fp = fopen(arquivo, "a");
    if (!fp) {
        printf("Erro ao abrir arquivo para salvar.\n");
        return;
    }

    fprintf(fp, "PF;%s;%s;%s;%s;%s\n", nome, cpf, dataNascimento, telefone, email);
    fclose(fp);

    printf("Pessoa física cadastrada com sucesso!\n");
}

void cadastrarPessoaJuridica(const char *arquivo) {
    char nome[MAX_NOME], cnpj[20], endereco[150], telefone[20], email[100];
    printf("Cadastro Pessoa Jurídica (OSC):\n");
    printf("Nome da empresa: ");
    fgets(nome, MAX_NOME, stdin);
    removeNewline(nome);

    printf("CNPJ: ");
    fgets(cnpj, 20, stdin);
    removeNewline(cnpj);

    printf("Endereço: ");
    fgets(endereco, 150, stdin);
    removeNewline(endereco);

    printf("Telefone: ");
    fgets(telefone, 20, stdin);
    removeNewline(telefone);

    printf("E-mail: ");
    fgets(email, 100, stdin);
    removeNewline(email);

    FILE *fp = fopen(arquivo, "a");
    if (!fp) {
        printf("Erro ao abrir arquivo para salvar.\n");
        return;
    }

    fprintf(fp, "PJ;%s;%s;%s;%s;%s\n", nome, cnpj, endereco, telefone, email);
    fclose(fp);

    printf("Pessoa jurídica cadastrada com sucesso!\n");
}

void cadastrarVoluntarioInterativo(void) {
    char nomeUsuario[MAX_NOME], nomeAcao[MAX_NOME];
    printf("Inscrição de Usuário em Ação:\n");

    printf("Nome do usuário: ");
    fgets(nomeUsuario, MAX_NOME, stdin);
    removeNewline(nomeUsuario);

    printf("Nome da ação: ");
    fgets(nomeAcao, MAX_NOME, stdin);
    removeNewline(nomeAcao);

    FILE *fp = fopen("inscricoes.txt", "a");
    if (!fp) {
        printf("Erro ao abrir arquivo para salvar inscrição.\n");
        return;
    }

    fprintf(fp, "%s;%s\n", nomeUsuario, nomeAcao);
    fclose(fp);

    printf("Inscrição realizada com sucesso!\n");
}

void lerTodasAcoes(const char *arquivo) {
    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        printf("Nenhuma ação cadastrada.\n");
        return;
    }

    char linha[MAX_LINHA];
    printf("Lista de Ações:\n");
    while (fgets(linha, sizeof(linha), fp)) {
        char nome[MAX_NOME], descricao[256], data[12], local[MAX_NOME];
        sscanf(linha, "%[^;];%[^;];%[^;];%[^\n]", nome, descricao, data, local);
        printf("\nNome: %s\nDescrição: %s\nData: %s\nLocal: %s\n", nome, descricao, data, local);
    }
    fclose(fp);
}

// ========== Logotipo ==========
void mostrarLogo(void) {
    printf(".====================================================================.\n");
    printf("!                                                                    !\n");
    printf("!   |||||||  ||||||  ||||||  ||  |||||  ||      || ||||   || ||   || !\n");
    printf("!   ||      ||    || ||      || ||   || ||      || || ||  || ||  ||  !\n");
    printf("!   ||||||| ||    || ||      || ||||||| ||      || ||  || || || ||   !\n");
    printf("!        || ||    || ||      || ||   || ||      || ||   |||| ||  ||  !\n");
    printf("!   |||||||  ||||||  ||||||  || ||   || ||||||| || ||    ||| ||   || !\n");
    printf("!                                                                    !\n");
    printf("!   Plataforma de Engajamento Social Integrado (P.E.S.I.)            !\n");
    printf("!   Bem-vindo à transformação digital do engajamento!                !\n");
    printf("!   Conectando ideias, pessoas e propósitos com inteligência.        !\n");
    printf(".====================================================================.\n");
}

// ========== Função principal ==========
int main() {
    system("chcp 65001"); 
    setlocale(LC_ALL, "pt_BR.UTF-8");

    const char *arquivoPessoas = "dados.txt";
    const char *arquivoAcoes = "acoes.txt";

    int selecao;
    bool cont = true;

    mostrarLogo();

    do {
        printf("\n========= Menu Principal =========\n");
        printf("1. Sobre nós\n");
        printf("2. Equipe\n");
        printf("3. Cadastro pessoa física\n");
        printf("4. Cadastro pessoa jurídica\n");
        printf("5. Inscrição de usuários em ação\n");
        printf("6. Listagem de ações\n");
        printf("7. Contato\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &selecao);
        getchar(); // Captura o Enter

        switch (selecao) {
            case 1:
                sobreNos();
                break;
            case 2:
                equipe();
                break;
            case 3:
                cadastrarPessoaFisica(arquivoPessoas);
                break;
            case 4:
                cadastrarPessoaJuridica(arquivoPessoas);
                break;
            case 5:
                cadastrarVoluntarioInterativo();
                break;
            case 6:
                lerTodasAcoes(arquivoAcoes);
                break;
            case 7:
                contato();
                break;
            case 0:
                cont = false;
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (cont);

    printf("\nObrigado por utilizar o P.E.S.I.!\n");
    return 0;
}
