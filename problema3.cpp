#include <iostream>
#include <cmath>
#include <string.h>

//Obs: habilitar linhas para printar a newSequence no final do codigo caso necessario exibir o array re ordenado da maneira pedida (linhas marcadas com //-->)

using namespace std;

int seqSize;
int sequence[1000]; //ja setado no tamanho maximo para evitar ficar passando na pilha de chamada de funcao
bool used[1000]; //se o numero da sequencia ja foi utilizado
int fibonacciAux[1000]; //auxiliar para a geracao de um fibonacci

void seq_swap(int i, int j){ //troca duas posicoes do array sequence
    int aux = sequence[i]; //realizar o swap das duas posicoes
    sequence[i] = sequence[j];
    sequence[j] = aux;
}

void quickSort(int start, int finish){ //ordena o array sequence (escolhido por eficiencia em conjuntos pequenos e no uso de memoria)
    int i = start, j = finish,
        pivot = sequence[(start + finish) / 2]; //declarar variaveis iniciais

    while(i <= j){
        while(sequence[i] < pivot) i++; //re posicionar ponteiro do inicio
        while(sequence[j] > pivot) j--; //re posicionar ponteiro do final

        if(i <= j){
            seq_swap(i, j);
            i++; j--; //re ajustar os valores dos indexes
        }
    }

    if(j > start) quickSort(start, j); //se j nao for o inicio do array sequence
    if(i < finish) quickSort(i, finish); //se i nao for o final do array sequence
}


int binarySearch (int value){ //procurar um valor no array da sequencia
     int start = 0, finish = seqSize - 1, middle; //definir extremidades
     while (start <= finish)
     {
          middle = (start + finish) / 2; //atualizar meio
          if (value == sequence[middle] && !used[middle]) return middle; //caso encontre o valor (e ainda nao foi utilizado), retornar o indice
          if (value < sequence[middle]) finish = middle - 1; //atualizar final
          else start = middle + 1; //atualizar inicio
     }
     return -1; //retornar -1 --> nao encontrou
}

int main()
{
    cin >> seqSize;

    int i, j, k, fAuxCount = 0, indexAux;
    for(i = 0; i < seqSize; i++) cin >> sequence[i]; //ler cada elemento da entrada

    quickSort(0, seqSize - 1); //ordenar array sequence de entrada
    //for(i = 0; i < seqSize; i++) cout << sequence[i] << " ";
    //cout << endl;

    int seqIndexesFinal[seqSize], seqIndexesAux[seqSize]; //array de sequencia para reordenar o array original
    int seqIndexesPos = 2;
    bool usedFinal[seqSize];

    memset(seqIndexesFinal, -1, sizeof(seqIndexesFinal)); //inicializar com -1

    for(i = 0; i < seqSize; i++){
        for(j = 0; j < seqSize; j++){ //pegar todas as combinacoes de iniciais
            if(i == j) continue; //caso i == j, passar para a proxima iteracao

            memset(seqIndexesAux, -1, sizeof(seqIndexesAux)); //re setar com -1

            seqIndexesAux[0] = i; //setar indexes para posterior reordenacao
            seqIndexesAux[1] = j;

            memset(used, false, sizeof(used)); //re setar array de numeros utilizados

            seqIndexesPos = 2;
            fibonacciAux[0] = sequence[i];
            fibonacciAux[1] = sequence[j];
            used[i] = true;
            used[j] = true;

            for(k = 2; k < seqSize; k++){ //gerar um fibonacci auxiliar
                fibonacciAux[k] = fibonacciAux[k - 1] + fibonacciAux[k - 2];
                indexAux = binarySearch(fibonacciAux[k]); //procurar numero gerado

                if(indexAux == -1) break; //se nao encontrar numero, sair do loop e ir para a proxima combinacao possivel do array sequence

                used[indexAux] = true; //marcar como usado
                seqIndexesAux[seqIndexesPos++] = indexAux; //adicionar na sequecia de indices
            }

            if(fAuxCount < seqIndexesPos){ //se o tamanho da sequencia encontrada superar maior tamanho anterior
                fAuxCount = seqIndexesPos; //atualizar tamanho maximo
                memcpy(seqIndexesFinal, seqIndexesAux, sizeof(seqIndexesFinal)); //atualizar array com a sequencia de indices utilizados
                memcpy(usedFinal, used, sizeof(usedFinal)); //atualizar array com a sequencia de indices utilizados
            }
        }
    }

    int newSequence[seqSize];
    for(i = 0; i < seqSize && seqIndexesFinal[i] != -1; i++){ //preencher valores da sequencia
        newSequence[i] = sequence[seqIndexesFinal[i]];
    }
    for(j = 0; j < seqSize; j++){ //preencher valores restantes
        if(!usedFinal[j]) newSequence[i++] = sequence[j];
    }

    cout << fAuxCount << endl;
//--> for(i = 0; i < seqSize; i++) cout << newSequence[i] << " "; //printar caso necessario exibir o array re ordenado da maneira pedida
//--> cout << endl;

    //Exemplo de execucao: 3 --> 1 2 -1 --> 3 (newSequence --> -1 2 1)
    //Exemplo de execucao: 5 --> 28 35 7 14 21 --> 4 (newSequence -->  7 14 21 35 28)

    return 0;
}
