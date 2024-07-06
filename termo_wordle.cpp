#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>    // toupper() e tolower()
#include <algorithm> // std::transform

using namespace std;

#define FILENAME "words.txt"
#define MAX_TRIES 5

vector<string> readFromFile(string filename)
{
    ifstream inputFile(filename);
    vector<string> words;
    string word;

    if (inputFile.is_open())
    {
        while (getline(inputFile, word))
        {
            transform(word.begin(), word.end(), word.begin(), ::toupper); // certificar que palavra esta em uppercase
            words.push_back(word);
        }
        inputFile.close();
    }
    else
    {
        throw invalid_argument("Erro ao abrir arquivo " + filename + " para leitura.");
    }
    return words;
}

string getRandomWord(vector<string> &availableWords)
{
    if (availableWords.empty())
    {
        throw invalid_argument("Nao ha mais palavras disponiveis para jogar.");
    }

    int randomIndex = rand() % availableWords.size();
    string word = availableWords[randomIndex];
    availableWords.erase(availableWords.begin() + randomIndex);
    return word;
}

string getHint(string word, string guess)
{
    string hint = "";
    for (size_t i = 0; i < guess.size(); i++)
    {
        size_t charPosition = word.find(guess[i]);

        if (charPosition == string::npos)
        {
            hint.append(1, '*');
            continue;
        }

        bool rightPosition = (guess[i] == word[i]);
        if (rightPosition)
        {
            hint.append(1, toupper(guess[i]));
            continue;
        }
        else
        {
            hint.append(1, tolower(guess[i]));
            continue;
        }
    }
    return hint;
}

string getUserGuess(size_t wordSize, int tries)
{
    string guess;
    bool validGuess = false;
    do
    {
        cout << "Tentativa " << tries << ": ";
        cin >> guess;

        validGuess = !guess.empty() && guess.size() == wordSize;
        if (!validGuess)
        {
            cout << "  Palavra de tamanho invalido. Sua tentativa deve conter " << wordSize << " caracteres. Tente novamente." << endl;
        }
    } while (!validGuess);

    transform(guess.begin(), guess.end(), guess.begin(), ::toupper); // certificar que palavra esta em uppercase
    return guess;
}

void runGame(vector<string> &availableWords, int gameCount)
{
    cout << "Iniciando jogo..." << endl;
    cout << "Jogo " << gameCount << ". Obtendo palavra..." << endl;

    string word;
    try
    {
        word = getRandomWord(availableWords);
    }
    catch (const invalid_argument &e)
    {
        cout << "  Finalizando jogo. Motivo: " << e.what() << endl;
        exit(1);
    }

    cout << "Palavra obtida. Tente adivinhar a palavra de " << word.size() << " letras." << endl;
    cout << "Voce tem " << MAX_TRIES << " tentativas.\n"
         << endl;

    bool newGame = false;
    int tries = 1;
    while (tries <= MAX_TRIES)
    {
        string guess = getUserGuess(word.size(), tries);

        if (guess == word)
        {
            cout << "VOCE GANHOU! Foram necessarias " << tries << "/" << MAX_TRIES << " tentativas" << endl;
            newGame = true;
            break;
        }
        else
        {
            string hint = getHint(word, guess);
            cout << "  Palavra incorreta. Dica: " << hint << endl;
            tries++;
        }

        if (newGame)
        {
            cout << "  Iniciando novo jogo...\n"
                 << endl;
            break;
        }
    }

    cout << "\nVoce perdeu! A palavra certa era \"" << word << "\"." << endl;
}

void printHeader()
{
    cout << "\nBem-vindo ao Wordle/Termo Clone!" << endl;
    cout << "O jogo consiste em adivinhar uma palavras." << endl;
    cout << "A cada tentativa, o jogador recebe uma dica com letras corretas e incorretas de acordo com a posicao dos caracteres da palavra que o jogador digitou. Para entender as dicas:" << endl;
    cout << "  - Asteriscos: a palavra a ser adivinhada nao contem a letra;" << endl;
    cout << "  - Letras maiusculas: a palavra a ser adivinhada contem a letra e ela esta na posicao correta;" << endl;
    cout << "  - Letras minusculas: a palavra a ser adivinhada contem a letra mas ela esta na posicao errada." << endl;
    cout << "O jogador tem " << MAX_TRIES << " tentativas por partida para adivinhar a palavra." << endl;
    cout << "Boa sorte!\n"
         << endl;

    return;
}

int main()
{
    vector<string> allWords = readFromFile(FILENAME);
    vector<string> availableWords = allWords;

    printHeader();

    int gameCount = 1;
    int menuOption = -1;
    do
    {
        cout << "Pronto(a) para jogar a partida " << gameCount << "? (1 - Sim, 0 - Nao): ";
        cin >> menuOption;

        switch (menuOption)
        {
        case 1:
            runGame(availableWords, gameCount);
            gameCount++;
            break;
        case 0:
            cout << "Saindo do jogo..." << endl;
            return 0;
        default:
            cout << "Opcao invalida. Tente novamente." << endl;
            break;
        }
    } while (menuOption != 0);

    return 0;
}
