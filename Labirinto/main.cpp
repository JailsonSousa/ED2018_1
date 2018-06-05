#include "libs/ed_base.h"
#include "libs/ed_mat.h"

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

const char PAREDE = 'k';
const char ABERTO = 'w';
const char EMBUSCA = 'y';
const char CAMINHO = 'b';
const char ABATIDO = 'm';

void showMat(matchar& mat, vector<Par> pilha, Par inicio, Par fim){
    mat_draw(mat);
    for(Par par : pilha)
        mat_focus(par, 'c');
    if(pilha.size() > 0)
        mat_focus(pilha.back(), 'k');
    mat_focus(inicio, 'g');
    mat_focus(fim, 'r');
}

// pega vizinho
vector<Par> getNeib(Par par){
    vector<Par> vizinhos;
    vizinhos.push_back(Par(par.l + 1, par.c));
    vizinhos.push_back(Par(par.l - 1, par.c));
    vizinhos.push_back(Par(par.l, par.c + 1));
    vizinhos.push_back(Par(par.l, par.c - 1));
    return vizinhos;
}

// conta vizinhos aberto
int countOpen(matchar &mat, Par par){
    int cont = 0;
    for(auto vizinho : getNeib(par))
        if(!mat.is_inside(vizinho) || mat.get(vizinho) != PAREDE)
            cont++;
    return cont;
}

// embaralhar matriz
vector<Par> shuffle(vector<Par> vet){
    random_shuffle(vet.begin(), vet.end());
    return vet;
}

void criarLabirinto(matchar &mat, Par pontoInicial){
    vector<Par> pilha;
    pilha.push_back(pontoInicial);
    mat.get(pontoInicial) = ABERTO;
    while (pilha.size() > 0) {
        Par topo = pilha.back();
        vector<Par> paredes;
        for(auto vizinhoValido : getNeib(topo))
            if(mat.equals(vizinhoValido, PAREDE) && countOpen(mat, vizinhoValido) <= 1 )
                paredes.push_back(vizinhoValido);
        if(paredes.size() == 0)
            pilha.pop_back();
        else{
            Par posValida = paredes[rand() % paredes.size()];
            mat.get(posValida) = ABERTO;
            pilha.push_back(posValida);
            mat_draw(mat);
            ed_show();
        }
    }
}

//solução do labirinto com pilha
bool findPath(matchar& mat, Par inicio, Par final){
    vector<Par> pilha;
    pilha.push_back(inicio);
    mat.get(inicio) = EMBUSCA;

    while(pilha.size() != 0){
        Par topo = pilha.back();
        if(topo == final){
            showMat(mat, pilha, inicio, final);
            ed_show();
            return true;
        }
        vector<Par> abertos;
        showMat(mat, pilha, inicio, final);
        for(Par par : getNeib(topo)){
            if(mat.get(par) == ABERTO){
                abertos.push_back(par);
                mat_focus(par, 'r');
            }
        }
        ed_show();
        if(abertos.size() == 0){
            pilha.pop_back();
            showMat(mat, pilha, inicio, final);
            ed_show();
        }else{
            Par escolhido = abertos[rand() % abertos.size()];
            mat.get(escolhido) = EMBUSCA;
            pilha.push_back(escolhido);
            showMat(mat, pilha, inicio, final);
            ed_show();
        }
    }
    showMat(mat, pilha, inicio, final);
    ed_show();
    return false;
}

int main(){
    srand(time(NULL));
    matchar mat(20, 60, PAREDE);
    criarLabirinto(mat, Par(1, 1));// cria labirinto com pilha
    mat_draw(mat);
    ed_show();
    Par inicio = mat_get_click(mat, "digite o local de inicio");
    Par final = mat_get_click(mat, "digite o local de fim");
    mat_draw(mat);
    ed_show();

    findPath(mat, inicio, final); // solução do labirinto com pilha
    ed_lock();//impede que termine abruptamente
    return 0;
}


