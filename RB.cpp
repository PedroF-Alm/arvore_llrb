#include <iostream>
#include <queue>
#include "RB.h"

#define RED 1
#define BLACK 0

#define PRE_ORDEM 0
#define EM_ORDEM 1
#define POS_ORDEM 2

struct no 
{
    int chave;
    struct no *esq;
    struct no *dir;
    int cor;
};

RB::RB()
{

}

RB* RB::criar(int valor)
{
    RB* novaRB = new RB();

    novaRB->raiz = (NO) malloc(sizeof(struct no));
    if (novaRB->raiz == NULL)
    {
        delete novaRB;
        return NULL;
    }

    novaRB->raiz->chave = valor;    
    novaRB->raiz->esq = NULL;
    novaRB->raiz->dir = NULL;
    novaRB->raiz->cor = BLACK;

    return novaRB;
}

NO criarNO(int valor)
{
        NO novo;
        novo = (NO) malloc(sizeof(struct no));
        if(novo == NULL)            
            return NULL;

        novo->chave = valor;
        novo->cor = RED;
        novo->dir = NULL;
        novo->esq = NULL;

        return novo;
}

void liberarNO(NO H)
{
    if(H == NULL)
        return;
    liberarNO(H->esq);
    liberarNO(H->dir);
    free(H);
    H = NULL;
}

RB::~RB()
{
    liberarNO(raiz);
}

int RB::buscar(int valor)
{
    if(raiz == NULL)
        return 0;

    NO atual = raiz;

    while(atual != NULL)
    {
        if(valor == atual->chave)
            return 1;
        if(valor > atual->chave)
            atual = atual->dir;
        else
            atual = atual->esq;
    }

    return 0;
}

NO rotacionaEsquerda(NO A)
{
    NO B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}

NO rotacionaDireita(NO A)
{
    NO B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}

int cor(NO H)
{
    if(H == NULL)
        return BLACK;
    else
        return H->cor;
}

void trocaCor(NO H)
{
    H->cor = !H->cor;
    if(H->esq != NULL)
        H->esq->cor = !H->esq->cor;
    if(H->dir != NULL)
        H->dir->cor = !H->dir->cor;
}

NO inserirNO(NO H, int valor, int *resp)
{
    if(H == NULL)
    {
        NO novo = criarNO(valor);
        if (!novo)
            *resp = 0;
        return novo;
    }

    if(valor == H->chave)
        *resp = 0;// Valor duplicado
    else{
        if(valor < H->chave)
            H->esq = inserirNO(H->esq, valor, resp);
        else
            H->dir = inserirNO(H->dir, valor, resp);
    }

    if(cor(H->dir) == RED && cor(H->esq) == BLACK)
        H = rotacionaEsquerda(H);

    if(cor(H->esq) == RED && cor(H->esq->esq) == RED)
        H = rotacionaDireita(H);

    if(cor(H->esq) == RED && cor(H->dir) == RED)
        trocaCor(H);

    return H;
}

int RB::inserir(int valor)
{
    int resp;

    raiz = inserirNO(raiz, valor, &resp);
    if(raiz != NULL)
        raiz->cor = BLACK;

    return resp;
}

NO balancear(NO H)
{
    // Filho à direita não pode ser vermelho
    if(cor(H->dir) == RED)
        H = rotacionaEsquerda(H);

    // Se o há dois filhos vermelhos à esquerda, rotaciona para a direta
    if(H->esq != NULL && cor(H->esq) == RED && cor(H->esq->esq) == RED)
        H = rotacionaDireita(H);

    // Se os dois filhos são vermelhos, então troca a cor do nó e de seus filhos
    if(cor(H->esq) == RED && cor(H->dir) == RED)
        trocaCor(H);

    return H;
}

NO move2EsqRED(NO H)
{
    trocaCor(H);
    if(cor(H->dir->esq) == RED)
    {
        H->dir = rotacionaDireita(H->dir);
        H = rotacionaEsquerda(H);
        trocaCor(H);
    }
    return H;
}

NO move2DirRED(NO H)
{
    trocaCor(H);
    if(cor(H->esq->esq) == RED)
    {
        H = rotacionaDireita(H);
        trocaCor(H);
    }
    return H;
}

NO removerMenor(NO H)
{
    if(H->esq == NULL)
    {
        free(H);
        return NULL;
    }
    if(cor(H->esq) == BLACK && cor(H->esq->esq) == BLACK)
        H = move2EsqRED(H);

    H->esq = removerMenor(H->esq);
    return balancear(H);
}


NO procurarMenor(NO atual)
{
    if (!atual->esq)
        return atual;
    
    return procurarMenor(atual->esq);
}

NO removerNO(NO H, int valor)
{
    if (!H)
        return NULL;

    if(valor < H->chave)
    {
        if(cor(H->esq) == BLACK && cor(H->esq->esq) == BLACK)
            H = move2EsqRED(H);

        H->esq = removerNO(H->esq, valor);
    }
    else
    {
        if(cor(H->esq) == RED)
            H = rotacionaDireita(H);

        if(valor == H->chave && (H->dir == NULL))
        {
            free(H);
            return NULL;
        }

        if(cor(H->dir) == BLACK && cor(H->dir->esq) == BLACK)
            H = move2DirRED(H);

        if(valor == H->chave)
        {
            NO x = procurarMenor(H->dir);
            H->chave = x->chave;
            H->dir = removerMenor(H->dir);
        }
        else
            H->dir = removerNO(H->dir, valor);
    }
    return balancear(H);
}

int RB::remover(int valor)
{
    if(buscar(valor))
    {
        NO h = raiz;
        raiz = removerNO(h, valor);
        if(raiz != NULL)
            raiz->cor = BLACK;
        return 1;
    }
    else
        return 0;
}

int RB::vazia(){
    if(raiz == NULL)
        return 1;
        
    return 0;
}

int totalNO(NO raiz){
    if (raiz == NULL)
        return 0;
    if (raiz == NULL)
        return 0;

    int alt_esq = totalNO(raiz->esq);
    int alt_dir = totalNO(raiz->dir);
    return (alt_esq + alt_dir + 1);
}

int RB::numNos()
{
    return totalNO(raiz);
}

int alturaNO(NO raiz){
    if (raiz == NULL)
        return 0;
    if (raiz == NULL)
        return 0;
    int alt_esq = alturaNO(raiz->esq);
    int alt_dir = alturaNO(raiz->dir);
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}

int RB::altura()
{
    return alturaNO(raiz);
}

void RB::largura()
{
    std::queue<NO> f;
    f.push(raiz);
    while (!f.empty())
    {
        NO atual = f.front();
        f.pop();
        std::cout << atual->chave << " ";
        if (atual->esq)
            f.push(atual->esq);
        if (atual->dir)
            f.push(atual->dir);
    }
}

void exibirNO(NO H)
{
    std::cout << H->chave << " é " << (cor(H) ? "Rubro" : "Negro");
}

void RB::percurso(NO raiz, int tipo)
{
    if (raiz == NULL)
        return;

    if (tipo == PRE_ORDEM)
    {
        exibirNO(raiz); 
        std::cout << (this->raiz == raiz ? " <- raiz" : "") << std::endl;
    }

    percurso(raiz->esq, tipo);

    if (tipo == EM_ORDEM)
    {
        exibirNO(raiz); 
        std::cout << (this->raiz == raiz ? " <- raiz" : "") << std::endl;
    }

    percurso(raiz->dir, tipo);

    if (tipo == POS_ORDEM)
    {
        exibirNO(raiz); 
        std::cout << (this->raiz == raiz ? " <- raiz" : "") << std::endl;
    }
}

void RB::preOrdem()
{
    percurso(raiz, PRE_ORDEM);
}

void RB::emOrdem()
{
    percurso(raiz, EM_ORDEM);
}

void RB::posOrdem()
{
    percurso(raiz, POS_ORDEM);
}

