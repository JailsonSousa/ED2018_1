#include <iostream>
#include <vector>

using namespace std;


const int nc = 60;
const int nl = 20;

struct Par{
    int l, c;
    Par(int l = 0, int c = 0){
        this->l = l;
        this->c = c;
    }
};

vector<Par> getNeib(Par p){
    vector<Par> v;
    v.push_back(Par(p.l, p.c + 1));
    v.push_back(Par(p.l, p.c - 1));
    v.push_back(Par(p.l + 1, p.c));
    v.push_back(Par(p.l - 1, p.c));
    return v;
}

void mostrar(vector<string>& mat){
    cout << string(50, '\n');
    for(string s : mat)
        cout << s << endl;
    getchar();
}


vector<Par> embaralhar(vector<Par> vet){
    for(int i = 0; i < (int) vet.size(); i++){
        int random = rand() % vet.size();
        swap(vet[i], vet[random]);
    }
    return vet;
}

int queimar(vector<string> &mat, int l, int c, int nivel){

    int total = 0;

    if(l < 0 || l >= nl)
        return 0;
    if(c < 0 || c >= nc)
        return 0;
    if(mat[l][c] != '#')
        return 0;

    mat[l][c] = '0' + (nivel % 10);
    mostrar(mat);
    nivel++;
    total++;
    for(Par p : embaralhar(getNeib(Par(l, c)))){
        total += queimar(mat, p.l, p.c, nivel);
    }

    mat[l][c]='-';
    mostrar(mat);
    return total;
}


int main()
{
    srand(time(NULL));
    //os containers tem uma construção padrao
    //container<tipo> nome(qtd, elemento_default)
    //cria um vetor de string
    //com nl elementos da string default
    //a string default sao 30 char ' '
    vector<string> mat(nl, string(nc, '#'));
//    int narvores = nl * nc * 1.5;
    //insere varias arvores em lugares aleatorios
    //muitas serao superpostas
//    for(int i = 0; i < narvores; i++){
//        mat[rand() % nl][rand() % nc] = '#';
//    }
    mostrar(mat);
    int total = queimar(mat, 0, 0, 0);
    cout << "Total de arvores queimada: "<<total ;
    getchar();
    return 0;
}
