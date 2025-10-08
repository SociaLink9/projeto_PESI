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

// ========== Fun��es para cadastro, listagem e intera��o =========

// Fun��es de cadastro para pessoas f�sicas e jur�dicas
void cadastrarPessoaFisica(const char *arquivo) {
    char nome[MAX_NOME], cpf[15], dataNascimento[12], telefone[20], email[100];
    printf("Cadastro Pessoa F�sica:\n");
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

    printf("Pessoa f�sica cadastrada com sucesso!\n");
}

void cadastrarPessoaJuridica(const char *arquivo) {
    char nome[MAX_NOME], cnpj[20], endereco[150], telefone[20], email[100];
    printf("Cadastro Pessoa Jur�dica (OSC):\n");
    printf("Nome da empresa: ");
    fgets(nome, MAX_NOME, stdin);
    removeNewline(nome);

    printf("CNPJ: ");
    fgets(cnpj, 20, stdin);
    removeNewline(cnpj);

    printf("Endere�o: ");
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

    printf("Pessoa jur�dica cadastrada com sucesso!\n");
}

// Cadastro volunt�rio simplificado para exemplo
void cadastro_voluntario(void) {
    char nome[MAX_NOME], telefone[20], email[100];
    printf("Cadastro de Volunt�rio:\n");
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
        printf("Erro ao abrir arquivo para salvar volunt�rio.\n");
        return;
    }

    fprintf(fp, "%s;%s;%s\n", nome, telefone, email);
    fclose(fp);

    printf("Volunt�rio cadastrado com sucesso!\n");
}

// Cadastro de a��o
void cadastrarAcao(void) {
    char nome[MAX_NOME], descricao[256], data[12], local[MAX_NOME];
    printf("Cadastro de A��o:\n");
    printf("Nome da a��o: ");
    fgets(nome, MAX_NOME, stdin);
    removeNewline(nome);

    printf("Descri��o: ");
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
        printf("Erro ao abrir arquivo para salvar a��o.\n");
        return;
    }

    fprintf(fp, "%s;%s;%s;%s\n", nome, descricao, data, local);
    fclose(fp);

    printf("A��o cadastrada com sucesso!\n");
}

// Listar todas as a��es
void lerTodasAcoes(const char *arquivo) {
    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        printf("Nenhuma a��o cadastrada.\n");
        return;
    }

    char linha[MAX_LINHA];
    printf("Lista de A��es:\n");
    while (fgets(linha, sizeof(linha), fp)) {
        char nome[MAX_NOME], descricao[256], data[12], local[MAX_NOME];
        sscanf(linha, "%[^;];%[^;];%[^;];%[^\n]", nome, descricao, data, local);

        printf("\nNome: %s\nDescri��o: %s\nData: %s\nLocal: %s\n", nome, descricao, data, local);
    }
    fclose(fp);
}

// Inscrever usu�rio em a��o
void cadastrarVoluntarioInterativo(void) {
    char nomeUsuario[MAX_NOME], nomeAcao[MAX_NOME];
    printf("Inscri��o de Usu�rio em A��o:\n");

    printf("Nome do usu�rio: ");
    fgets(nomeUsuario, MAX_NOME, stdin);
    removeNewline(nomeUsuario);

    printf("Nome da a��o: ");
    fgets(nomeAcao, MAX_NOME, stdin);
    removeNewline(nomeAcao);

    FILE *fp = fopen("inscricoes.txt", "a");
    if (!fp) {
        printf("Erro ao abrir arquivo para salvar inscri��o.\n");
        return;
    }

    fprintf(fp, "%s;%s\n", nomeUsuario, nomeAcao);
    fclose(fp);

    printf("Inscri��o realizada com sucesso!\n");
}

// Mostrar usu�rios inscritos por a��o
void mostrarUsuariosPorAcao(void) {
    char nomeAcao[MAX_NOME];
    printf("Visualiza��o de Participantes por A��o:\n");
    printf("Digite o nome da a��o: ");
    fgets(nomeAcao, MAX_NOME, stdin);
    removeNewline(nomeAcao);

    FILE *fp = fopen("inscricoes.txt", "r");
    if (!fp) {
        printf("Nenhuma inscri��o encontrada.\n");
        return;
    }

    char linha[MAX_LINHA];
    bool encontrou = false;
    printf("Usu�rios inscritos na a��o \"%s\":\n", nomeAcao);

    while (fgets(linha, sizeof(linha), fp)) {
        char usuario[MAX_NOME], acao[MAX_NOME];
        sscanf(linha, "%[^;];%[^\n]", usuario, acao);

        if (strcmp(acao, nomeAcao) == 0) {
            printf("- %s\n", usuario);
            encontrou = true;
        }
    }

    if (!encontrou) printf("Nenhum usu�rio inscrito nessa a��o.\n");

    fclose(fp);
}

// ========== Fun��es para editar e excluir registros ==========

void editarPessoa(const char *arquivo) {
    char nomeBusca[MAX_NOME];
    printf("Digite o nome da pessoa (PF ou PJ) que deseja editar: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    removeNewline(nomeBusca);

    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        printf("Arquivo n�o encontrado.\n");
        return;
    }
    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Erro ao criar arquivo tempor�rio.\n");
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

                printf("Endere�o: ");
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
        printf("Pessoa n�o encontrada.\n");
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
        printf("Arquivo n�o encontrado.\n");
        return;
    }
    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Erro ao criar arquivo tempor�rio.\n");
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
            // N�o escreve - exclui
            continue;
        } else {
            fputs(linha, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if (!encontrado) {
        printf("Pessoa n�o encontrada.\n");
        remove("temp.txt");
    } else {
        remove(arquivo);
        rename("temp.txt", arquivo);
        printf("Registro exclu�do com sucesso.\n");
    }
}

void editarAcao(const char *arquivo) {
    char nomeBusca[MAX_NOME];
    printf("Digite o nome da a��o que deseja editar: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    removeNewline(nomeBusca);

    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        printf("Arquivo n�o encontrado.\n");
        return;
    }
    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Erro ao criar arquivo tempor�rio.\n");
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
        printf("A��o n�o encontrada.\n");
        remove("temp.txt");
    } else {
        remove(arquivo);
        rename("temp.txt", arquivo);
        printf("Registro editado com sucesso.\n");
    }
}

void excluirAcao(const char *arquivo) {
    char nomeBusca[MAX_NOME];
    printf("Digite o nome da a��o que deseja excluir: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    removeNewline(nomeBusca);

    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        printf("Arquivo n�o encontrado.\n");
        return;
    }
    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Erro ao criar arquivo tempor�rio.\n");
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
            // n�o escreve = exclui
            continue;
        } else {
            fputs(linha, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if (!encontrado) {
        printf("A��o n�o encontrada.\n");
        remove("temp.txt");
    } else {
        remove(arquivo);
        rename("temp.txt", arquivo);
        printf("Registro exclu�do com sucesso.\n");
    }
}

void excluirInscricao(const char *arquivo) {
    char nomeUsuario[MAX_NOME], nomeAcao[MAX_NOME];
    printf("Digite o nome do usu�rio para excluir inscri��o: ");
    fgets(nomeUsuario, MAX_NOME, stdin);
    removeNewline(nomeUsuario);

    printf("Digite o nome da a��o para excluir inscri��o: ");
    fgets(nomeAcao, MAX_NOME, stdin);
    removeNewline(nomeAcao);

    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        printf("Arquivo de inscri��es n�o encontrado.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Erro ao criar arquivo tempor�rio.\n");
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
            continue; // n�o escreve, exclui
        } else {
            fputs(linha, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if (!encontrado) {
        printf("Inscri��o n�o encontrada.\n");
        remove("temp.txt");
    } else {
        remove(arquivo);
        rename("temp.txt", arquivo);
        printf("Inscri��o exclu�da com sucesso.\n");
    }
}

// Fun��o de logotipo
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
    printf("!   Bem-vindo � transforma��o digital do engajamento!                !\n");
    printf("!   Conectando ideias, pessoas e prop�sitos com intelig�ncia.        !\n");
    printf(".====================================================================.\n");
}

// ========== Fun��o principal ==========

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil.1252");

    const char *arquivoPessoas = "dados.txt";
    const char *arquivoAcoes = "acoes.txt";
    const char *arquivoInscricoes = "inscricoes.txt";

    int selecao;
    bool cont = true;
    bool valid;

    mostrarLogo();

    do {
        printf("\nSelecione uma opcao:\n\n");
        printf("1. Cadastro de OSCs (Pessoa Jur�dica)\n");
        printf("2. Cadastro de Usu�rios (Pessoa F�sica / Volunt�rios)\n");
        printf("3. Registro de A��es por OSCs\n");
        printf("4. Listagem de A��es\n");
        printf("5. Inscri��o de Usu�rios em A��es\n");
        printf("6. Visualiza��o de Participantes por A��o\n");
        printf("7. Editar Pessoa (PF/PJ)\n");
        printf("8. Excluir Pessoa (PF/PJ)\n");
        printf("9. Editar A��o\n");
        printf("10. Excluir A��o\n");
        printf("11. Excluir Inscri��o de Usu�rio em A��o\n");
        printf("0. Sair\n");
        printf("Digite o n�mero da op��o desejada: ");
        scanf("%d", &selecao);
        getchar();

        switch (selecao) {
        case 1: {
            int tipoPessoa;
            do {
                system("cls"); // ou system("clear") se n�o for Windows
                printf("Cadastro de OSCs (Pessoa Jur�dica)\n");
                printf("Voc� �:\n1. Pessoa Jur�dica (PJ)\nDigite a op��o: ");
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
                printf("Cadastro de Usu�rios (Pessoa F�sica / Volunt�rios)\n");
                printf("Escolha o tipo:\n1. Pessoa F�sica (PF)\n2. Volunt�rio\nDigite a op��o: ");
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
            printf("Op��o inv�lida. Tente novamente.\n");
        }
    } while (cont);

    printf("Obrigado por utilizar o P.E.S.I.!\n");
    return 0;
}