#include <iostream>

using namespace std;

struct Vetor{
    int * data;
    int _capacity;
    int _size;

    Vetor(int capacity){
        this->_capacity = capacity;
        this->_size = 0;
        this->data = new int[capacity];
    }

    void push_back(int value){
        if(this->_size == this->_capacity)
            this->reserve(2 * this->_capacity);

        this->data[this->_size] = value;
        this->_size += 1;
    }

    void pop_back(){
        if(this->_size == 0)
            return;

        this->data[this->_size] = 0;
        this->_size -= 1;
    }

    int& at(int index){
        return this->data[index];
    }

    int& front(){
        return this->data[0];
    }

    int& back(){
        return this->data[this->_size - 1];
    }

    int * begin(){
        return &this->data[0];
    }

    int * end(){
        return &this->data[this->_size];
    }

    int size(){
        return this->_size;
    }

    int capacity(){
        return this->_capacity;
    }

    void reserve(int capacity){

        if(this->_capacity < capacity)
            return;

        int * newVector = new int[this->_size * 2];

        for (int i = 0; i < this->_size; i++) {
            newVector[i] = this->data[i];
        }

        this->_capacity = capacity;
        this->data = newVector;
    }
};

#include <vector>
int main()
{
    Vetor vetor(1);

    vetor.push_back(1);
    vetor.push_back(2);
    vetor.push_back(3);
    vetor.push_back(4);

    for(auto elemento : vetor)
        cout << elemento << "\n";

    cout << "Teste AT: \n";
    for (int i = 0; i < vetor.size(); i++) {
        cout << "O Elemento do índice["<< i << "] é: "<< vetor.at(i) <<"\n";
    }

    cout << "Mudar valor no AT \n";
    vetor.at(0) = 10;
    cout << "Novo Valor do Indice[0]: " << vetor.at(0) << "\n";

    cout << "Capacidade do Vetor: " << vetor.capacity() << "\n";
    cout << "Size do Vetor: " << vetor.size() << "\n";

    cout << "Teste Reserve \n";
    vetor.reserve(30);
    cout << "Nova capacidade: " << vetor.capacity() << endl;

    return 0;
}










