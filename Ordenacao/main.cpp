#include <iostream>
#include <ctime>
#include <cstdlib> //rand
#include "libs/ed_sort.h"

using namespace std;


void swapSort(vector<int>& vet){
    int sizeVet = vet.size();
    for(int i = 0; i < sizeVet - 1; i++){
        view_set_faixa(i, sizeVet - 1);
        for(int j = i + 1; j < sizeVet; j++){
            view_show(vet, {i, j}, "yg");
            if(vet[j] < vet[i]){
                swap(vet[i], vet[j]);
                view_show(vet, {i, j}, "yg");
            }
        }
    }
}

// Ordena da esquerda para a direita (Menor para o maior)
void selectionSort(vector<int>& vet){
    int sizeVet = vet.size();
    for(int i = 0; i < sizeVet - 1; i++){
        int menor = i;
        view_set_faixa(i, sizeVet - 1);
        for(int j = i + 1; j < sizeVet; j++){
            view_show(vet, {i, j, menor}, "ygr");
            if(vet[j] < vet[menor]){
                menor = j;
                view_show(vet, {i, j, menor}, "ygr");
            }
        }
        swap(vet[menor], vet[i]);
    }
}


// Ordena da direita para a esquerda (maior para o menor)
void reverseMinimumSort(vector<int>& vet){
    int ultimo = vet.size() - 1;
    for(int i = 0; i <= ultimo; ultimo--){
        int maior = ultimo;
        for(int j = 0; j < ultimo; j++){
            view_show(vet, {j, maior, ultimo}, "ygr");
            if(vet[j] > vet[maior]){
                maior = j;
                view_show(vet, {j, maior, ultimo}, "ygr");
            }
        }
        swap(vet[maior], vet[ultimo]);
    }
}

// Ordena do menor para o maior e do maior para o menor
void palmaSort(vector<int>& vet){
    int ultimo = vet.size() - 1;
    for(int i = 0; i <= ultimo; i++, ultimo--){
        int maior = i;
        int menor = i;
        view_set_faixa(i, ultimo);
        for(int j = i; j <= ultimo; j++){
            view_show(vet, {i, j, menor, maior, ultimo}, "rgyyr");
            if(vet[j] < vet[menor]){
                menor = j;
                view_show(vet, {i, j, menor, maior, ultimo}, "rgyyr");
            }
            else if(vet[j] > vet[maior]){
                maior = j;
                view_show(vet, {i, j, menor, maior, ultimo}, "rgyyr");
            }
        }
        swap(vet[menor], vet[i]);
        if(maior == i)
            maior = menor;
        swap(vet[maior], vet[ultimo]);
        view_show(vet, {i, menor, maior, ultimo}, "ryyr");
    }
}

// Ordena empurrando o maior para a ultima posição
void bubbleSort(vector<int>& vet){
    int vetSize = vet.size();
    for(int i = vetSize - 1; i > 0; i--){
        for(int j = 0; j < i; j++){
            view_show(vet, {i, j, j + 1}, "rgy");
            if(vet[j] > vet[j + 1]){
                swap(vet[j], vet[j + 1]);
                view_show(vet, {i, j, j + 1}, "rgy");
            }
        }

    }
}

// Ordena empurrando os menores valores para o inicio.
void insertionSort(vector<int>& vet){
    int vetSize = vet.size();
    for(int i = 1; i < vetSize; i++){
        for(int j = i; j > 0; j--){
            view_show(vet, {i, j, j - 1}, "rgy");
            if(vet[j] < vet[j - 1]){
                swap(vet[j], vet[j - 1]);
                view_show(vet, {i, j, j - 1}, "ryg");
            }else{
                break;
            }
        }

    }
}


// Algoritmos de ordenação usando recursão

#define qshow view_show(vet, {inicio, fim, i, j}, "rgby")
void quickSort(vector<int> & vet, int inicio, int fim){
    if(inicio >= fim)
        return;
    int pivo = vet[inicio];
    int i = inicio;
    int j = fim;
    while(i <= j){
        while(vet[i] < pivo){
               i++;
               qshow;
        }
        while(vet[j] > pivo){
            j--;
            qshow;
        }
        if(i <= j){
           swap(vet[i], vet[j]);
           i++;
           j--;
           qshow;
        }
    }
    quickSort(vet, inicio, j);
    quickSort(vet, i, fim);
}

void merge(vector<int>& vet, int inicio, int meio, int fim){
    int i = inicio;
    int j = meio;
    vector<int> vaux;
    vaux.reserve(fim - inicio);
    while((i < meio) && (j < fim)){
        if(vet[i] < vet[j])
            vaux.push_back(vet[i++]);
        else
            vaux.push_back(vet[j++]);
        view_show(vet, {inicio, meio, fim, i, j}, "rgbyc");
    }
    while(i < meio){
        vaux.push_back(vet[i++]);
        view_show(vet, {inicio, meio, fim, i, j}, "rgbyc");
    }
    while(j < fim){
        vaux.push_back(vet[j++]);
        view_show(vet, {inicio, meio, fim, i, j}, "rgbyc");
    }
    for(int i = 0; i < (int) vaux.size(); i++){
        vet[inicio + i] = vaux[i];
        view_show(vet, {inicio + i}, "r");
    }
}

void mergeSort(vector<int>& vet, int inicio, int fim){
    if(fim == inicio + 1)
        return;
    int meio = (inicio + fim)/2;
    mergeSort(vet, inicio, meio);
    mergeSort(vet, meio, fim);
    merge(vet, inicio, meio, fim);
}

void test_sort(vector<int>& vet){
    int vetSize = vet.size();
    for(int i = 0; i < vetSize - 1; i++){
        if(vet[i] <= vet[i + 1])
            view_show(vet, {i, i + 1}, "gg");
        else{
            view_show(vet, {i, i + 1}, "rr");
            view_lock();
        }
    }
}

int main(){
    srand(time(NULL));

    const int qtd = 30;
    vector<int> vet(qtd, 0);

    int min = 10;
    int max = 400;

    for(int i = 0; i < qtd; i++)
        vet[i] = (rand() % (max - min + 1) + min);

//    view_set_dot();
    view_set_bar();
//    view_set_faixa(0, qtd - 1);

    // algoritmos de ordenação interativo

    //swapSort(vet);
    //selectionSort(vet);
    //reverseMinimumSort(vet);
    //palmaSort(vet);
    //bubbleSort(vet);
    //insertionSort(vet);


    // algoritmos de ordenação recursivo
    // dividir e conquistar

    //quickSort(vet, 0, vet.size() - 1);
    mergeSort(vet, 0, vet.size());

    test_sort(vet);
    view_lock();
    return 0;
}





















