#include <iostream>

using namespace std;

struct  Node{
    int value;
    Node* next;

    Node(int value = 0, Node * next = nullptr){
        this->value = value;
        this->next = next;
    }
};

struct SList{

    Node* head;

    SList(){
        this->head = nullptr;
    }

    ~SList(){
        head = deletarTudo(head);
    }

    void clear(){
        head = deletarTudo(head);
    }

    Node * deletarTudo(Node * node){
        if(node == nullptr)
            return nullptr;

        deletarTudo(node->next);
        delete node;
        return nullptr;
    }

    void push_front(int value){
        Node *node = new Node(value);
        node->next = head;
        this->head = node;
    }

    void pop_front(){
       if(head == nullptr)
           return;
        auto aux = head;
        head = head->next;
        delete aux;
    }

    void push_back(int value){
        if(head == nullptr){
            head = new Node(value);
            return;
        }
        Node * node = head;
        while(node->next != nullptr){
             node = node->next;
        }
        node->next = new Node(value);
    }


    // push_back recursivo
    Node * _push_back(Node * node, int value){
        if(node->next == nullptr){
           node->next = new Node(value);
           return node;
        }
        return _push_back(node->next, value);
    }
    // push_back recursivo chamada externa
    void rpush_back(int value){
        _push_back(head, value);
    }

    void pop_back(){
        if(head == nullptr)
            return;
        if(head->next == nullptr){
            delete head;
            head = nullptr;
            return;
        }

        auto node = head;
        while(node->next->next != nullptr)
            node = node->next;
        delete node->next;
        node->next = nullptr;
    }


    // pop back recursivo
    Node * _rpop_back(Node * node){
        if(node->next == nullptr){
            delete node;
            return nullptr;
        }
        node->next = _rpop_back(node->next);
    }

    // pop back recursivo chamada externa
    void rpop_back(){
        this->head = _rpop_back(head);
    }

    void show(){
        auto node = head;
        while(node != nullptr){
            cout << node->value << " ";
            node = node->next;
        }
        cout << endl;
    }

    //Show recursivo
    void _rshow(Node * node){
        if(node == nullptr)
            return;
        cout << node->value << " ";
        _rshow(node->next);
    }

    //Show recursivo chamada externa
    void rshow(){
        _rshow(head);
        cout << endl;
    }


    // Show recursivo de tras para frente
    void trshow(){
        _trshow(head);
        cout << endl;
    }


    // Show recursivo de tras para frente, chamada externa
    void _trshow(Node * node){
        if(node == nullptr)
            return;
        _trshow(node->next);
        cout << node->value << " ";
    }

    // remove recursivo
    Node * _remove(Node * node, int value){
        if(node == nullptr)
            return nullptr;
        if(node->value == value){
            auto aux = node->next;
            delete node;
            return aux;
        }
       return node->next = _remove(node->next, value);
    }

    void rremove(int value){
        head = _remove(head, value);
    }

    void remove(int value){
        if(head == nullptr)
            return;
        if(head->value == value){
            delete head;
            head = nullptr;
            return;
        }

        auto node = head;
        while(node->next->value != value){
            if(node->next == nullptr)
                return;
            node = node->next;

        }

        auto aux = node->next->next;
        delete node->next;
        node->next = nullptr;
        node->next = aux;
    }

    void inserir_ordenado(int value){
        auto node = head;
        if(head == nullptr || head->value > value){
            this->head = new Node(value, head);
            return;
        }
        while(node->next != nullptr && node->next->value < value){
            node = node->next;
        }
        node->next = new Node(value, node->next);
    }

    // inserir ordenado recursivo
    Node * _rinserir_ordenado(Node * node, int value){

        if(node == nullptr)
            return new Node(value, node->next);
        if(node->value > value)
            return head = new Node(value, node);

        if(node->next == nullptr || node->next->value > value){
            return node->next = new Node(value, node->next);
        }

        return _rinserir_ordenado(node->next, value);
    }

    void rinserir_ordenado(int value){
        _rinserir_ordenado(head, value);
    }

    int rsize(){
        return _rsize(head);
    }

    // size recursivo
    int _rsize(Node * node){
        if(node == nullptr)
            return 0;
        return 1 + _rsize(node->next);
    }

    // size interativo
    int size(){
       int count = 0;
       auto node = head;
       while(node != nullptr){
           count++;
           node = node->next;
       }
       return count;
    }

    // soma recursivo
    int _rsomar(Node * node){
        if(node->next == nullptr)
            return node->value;
        return node->value + _rsomar(node->next);
    }

    int rsomar(){
         return _rsomar(head);
    }

    int soma() {
        int total = 0;
        auto node = head;
        while(node->next != nullptr)
            total += node->value;
        return total;
    }

    // minimo recursivo
    int _rmin(Node * node){
        if(node->next == nullptr)
            return node->value;
        return std::min(node->value, _rmin(node->next));
    }

    int rmin(){
        return _rmin(head);
    }

    int min(){
        if(head == nullptr)
            return 0;

        int min = head->value;
        auto node = head;

        while(node->next != nullptr){
            min = std::min(min, node->next->value);
            node = node->next;
        }

        return min;
    }


    // Arranca Rabo Recursivo
    Node * _arrancaRabo(Node * node, int value){
        if(node == nullptr)
            return nullptr;
        node->next = _arrancaRabo(node->next, value);
        if(node->next == nullptr){
            if(node->value != value){
                delete node;
                return nullptr;
            }else
                return node;
        }
        return node;
    }

    void arrancaRabo(int value){
        _arrancaRabo(head, value);
    }

    // Arranca Venta Recursivo
    Node * _arrancaVenta(Node * node, int value){
        if(node == nullptr)
            return nullptr;
        if(node->value == value)
            return node;

        auto aux = node;
        delete node;
        node = nullptr;
        aux = _arrancaVenta(aux->next, value);
        return aux;
    }

    void arrancaVenta(int value){
        head = _arrancaVenta(head, value);
    }

};

int main(){

    SList lista;

    cout << "incluir 10 valores com push_back interativo" << endl;
    for(int i = 0; i < 10; i++)
        lista.push_back(i+1);

    cout << "Exibe com show interativo" << endl;
    lista.show();

    cout << "Exibe com show de tras pra frente" << endl;
    lista.trshow();

    cout << "incluir 11 com push_back recursivo" << endl;
    lista.rpush_back(11);

    cout << "incluir -11 com push_front" << endl;
    lista.push_front(-11);

    cout << "Exibe com show recursivo" << endl;
    lista.rshow();

    cout << "pop_front" << endl;
    lista.pop_front();
    lista.rshow();

    cout << "pop_back interativo" << endl;
    lista.pop_back();
    lista.rshow();

    cout << "pop_back recursivo" << endl;
    lista.rpop_back();
    lista.rshow();

    cout << "remove 5 interativo" << endl;
    lista.remove(5);
    lista.rshow();

    cout << "remove  3 recursivo" << endl;
    lista.rremove(3);
    lista.rshow();

    cout << "inserir ordenado  3 interativo" << endl;
    lista.inserir_ordenado(3);
    lista.rshow();

    cout << "inserir ordenado  5 recursivo" << endl;
    lista.rinserir_ordenado(5);
    lista.rshow();

    cout << "inserir ordenado  -7 recursivo" << endl;
    lista.rinserir_ordenado(-5);
    lista.rshow();

    cout << "Size interativo: " << lista.size() << endl;
    cout << "Size recursivo: " << lista.rsize() << endl;

    cout << "soma recursivo: " << lista.rsomar() << endl;

    cout << "min interativo: " << lista.min() << endl;
    cout << "min recursivo: " << lista.rmin() << endl;

    cout << "Arranca Rabo: " << endl;
    lista.arrancaRabo(7);
    lista.rshow();

    cout << "Arranca Venta: " << endl;
    lista.arrancaVenta(3);
    lista.rshow();


    cout << "Clear Lista: " << endl;
    lista.clear();
    lista.rshow();

    return 0;
}
