#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int friend1, friend2; //declarar e ler posicoes do amigo 1 e 2
    cin >> friend1 >> friend2;
    //cout << friend1 << " - " << friend2;

    int distanceDiff = abs(friend1 - friend2); //encontrar diferenca de distancia dos 2 amigos
    int halfDistanceDiff = (distanceDiff + 1) / 2; //pegar metade arredondado para cima da distancia dos 2 amigos

    int sum1toN_2 = (halfDistanceDiff * (1 + halfDistanceDiff)) / 2; //pegar o somatorio (progressao aritmetica) de 1 ate a metade da distancia dos amigos
    int result = (2 * sum1toN_2) - ((distanceDiff % 2) * halfDistanceDiff); //multiplicar o resultado por 2 e verificar se sobrou uma soma (para distancias impares) para interar a distancia

    //Exemplo de execucao: (2 somatorios --> ex: distanceDiff = 5 --> 1 + 1 + 2 + 2 + 3) --> 2*sum(1->3) - (1 * 3) --> 9
    //Exemplo de execucao: (2 somatorios --> ex: distanceDiff = 4 --> 1 + 1 + 2 + 2) --> 2*sum(1->2) - (0 * 2) --> 6

    cout << result << endl;

    return 0;
}
