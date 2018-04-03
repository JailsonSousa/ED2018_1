#include <stdio.h>
#include <iostream>
#include <list>

using namespace std;

void rodar(list<int> &lista){
    lista.push_back(lista.front());
    lista.pop_front();
}

void saltos(list<int> &lista, int qtd){
    for (int i = 0; i < qtd; i++) {
        lista.push_back(lista.front());
        lista.pop_front();
    }
}

void mostrarLista(list<int> &lista){

    for(auto jogador : lista){
        cout << jogador << " ";
    }
    cout << "\n";
}


int main(){

    int qtd = 0;
    int primeiro = 0;
    int nSaltos = 0;

    cout << "Informe a quantidade de jogadores." << endl;
    cin >> qtd;

    cout << "Informe quem será o primeiro jogador." << endl;
    cin >> primeiro;

    cout << "Deseja modificar a quantidade de saltos?." << endl;
    cout << "0 - Não | 1 - Sim." << endl;
    cin >> nSaltos;

    if(nSaltos >= 1) {
        cout << "Informe a quantidade de saltos." << endl;
        cin >> nSaltos;
    }

    list<int> lista;

    for(int i = 1; i <= qtd; i++)
        lista.push_back(i);

    while(lista.front() != primeiro)
        rodar(lista);

    mostrarLista(lista);

    while(lista.size() > 1){
        rodar(lista);
        lista.pop_front();
        mostrarLista(lista);
        saltos(lista, nSaltos);
    }
    return 0;
}
