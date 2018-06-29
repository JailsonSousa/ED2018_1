#include <vector>
#include <list>
#include <algorithm>
#include <ctime>//funcao time
#include <cstdlib> //funcao srand
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

//Cada dia possui 6 horas de trabalho
//60 minutos x 6 horas = 360 minutos
//cada minuto eh um turno.
const int TURNOS_DIA = 360;

//A quantidade máxima de caixa.
const int MAX_CAIXAS = 10;

//Esse valor determina o quanto o banco por caixa por dia de trabalho
const int CUSTO_CAIXA_DIA = 100;

//numero de simulacoes de teste
const int N_EXEC_TESTE = 100;

struct Cliente
{
    int paciencia;
    int documentos;
    std::string nome;

    Cliente(int paciencia, int documentos)
    {
        gerarNomeAleatorio();
        this->paciencia = paciencia;
        this->documentos = documentos;
    }

    void gerarNomeAleatorio(){
        std::string consoantes = "bcdfghjklmnpqrstvxyz";
        std::string vogais = "aeiou";
        this->nome = std::string(1, consoantes[std::rand() % consoantes.size()]);
        this->nome += std::string(1, vogais[std::rand() % vogais.size()]);
    }
};



//gera um numero entre min e max, [min, max]
int rand_mm(int min, int max){
    static int init = 1;
    if(init){
        init = 0;
        srand(time(NULL));
    }
    return rand() % (max - min + 1) + min;
}

std::string to_string(const Cliente *cliente){
    std::stringstream str;
    str << "[" << cliente->nome << ":";
    str << "d" << setw(2) << cliente->documentos <<
           ":p" << setw(2) << cliente->paciencia << "]";
    return str.str();
}


void print_banco(list<Cliente *> fila, vector<Cliente *> caixas, int turno, int lucro){
    Cliente dummy(0, 0);
    int slot = to_string(&dummy).size();//quandos caracteres ocupa um cliente
    std::cout << string(1 + (slot - 1) * MAX_CAIXAS, '#') << std::endl;
    std::cout << "|";
    for(auto& x : caixas){
        if(x == nullptr)
            cout << std::string(slot - 2, ' ');
        else
            cout << to_string(x);
        cout << "|";
    }
    for(int x = 0; x < MAX_CAIXAS - (int) caixas.size(); x++)
        std::cout << std::string(slot - 2, '-') << "|";
    std::cout << endl;
    std::cout << "-" << std::string(slot - 2, ' ') << std::string((slot - 1) * MAX_CAIXAS, '-') << std::endl;

    std::cout << " ";
    int ind = 1;
    for(auto it = fila.begin(); it != fila.end(); it++, ind++){
        if(ind % MAX_CAIXAS == 0)
            cout << endl << " ";
        cout << to_string(*it) << " ";
    }
    std::cout << std::endl;
    std::cout << std::string(1 + (slot - 1) * MAX_CAIXAS, '#') << std::endl;
    std::cout << "Turno : " << turno << endl;
    std::cout << "Lucro : " << lucro << endl;
}

//pac é paciencia do cliente, entre min e max
//doc é a quantidade de documentos do cliente
//cli é a quantidade de clientes que entra por minuto
//numCaixas é o número de caixas no banco

int simulacao(pair<int, int> pac, pair<int, int> doc, pair<int, int> cli, int numCaixas){
    std::vector<Cliente*> caixa(numCaixas);
    std::list<Cliente*> filaClientes;

    int turno = 1; // Inicia o turno de trabalho
    int lucro = 0; // Inicialmente sem lucro

    //enquanto o banco estiver aberto ou houver clientes no banco faça:
    while( (turno <= TURNOS_DIA ) || (filaClientes.size() !=  0)){
        //gera aleatoriamento clientes
        int qtd = rand_mm(cli.first,cli.second);
        // insere na fila de espera
        for(int i = 0; i < qtd;i++)
            filaClientes.push_back(new Cliente (rand_mm(pac.first, pac.second), rand_mm(doc.first, doc.second)));

        //para cada caixa
        for(int i = 0; i < numCaixas ; i++){
            //se o caixa esta vazio, chama alguém da fila de espera
            if((caixa[i] == nullptr) && (filaClientes.size() != 0)){
                caixa[i] = filaClientes.front();
                filaClientes.pop_front();

                //se tem cliente no caixa, enquanto tiver documento,
                //decremente um documento do cliente e incremente 1 no lucro do banco
                while(caixa[i]->documentos > 0){
                    caixa[i]->documentos--;
                    lucro++;
                }

                //se nao tem mais documentos
                //envia o cliente para casa
                auto caixaAux = caixa[i];
                delete caixaAux;
                caixa[i] = nullptr;
            }
        }

        //para cada cliente da fila de espera
        for(auto it = filaClientes.begin();it != filaClientes.end();){
            // se ainda tem paciencia, decremente
            if((*it)->paciencia !=0){
                (*it)->paciencia--;
                it++;
            }else{
                //se a paciencia for 0, retira cliente do banco
                it = filaClientes.erase(it);
            }
        }

        turno++; // aumenta um turno
    }

    return lucro - (numCaixas * CUSTO_CAIXA_DIA);
}


int main (){

    vector<int> lucroCaixa(MAX_CAIXAS);

    cout <<"Lucro dos caixas"<< endl;
    for (int var = 0; var < MAX_CAIXAS; ++var)
        lucroCaixa[var] = 0;

    // rodar a simulação para todos os caixas
    for(int i = 0; i <= MAX_CAIXAS; ++i){
        for(int qtdTeste = 0 ; qtdTeste < N_EXEC_TESTE ; qtdTeste++){
            lucroCaixa[i] += simulacao({1,5},{1,3},{0,3},i);
        }
        // lucro médio dos caixas é total do caixa atual / quantidade de testes
        lucroCaixa[i] = lucroCaixa[i]/N_EXEC_TESTE;
    }

    // exibir o lucro de todos os caixas
    for(int i = 1; i <= MAX_CAIXAS; i++)
        cout << "Caixa "<< i <<" Lucro Médio: " <<lucroCaixa[i]<< endl;

    return 0;
}
