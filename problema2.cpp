#include <iostream>

using namespace std;

//OBS: Eh importante notar que devido ao acento de "inválido", pode ocorrer "prints" diferentes a depender do sistema operacional e da codificacao

bool board_checkWin(char board[], char whoWin) //checa se determinada pessoa ganhou (necessario para tratar casos, por exemplo, XXX...000, onde os 2 ganham --> tabuleiro invalido)
{
    if((board[0] == whoWin &&
        ((board[0] == board[1] && board[1] == board[2])
         || (board[0] == board[3] && board[3] == board[6]))) ||
       (board[4] == whoWin &&
        ((board[0] == board[4] && board[4] == board[8])
         || (board[1] == board[4] && board[4] == board[7])
         || (board[2] == board[4] && board[4] == board[6])
         || (board[3] == board[4] && board[4] == board[5]))) ||
       (board[8] == whoWin &&
        ((board[2] == board[5] && board[5] == board[8])
         || (board[6] == board[7] && board[7] == board[8])))) return true; //se ocorrer alguma dessas combinacoes, retornar que "ganhou"

    return false; //retornar que nao "ganhou"
}

int main()
{
    char board[9]; //declarar e ler tabuleiro
    int qtdX = 0, qtd0 = 0;

    int i, j, aux;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            aux = (i * 3) + j;
            cin >> board[aux]; //ler tabuleiro (feito assim para "otimizar" retorno da memoria (apesar de ja ser estatico))

            if(board[aux] == 'X') qtdX++; //marcar quantidade de Xs e 0s
            else if(board[aux] == '0') qtd0++;
        }
    }

//    for(i = 0; i < 3; i++){
//        for(j = 0; j < 3; j++){
//            cout << board[(i * 3) + j];
//        }
//        cout << endl;
//    }

    if(qtd0 > qtdX || qtd0 < (qtdX - 1)){ //se a quantidade de Xs eh maior que a de 0s ou se a qtd de 0s eh menor que a de Xs-1, invalido
        cout << "inválido" << endl;
        return 0;
    }

    //verificar se alguem ganhou
    bool winX = board_checkWin(board, 'X'); //verificar se o X ganhou
    bool win0 = board_checkWin(board, '0'); //verificar se o 0 ganhou

    if(winX && win0){ //se os 2 ganharam, invalido
        cout << "inválido" << endl;
    }else if(winX){ //se o primeiro ganhou
        cout << "primeiro_venceu" << endl;
    }else if(win0){ //se o segundo ganhou
        cout << "segundo_venceu" << endl;
    }else{ //se ninguem ganhou
        if(qtd0 == 4){ //se o jogo terminou (empate --> maximo de jogadas do segundo)
            cout << "empate" << endl;
        }else if(qtd0 == qtdX){ //se o primeiro jogou a mesma quantidade do segundo, vez do primeiro
            cout << "primeiro" << endl;
        }else{ //caso contrario, vez do segundo
            cout << "segundo" << endl;
        }
    }

    /*Exemplos de execucao: X0X
                            .0.
                            .X.  --> segundo

                            X0X
                            .X.
                            .X.  --> inválido

                            XXX
                            .00
                            .X0  --> primeiro_venceu

                            XXX
                            ...
                            000  --> invalido
    */

    return 0;
}
