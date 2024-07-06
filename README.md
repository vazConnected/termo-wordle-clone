# Wordle/Termo Clone

Esse jogo tem se trata sobre uma implementação em C++ de um jogo inspirado nos populares [Wordle](https://www.nytimes.com/games/wordle/index.html) e [Termo](https://term.ooo/).

# Como jogar

O jogo selecionará uma palavra aleatória e o jogador terá um número de tentativas para adivinha-la. A cada tentativa, o jogo fornecerá dicas para guiar as próximas jogadas.

# Como Executar

Para gerar o executável, basta rodar o seguinte comando na pasta com o codigo-fonte:
- Windows:
    ```
    g++ termo_wordle.cpp -o termo_wordle.exe
    ```
- Linux:
    ```
    g++ termo_wordle.cpp -o termo_wordle.out
    ```
Para a execução, é possível passar parâmetros de <ins>tentativas máximas</ins> e <ins>caminho do arquivo com banco de palavras</ins>. A seguir exemplos para Windows e Linux em que o limite de tentativas é ```5``` e o arquivo com as palavras é o ```palavras.txt```:
- Windows:
    ```
    ./termo_wordle.exe palavras.txt 10
    ```
- Linux:
    ```
    ./termo_wordle.out palavras.txt 10
    ```
Caso os parametros não sejam informados, o jogo definirá o máximo de tentativas por jogadas como 5 e tentará buscar o banco de palavras no arquivo [words.txt](words.txt).
