# 📚 Biblioteca Digital

Este repositório contém o projeto desenvolvido para a disciplina **Algoritmos e Estruturas de Dados II** do curso de **Bacharelado em Ciência da Computação**, ministrada pelo professor [Luiz Ricardo Begosso](https://www.escavador.com/sobre/3201843/luiz-ricardo-begosso).

## 👥 Autores

O desenvolvimento está sendo realizado em **Pair Programming** por:

- Thiago Ausechi — RA: 2411600623
  - [Github](https://github.com/thiagoausechi)
  - [LinkedIn](https://www.linkedin.com/in/thiagoausechi/)
- Lucas Facina — RA: 2411600015
  - [Github](https://github.com/lucasfacina)
  - [LinkedIn](https://www.linkedin.com/in/lucasfacina/)

## 📋 Requisitos do Trabalho

Escrever um programa para criar as seguintes estruturas que simularão arquivos sequenciais para uma aplicação de Biblioteca:

### Estruturas (arquivos/tabelas)

```txt
1. [ ] Cidades:     código (PK), descrição, UF
2. [ ] Pessoas:     codigo (PK), nome, CPF, endereço, codigo_cidade (FK)
3. [ ] Editoras:    codigo (PK), nome, codigo_cidade (FK)
4. [ ] Autores:     codigo (PK), nome
5. [ ] Gêneros:     codigo (PK), descrição
6. [ ] Livros:      codigo (PK), nome, codigo_editora (FK), codigo_autor (FK), codigo_genero (FK), disponível_s_n
7. [ ] Empréstimos: codigo (PK), codigo_pessoa (FK), codigo_livro (FK), data_empréstimo, data_prevista_devolução, data_efetiva_devolução
```

### Requisitos

```txt
1. [ ] Escreva funções específicas para a leitura dos dados das estruturas.
2. [ ] Escreva uma função para permitir a inclusão de novos registros na tabela de pessoas.
   1. [ ] Quando o usuário digitar o CPF, o programa deverá realizar a validação do CPF.
   2. [ ] Quando o usuário digitar o código da cidade, o programa deverá buscar este código na tabela de cidades e exibir a descrição e UF da cidade.

3. [ ] Escreva uma função para permitir a inclusão de novos registros na tabela de livros.
   1. [ ] Quando o usuário digitar o código da editora, o programa deverá buscar este código na tabela de editoras e exibir o nome da editora.
   2. [ ] Quando o usuário digitar o código do autor, o programa deverá buscar este código na tabela de autores e exibir o nome do autor.
   3. [ ] Quando o usuário digitar o código do gênero, o programa deverá buscar este código na tabela de gêneros e exibir a descrição.

4. [ ] Escreva uma função para permitir que uma pessoa realize o empréstimo de um livro, cujas informações serão gravadas na tabela Empréstimos.
   1. [ ] O código do empréstimo (PK) deverá ser gerado automaticamente e sequencialmente a partir do último registro cadastrado.
   2. [ ] O usuário deverá informar o código da pessoa que está emprestando o livro e o programa deverá buscar este código na tabela de pessoas e exibi o nome da pessoa e o nome da sua cidade.
   3. [ ] O usuário deverá informar o código do livro a ser emprestado e o programa deverá buscar este código na tabela de livros e exibir o nome do livro.
   4. [ ] O programa deverá exibir o nome da editora e o nome do autor do livro.
   5. [ ] O programa deverá verificar na tabela de livros se o livro está disponível para empréstimo (disponivel_s_n = "S").
      1. [ ] SE o livro estiver disponível para empréstimo, o programa deverá:
         1. [ ] Gravar a data_empréstimo como a data do dia atual.
         2. [ ] Gravar a data_prevista_devolução como sendo a data atual mais sete dias.
         3. [ ] Gravar a informação da tabela de Livros disponivel_s_n = "N"
   6. [ ] Se o livro não estiver disponível para empréstimo, então uma mensagem deverá ser mostrado ao usuário e o empréstimo não será realizado.

5. [ ] Escreva uma função para permitir que uma pessoa realize a devolução de um livro.
   1. [ ] O usuário deverá informar o código do empréstimo do livro a ser devolvido e o programa deverá buscar este código na tabela de Empréstimos e exibir:
      1. [ ] O nome da pessoa e o nome do livro.
      2. [ ] O nome da editora e o nome do autor do livro.
      3. [ ] A data do empréstimo e a data da efetiva devolução (que deverá ser a data do dia atual).
   2. [ ] Se a data da efetiva devolução estiver em branco, então o livro ainda não foi devolvido e poderá ser devolvido neste momento.
      1. [ ] Para confirmar a devolução, o programa deverá atualizar a data da efetiva devolução com a data atual e atualizar o atributo da tabela de Livros disponivel_s_n = "S".

6. [ ] Escreva uma função para mostrar todos os livros que estejam emprestados, verificando a tabela de Livros: disponível_s_n = "N".
   1. [ ] O programa deverá exibir: código do livro, nome do livro.
   2. [ ] Ao final dessa função, mostrar a quantidade de livros emprestados e a quantidade de livros disponíveis para empréstimo.

7. [ ] Escreva uma função para mostrar os dados dos livros e das pessoas que estejam com a devolução em atraso (data_prevista_devolução < data atual).
   1. [ ] O programa deverá exibir: código do livro, nome do livro, nome da editora, nome do autor, data prevista da devolução, quantidade de dias em atraso.

8. [ ] Todas as funções descritas acima deverão ser chamadas através de um menu de opções que será chamado a partir da função main().

Obs: não utilizar variáveis globais.
```

> 📝 **Nota:** Os itens dos requisitos podem ser localizados no código por meio da busca por "Requisito x.x.x" (_ex.: Requisito 4.5.1.2_), utilizando a concatenação dos identificadores dos itens aninhados.

## 📁 Estrutura do Projeto

### Estrutura de Diretórios

```bash
📁 biblioteca-digital-aed/
├── 📁 include/        # Arquivos de cabeçalho (.h / .hpp)
├── 📁 src/            # Implementação do projeto (.cpp)
├── 📁 data/           # Arquivos/banco de dados
└── 📄 CMakeLists.txt  # Configuração do CMake
```

### Diagrama de Relacionamentos

![Diagrama de Relacionamentos](https://github.com/user-attachments/assets/20f71829-bf52-4b1d-8cf8-526823504ec6)

## 💻 Ambiente de Desenvolvimento e Execução

Este projeto foi desenvolvido em **C++** utilizando a IDE [CLion](https://www.jetbrains.com/clion/) da JetBrains, que oferece integração nativa com [CMake](https://cmake.org/).
A execução do projeto pode ser feita diretamente pela própria IDE, sem necessidade de executar comandos manuais de build.

> **⚠️ Atenção:**
> Como o projeto foi criado e testado em um ambiente **macOS**, pode ser necessário ajustar configurações específicas no `CMakeLists.txt` ou nas configurações da IDE para garantir a compatibilidade em sistemas **Windows** ou **Linux**.

## 📄 Licença

Este projeto é parte de uma atividade acadêmica e não possui fins comerciais.
Uso exclusivo para fins educacionais na [FEMA](https://fema.edu.br/) - Fundação Educacional do Município de Assis.
