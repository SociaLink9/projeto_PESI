#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>

#define MAX_NOME 100
#define MAX_LINHA 512

// Remove \n do final da string
void removeNewline(char *str) {
    str[strcspn(str, "\n")] = 0;
}

// ========== Funções para cadastro, listagem e interação =========

// Funções de cadastro para pessoas físicas e jurídicas
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

// Cadastro voluntário simplificado para exemplo
void cadastro_voluntario(void) {
    char nome[MAX_NOME], telefone[20], email[100];
    printf("Cadastro de Voluntário:\n");
    printf("Nome: ");
    fgets(nome, MAX_NOME, stdin);
    removeNewline(nome);

    printf("Telefone: ");
    fgets(telefone, 20, stdin);
    removeNewline(telefone);

    printf("E-mail: ");
    fgets(email, 100, stdin);
    removeNewline(email);

    FILE *fp = fopen("voluntarios.txt", "a");
    if (!fp) {
        printf("Erro ao abrir arquivo para salvar voluntário.\n");
        return;
    }

    fprintf(fp, "%s;%s;%s\n", nome, telefone, email);
    fclose(fp);

    printf("Voluntário cadastrado com sucesso!\n");
}

// Cadastro de ação
void cadastrarAcao(void) {
    char nome[MAX_NOME], descricao[256], data[12], local[MAX_NOME];
    printf("Cadastro de Ação:\n");
    printf("Nome da ação: ");
    fgets(nome, MAX_NOME, stdin);
    removeNewline(nome);

    printf("Descrição: ");
    fgets(descricao, 256, stdin);
    removeNewline(descricao);

    printf("Data (dd/mm/aaaa): ");
    fgets(data, 12, stdin);
    removeNewline(data);

    printf("Local: ");
    fgets(local, MAX_NOME, stdin);
    removeNewline(local);

    FILE *fp = fopen("acoes.txt", "a");
    if (!fp) {
        printf("Erro ao abrir arquivo para salvar ação.\n");
        return;
    }

    fprintf(fp, "%s;%s;%s;%s\n", nome, descricao, data, local);
    fclose(fp);

    printf("Ação cadastrada com sucesso!\n");
}

// Listar todas as ações
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

// Inscrever usuário em ação
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

// Mostrar usuários inscritos por ação
void mostrarUsuariosPorAcao(void) {
    char nomeAcao[MAX_NOME];
    printf("Visualização de Participantes por Ação:\n");
    printf("Digite o nome da ação: ");
    fgets(nomeAcao, MAX_NOME, stdin);
    removeNewline(nomeAcao);

    FILE *fp = fopen("inscricoes.txt", "r");
    if (!fp) {
        printf("Nenhuma inscrição encontrada.\n");
        return;
    }

    char linha[MAX_LINHA];
    bool encontrou = false;
    printf("Usuários inscritos na ação \"%s\":\n", nomeAcao);

    while (fgets(linha, sizeof(linha), fp)) {
        char usuario[MAX_NOME], acao[MAX_NOME];
        sscanf(linha, "%[^;];%[^\n]", usuario, acao);

        if (strcmp(acao, nomeAcao) == 0) {
            printf("- %s\n", usuario);
            encontrou = true;
        }
    }

    if (!encontrou) printf("Nenhum usuário inscrito nessa ação.\n");

    fclose(fp);
}

// ========== Funções para editar e excluir registros ==========

void editarPessoa(const char *arquivo) {
    char nomeBusca[MAX_NOME];
    printf("Digite o nome da pessoa (PF ou PJ) que deseja editar: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    removeNewline(nomeBusca);

    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        printf("Arquivo não encontrado.\n");
        return;
    }
    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(fp);
        return;
    }

    char linha[MAX_LINHA];
    bool encontrado = false;

    while (fgets(linha, sizeof(linha), fp)) {
        char tipo[3], nome[MAX_NOME];
        sscanf(linha, "%2[^;];%[^;];", tipo, nome);

        if (strcmp(nome, nomeBusca) == 0) {
            encontrado = true;
            printf("Registro encontrado:\n%s", linha);

            if (strcmp(tipo, "PF") == 0) {
                char cpf[15], dataNascimento[12], telefone[20], email[100];

                printf("Digite os novos dados (deixe vazio para manter o atual):\n");

                printf("Nome: ");
                char novoNome[MAX_NOME];
                fgets(novoNome, MAX_NOME, stdin);
                removeNewline(novoNome);
                if (strlen(novoNome) == 0) strcpy(novoNome, nome);

                printf("CPF: ");
                fgets(cpf, 15, stdin);
                removeNewline(cpf);

                printf("Data de nascimento: ");
                fgets(dataNascimento, 12, stdin);
                removeNewline(dataNascimento);

                printf("Telefone: ");
                fgets(telefone, 20, stdin);
                removeNewline(telefone);

                printf("E-mail: ");
                fgets(email, 100, stdin);
                removeNewline(email);

                char nomeAnt[MAX_NOME], cpfAnt[15], dataAnt[12], telAnt[20], emailAnt[100];
                sscanf(linha, "%*[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]", nomeAnt, cpfAnt, dataAnt, telAnt, emailAnt);

                if (strlen(cpf) == 0) strcpy(cpf, cpfAnt);
                if (strlen(dataNascimento) == 0) strcpy(dataNascimento, dataAnt);
                if (strlen(telefone) == 0) strcpy(telefone, telAnt);
                if (strlen(email) == 0) strcpy(email, emailAnt);

                fprintf(temp, "PF;%s;%s;%s;%s;%s\n", novoNome, cpf, dataNascimento, telefone, email);

            } else if (strcmp(tipo, "PJ") == 0) {
                char cnpj[20], endereco[150], telefone[20], email[100];

                printf("Digite os novos dados (deixe vazio para manter o atual):\n");

                printf("Nome da empresa: ");
                char novoNome[MAX_NOME];
                fgets(novoNome, MAX_NOME, stdin);
                removeNewline(novoNome);
                if (strlen(novoNome) == 0) strcpy(novoNome, nome);

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

                char nomeAnt[MAX_NOME], cnpjAnt[20], endAnt[150], telAnt[20], emailAnt[100];
                sscanf(linha, "%*[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]", nomeAnt, cnpjAnt, endAnt, telAnt, emailAnt);

                if (strlen(cnpj) == 0) strcpy(cnpj, cnpjAnt);
                if (strlen(endereco) == 0) strcpy(endereco, endAnt);
                if (strlen(telefone) == 0) strcpy(telefone, telAnt);
                if (strlen(email) == 0) strcpy(email, emailAnt);

                fprintf(temp, "PJ;%s;%s;%s;%s;%s\n", novoNome, cnpj, endereco, telefone, email);
            }
        } else {
            fputs(linha, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if (!encontrado) {
        printf("Pessoa não encontrada.\n");
        remove("temp.txt");
    } else {
        remove(arquivo);
        rename("temp.txt", arquivo);
        printf("Registro editado com sucesso.\n");
    }
}

void excluirPessoa(const char *arquivo) {
    char nomeBusca[MAX_NOME];
    printf("Digite o nome da pessoa (PF ou PJ) que deseja excluir: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    removeNewline(nomeBusca);

    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        printf("Arquivo não encontrado.\n");
        return;
    }
    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(fp);
        return;
    }

    char linha[MAX_LINHA];
    bool encontrado = false;

    while (fgets(linha, sizeof(linha), fp)) {
        char tipo[3], nome[MAX_NOME];
        sscanf(linha, "%2[^;];%[^;];", tipo, nome);

        if (strcmp(nome, nomeBusca) == 0) {
            encontrado = true;
            // Não escreve - exclui
            continue;
        } else {
            fputs(linha, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if (!encontrado) {
        printf("Pessoa não encontrada.\n");
        remove("temp.txt");
    } else {
        remove(arquivo);
        rename("temp.txt", arquivo);
        printf("Registro excluído com sucesso.\n");
    }
}

void editarAcao(const char *arquivo) {
    char nomeBusca[MAX_NOME];
    printf("Digite o nome da ação que deseja editar: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    removeNewline(nomeBusca);

    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        printf("Arquivo não encontrado.\n");
        return;
    }
    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(fp);
        return;
    }

    char linha[MAX_LINHA];
    bool encontrado = false;

    while (fgets(linha, sizeof(linha), fp)) {
        char nome[MAX_NOME];
        sscanf(linha, "%[^;];", nome);

        if (strcmp(nome, nomeBusca) == 0) {
            encontrado = true;
            printf("Registro encontrado:\n%s", linha);

            printf("Digite os novos dados (deixe vazio para manter o atual):\n");

            char novoNome[MAX_NOME], descricao[256], data[12], local[MAX_NOME];
            fgets(novoNome, MAX_NOME, stdin);
            removeNewline(novoNome);

            fgets(descricao, 256, stdin);
            removeNewline(descricao);

            fgets(data, 12, stdin);
            removeNewline(data);

            fgets(local, MAX_NOME, stdin);
            removeNewline(local);

            char nomeAnt[MAX_NOME], descAnt[256], dataAnt[12], localAnt[MAX_NOME];
            sscanf(linha, "%[^;];%[^;];%[^;];%[^\n]", nomeAnt, descAnt, dataAnt, localAnt);

            if (strlen(novoNome) == 0) strcpy(novoNome, nomeAnt);
            if (strlen(descricao) == 0) strcpy(descricao, descAnt);
            if (strlen(data) == 0) strcpy(data, dataAnt);
            if (strlen(local) == 0) strcpy(local, localAnt);

            fprintf(temp, "%s;%s;%s;%s\n", novoNome, descricao, data, local);

        } else {
            fputs(linha, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if (!encontrado) {
        printf("Ação não encontrada.\n");
        remove("temp.txt");
    } else {
        remove(arquivo);
        rename("temp.txt", arquivo);
        printf("Registro editado com sucesso.\n");
    }
}

void excluirAcao(const char *arquivo) {
    char nomeBusca[MAX_NOME];
    printf("Digite o nome da ação que deseja excluir: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    removeNewline(nomeBusca);

    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        printf("Arquivo não encontrado.\n");
        return;
    }
    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(fp);
        return;
    }

    char linha[MAX_LINHA];
    bool encontrado = false;

    while (fgets(linha, sizeof(linha), fp)) {
        char nome[MAX_NOME];
        sscanf(linha, "%[^;];", nome);

        if (strcmp(nome, nomeBusca) == 0) {
            encontrado = true;
            // não escreve = exclui
            continue;
        } else {
            fputs(linha, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if (!encontrado) {
        printf("Ação não encontrada.\n");
        remove("temp.txt");
    } else {
        remove(arquivo);
        rename("temp.txt", arquivo);
        printf("Registro excluído com sucesso.\n");
    }
}

void excluirInscricao(const char *arquivo) {
    char nomeUsuario[MAX_NOME], nomeAcao[MAX_NOME];
    printf("Digite o nome do usuário para excluir inscrição: ");
    fgets(nomeUsuario, MAX_NOME, stdin);
    removeNewline(nomeUsuario);

    printf("Digite o nome da ação para excluir inscrição: ");
    fgets(nomeAcao, MAX_NOME, stdin);
    removeNewline(nomeAcao);

    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        printf("Arquivo de inscrições não encontrado.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(fp);
        return;
    }

    char linha[MAX_LINHA];
    bool encontrado = false;

    while (fgets(linha, sizeof(linha), fp)) {
        char usuario[MAX_NOME], acao[MAX_NOME];
        sscanf(linha, "%[^;];%[^\n]", usuario, acao);

        if (strcmp(usuario, nomeUsuario) == 0 && strcmp(acao, nomeAcao) == 0) {
            encontrado = true;
            continue; // não escreve, exclui
        } else {
            fputs(linha, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if (!encontrado) {
        printf("Inscrição não encontrada.\n");
        remove("temp.txt");
    } else {
        remove(arquivo);
        rename("temp.txt", arquivo);
        printf("Inscrição excluída com sucesso.\n");
    }
}

// Função de logotipo
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
    const char *arquivoInscricoes = "inscricoes.txt";

    int selecao;
    bool cont = true;
    bool valid;

    mostrarLogo();

    do {
        printf("\nSelecione uma opcao:\n\n");
        printf("1. Cadastro de OSCs (Pessoa Jurídica)\n");
        printf("2. Cadastro de Usuários (Pessoa Física / Voluntários)\n");
        printf("3. Registro de Ações por OSCs\n");
        printf("4. Listagem de Ações\n");
        printf("5. Inscrição de Usuários em Ações\n");
        printf("6. Visualização de Participantes por Ação\n");
        printf("7. Editar Pessoa (PF/PJ)\n");
        printf("8. Excluir Pessoa (PF/PJ)\n");
        printf("9. Editar Ação\n");
        printf("10. Excluir Ação\n");
        printf("11. Excluir Inscrição de Usuário em Ação\n");
        printf("0. Sair\n");
        printf("Digite o número da opção desejada: ");
        scanf("%d", &selecao);
        getchar();

        switch (selecao) {
        case 1: {
            int tipoPessoa;
            do {
                system("cls"); // ou system("clear") se não for Windows
                printf("Cadastro de OSCs (Pessoa Jurídica)\n");
                printf("Você é:\n1. Pessoa Jurídica (PJ)\nDigite a opção: ");
                scanf("%d", &tipoPessoa);
                getchar();
            } while (tipoPessoa != 1);

            cadastrarPessoaJuridica(arquivoPessoas);
            break;
        }
        case 2: {
            int tipoPessoa;
            do {
                system("cls");
                printf("Cadastro de Usuários (Pessoa Física / Voluntários)\n");
                printf("Escolha o tipo:\n1. Pessoa Física (PF)\n2. Voluntário\nDigite a opção: ");
                scanf("%d", &tipoPessoa);
                getchar();
            } while (tipoPessoa != 1 && tipoPessoa != 2);

            if (tipoPessoa == 1) {
                cadastrarPessoaFisica(arquivoPessoas);
            } else {
                cadastro_voluntario();
            }
            break;
        }
        case 3:
            cadastrarAcao();
            break;
        case 4:
            lerTodasAcoes(arquivoAcoes);
            break;
        case 5:
            cadastrarVoluntarioInterativo();
            break;
        case 6:
            mostrarUsuariosPorAcao();
            break;
        case 7:
            editarPessoa(arquivoPessoas);
            break;
        case 8:
            excluirPessoa(arquivoPessoas);
            break;
        case 9:
            editarAcao(arquivoAcoes);
            break;
        case 10:
            excluirAcao(arquivoAcoes);
            break;
        case 11:
            excluirInscricao(arquivoInscricoes);
            break;
        case 0:
            cont = false;
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (cont);

    printf("Obrigado por utilizar o P.E.S.I.!\n");
    return 0;
}