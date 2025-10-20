# Projeto OSC - Sistema de Ações Sociais

## Visão Geral

Este projeto tem como objetivo criar um sistema simples, em linguagem C, que permita a interação entre *organizações da sociedade civil (OSCs)* e *voluntários*. Utilizando banco de dados SQLite, o sistema oferece funcionalidades básicas como:

- Cadastro de OSCs
- Registro de ações sociais (ex: mutirão de limpeza)
- Cadastro e login de usuários
- Inscrição de usuários em ações
- Visualização de participantes por ação

Este é o MVP (Produto Mínimo Viável) do projeto, desenvolvido como atividade prática para alunos de primeiro período, com foco em modularização, persistência de dados e lógica de programação.

---

## Estrutura do Projeto

```plaintext
projeto_osc/
├── main.c              # Menu principal
├── usuarios.c/h        # Cadastro e login de usuários
├── oscs.c/h            # Cadastro de OSCs e ações
├── acoes.c/h           # Inscrição e listagem de ações
├── database.c/h        # Conexão e criação do banco SQLite
├── projeto.db          # Banco de dados gerado automaticamente
└── README.md           # Este arquivo

---

## Créditos

Projeto desenvolvido por alunos do primeiro periodo de Análise e Desenvolvimento de Sistemas.
Equipe Back-end liderada por Gabriel Albuquerque Nascimento de Oliveira, com foco em aprendizado pratico em C.