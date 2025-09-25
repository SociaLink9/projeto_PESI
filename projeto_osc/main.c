/*
 Projeto: Plataforma de Engajamento Social
 Curso: Análise e Desenvolvimento de Sistemas
 Líder de projeto: Gabriel Albuquerque N. de Oliveira
 Integrantes:
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>


// Função de logotipo(***PONTO A MELHORAR***)
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

    setlocale(LC_ALL, "pt-BR"); // Configura acentuação (Não está aceitando**Resolver problema**)

    // Variáveis de seleção e controle.
    int selecao;
    bool cont = true;

    mostrarLogo();

    // Estrutura de loop para o menu.
    do
    {

        printf("\nSelecione uma opcao:\n\n1. Cadastro de OSCs\n2. Cadastro de Usuários\n3. Registro de Ações por OSCs\n4. Listagem de Ações\n5. Inscrição de Usuários em Ações\n6. Visualização de Participantes por Ação\n0. Sair\nDigite o número da opção desejada: ");
        scanf("%d", &selecao);

        switch (selecao)
        {
        case 1: // Cadastro de OSCs
            printf("teste 1 ok");  // Arquivo da função usuarios.c/h
            system("pause");

            break;

        case 2: // Cadastro de usuários
            printf("teste 2 ok"); // Arquivo da função oscs.c/h
            break;
        case 3: // Registro de ações por OSCs

            printf("teste 3 ok"); // Arquivo da função oscs.c/h
            break;
        case 4: // Listagem das ações

            printf("teste 4 ok"); // Arquivo da função database.c/h
            break;
        case 5: // Inscrição de usuários em ações

            printf("teste 5 ok"); // Arquivo da função database.c/h
            break;
        case 6: // Vizualização de participantes por ação

            printf("teste 6 ok"); // Arquivo da função database.c/h
            break;

        case 0: // Finaliza o programa

            printf("Finalizando sistema...");
            cont = false;
            break;

        default:

            printf("Opcao invalida!\nTente novamente");
            break;
        }

    } while (cont != false); // O loop se rompe quando a variavel for falsa;

    return 0;
}
