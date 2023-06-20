#include <iostream>
#include "RB.h"

using namespace std;

int main(){
    setlocale(LC_ALL, "portuguese");

    RB *rb = RB::criar(1);

    int i, N = 9, val[9] = {11,2,1,5,4,7,8,14,15};

    for(i=0; i< N; i++){

        rb->inserir(val[i]);
    }

    cout << "Pré-ordem:" << std::endl;
    rb->preOrdem();
    cout << endl;

    cout << "Em-ordem:" << std::endl;
    rb->emOrdem();
    cout << endl;

    cout << "Pós-ordem:" << std::endl;
    rb->posOrdem();
    cout << endl;

    cout << "Largura:" << endl;
    rb->largura();
    cout << endl << endl;
    cout << "Altura: " << rb->altura() << endl;

    cout << "\n3? " << rb->buscar(3);
    cout << "\n5? " << rb->buscar(5) << endl;

    return 0;
}