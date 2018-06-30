#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;


enum Marcador {VAZIO, CHEIO, DELETADO};

struct Elem {
    int key;
    string value;

    Elem(int key = 0, string value = ""){
        this->key = key;
        this->value = value;
    }

    bool operator ==(Elem other){
        return key == other.key;
    }

    friend ostream& operator << (ostream& os, Elem e){
        os << e.key;
        return os;
    }
};


struct hashLinear{

    pair<Elem, Marcador> * vet;
    int capacity;
    int size;

    hashLinear(int capacity){
        this->vet = new pair<Elem, Marcador>[capacity];
        this->capacity = capacity;
        this->size = 0;
    }

    int find(Elem elem){
        int posBase = elem.key % this->capacity;
        int pos = posBase;
        int i = 0;
        while(!(vet[pos].second == VAZIO) && !(vet[pos].first == elem)){
            i++;
            pos = (posBase + i * i) % this->capacity;
        }

        if(vet[pos].second == VAZIO)
            return -1;
        return pos;
    }

    bool insert(Elem elem) {
        int pos = find(elem);
        if(pos != -1)
            return false;
        pos = elem.key % this->capacity;
        while(vet[pos].second != VAZIO)
            pos = (pos + 1) % this->capacity;
        this->vet[pos].first = elem;
        this->vet[pos].second = CHEIO;
        this->size ++;
        return true;
    }

    bool remove(Elem elem){
        int pos = find(elem);
        if(pos == -1)
            return false;
        this->vet[pos].second = DELETADO;
        this->size--;
    }

    bool sm_remove(Elem elem){
        int pos = find(elem);
        if(pos == -1)
            return false;
        vet[pos].second = VAZIO;
        this-> size--;
        pos = (pos + 1) % this->capacity;
        while(vet[pos].second != VAZIO){
            vet[pos].second = VAZIO;
            insert(vet[pos].first);
            pos = (pos +1) % this->capacity;
        }
        return true;
    }


    void resize(int capacity){
        auto oldVet = vet;
        this->vet = new pair<Elem,Marcador>[capacity];
        for(int i = 0; i < this->size; i++)
            this->vet[i].second = VAZIO;

        for(int i = 0; i < this->size; i++)
            insert(oldVet[i].first);

        delete oldVet;
        oldVet = nullptr;
    }


};


int main()
{

    return 0;
}






