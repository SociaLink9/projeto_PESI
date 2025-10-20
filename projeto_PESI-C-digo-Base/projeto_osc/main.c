/*
 Projeto: Plataforma de Engajamento Social
 Curso: Análise e Desenvolvimento de Sistemas
 Líder de projeto: Gabriel Albuquerque N. de Oliveira
 Integrantes:
 David Richard Lima de Souza
 Luan Santos Alves Pequeno Da Silva
 Pedro Caio Francisco da Silva
 Vinicius da Silva ramos
 Yago vinicius de freitas silva
 Geovane Alves da Silva Filho
 Gabriela Torres Guerra da Fonte
 Guilherme Morais Cavalcante
 João Vitor Santos silva
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include "usuarios.h"
#include "oscs.h"
#include "acoes.h"

// Função de logotipo(Aguardando posicionamento do grupo comecial sobre nome do produto.)
void mostrarLogo(void)
{
    printf(".====================================================================.\n");
    printf("!                                                                    !\n");
    printf("!   |||||||  ||||||  ||||||  ||  |||||  ||      || ||||   || ||   || !\n");
    printf("!   ||      ||    || ||      || ||   || ||      || || ||  || ||  ||  !\n");
    printf("!   ||||||| ||    || ||      || ||||||| ||      || ||  || || || ||   !\n");
    printf("!        || ||    || ||      || ||   || ||      || ||   |||| ||  ||  !\n");
    printf("!   |||||||  ||||||  ||||||  || ||   || ||||||| || ||    ||| ||   || !\n");
    printf("!                                                                    !\n");
    printf("!                                                                    !\n");
    printf("!   Plataforma de Engajamento Social Integrado (P.E.S.I.)            !\n");
    printf("!                                                                    !\n");
    printf("!   Bem-vindo à transformação digital do engajamento!                !\n");
    printf("!   Conectando ideias, pessoas e propósitos com inteligência.        !\n");
    printf(".====================================================================.\n");
}

int main()
{
    // Configuração de idioma - OK
    setlocale(LC_ALL, "Portuguese_Brazil");

    // Ponteiro para o nome do arquivo de dados (dados.txt armazena OSCs)
    const char *arquivo1 = "dados.txt";
    

    // Variáveis de seleção e controle
    int selecao;
    bool cont = true;
    bool valid;

    // Exibe o logotipo do sistema
    mostrarLogo();

    // Estrutura de loop para exibir o menu principal enquanto o usuário não escolher sair
    do
    {
        // Exibe as opções do menu

        printf("\nSelecione uma opcao:\n\n1. Cadastro de OSCs\n2. Cadastro de Usuários\n3. Registro de Ações por OSCs\n4. Listagem de Ações\n5. Inscrição de Usuários em Ações\n6. Visualização de Participantes por Ação\n0. Sair\nDigite o número da opção desejada: ");
        
        // Uso de scanf para o inteiro, seguido por getchar para limpar o '\n'
        if (scanf("%d", &selecao) != 1) {
            selecao = -1; // Opção inválida forçada
        }
        getchar(); // Limpa o buffer do teclado após o scanf

        // Processa a opção escolhida pelo usuário
        switch (selecao)
        {
        case 1: // Cadastro de OSCs
            // Submenu para escolher entre Pessoa Física ou Jurídica
            do
            {
                system("cls");
                printf("Você é:\n1. PF\n2. PJ\nDigite a opção desejada:");
                if (scanf("%d", &selecao) != 1) {
                    selecao = -1; // Opção inválida forçada
                }
                getchar(); // Limpa o buffer do teclado

                switch (selecao)
                {
                case 1:
                    system("cls");
                    // Chama função para cadastrar Pessoa Física
                    cadastrarPessoaFisica(arquivo1);
                    valid = true;
                    break;
                case 2:
                    system("cls");
                    // Chama função para cadastrar Pessoa Jurídica
                    cadastrarPessoaJuridica(arquivo1);
                    valid = true;
                    break;
                default:
                    system("cls");
                    // Opção inválida, solicita nova tentativa
                    printf("\nOpção invalida!\nTente novamente!");
                    valid = false;
                    break;
                }
            } while (valid != true);

            // Pausa para o usuário visualizar o resultado
            system("pause");
            system("cls");
            break;


        case 2: // Cadastro de usuários (Voluntários)
            system("cls");
            // Chama função para cadastrar voluntário
            cadastro_voluntario();
            system("pause");
            system("cls");
            break;


        case 3: // Registro de ações por OSCs
            system("cls");
            // Chama função para cadastrar ação
            cadastrarAcao();
            system("pause");
            system("cls");
            break;


        case 4: // Listagem das ações
            system("cls");
            lerTodasAcoes();
            system("pause");
            system("cls");
            break;


        case 5: // Inscrição de usuários em ações
            system("cls");
            cadastrarVoluntarioInterativo();
            system("pause");
            system("cls");
            break;


        case 6: // Visualização de participantes por ação
            system("cls");
            mostrarUsuariosPorAcao();
            system("pause");
            system("cls");

            break;

        case 0: // Finaliza o programa
            // Mensagem de encerramento e termina o loop
            printf("Finalizando sistema...\n");
            cont = false;
            break;

        default:
            // Opção inválida, solicita nova tentativa
            system("cls");
            printf("Opcao invalida!\nTente novamente\n");
            system("pause");
            system("cls");
            break;
        }

    } while (cont != false); // O loop se rompe quando a variável for falsa

    // Retorna 0 indicando execução bem-sucedida
    return 0;
}