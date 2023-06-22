// Site para simulação da LLRB padrão 
// https://portaldoprofessor.fct.unesp.br/projetos/cadilag/apps/structs/arv_rn.php

typedef struct no* NO;

class LLRB 
{
    private:
        NO raiz;
        void percurso(NO raiz, int tipo);
        LLRB();
    public:
        static LLRB* criar(int valor);
        ~LLRB();
        /*Função para inserir na Árvore 
        Entrada: valor a ser inserido na LLRB
        Saida : 0 para erro 1 para sucesso 
        */
        int inserir(int valor);
        /*Função para remover na Árvore 
        Entrada: valor a ser removido na LLRB
        Saida : 0 para erro 1 para sucesso 
        */
        int remover(int valor);
        /*Função para verificar se a Árvore está vazia
        Entrada: não há
        Saida : 0 para não vazia e 1 para vazia
        */
        int vazia();
        /*Função para calcular o número de nós presentes na lista
        Entrada: não há
        Saida : número total de nós presente na lista
        */
        int numNos();
        /*Função para calcular a altura da Árvore 
        Entrada: não há
        Saida : altura da árvore
        */
        int altura();
        /*Função para busca na Árvore
        Entrada: não há
        Saida : retorna 0 para falha na busca ou 1 para sucesso da mesma
        */
        int buscar(int valor);
        /* Função percurso em largura na árvore
        Entrada: não há
        Saida: não há*/
        void largura();
        /*Função percurso em pré-ordem na Árvore
        Entrada: não há
        Saida : não há
        */
        void preOrdem();
        /*Função percurso em em-ordem na Árvore
        Entrada: não há
        Saida : não há
        */
        void emOrdem();
        /*Função percurso em pós-ordem na Árvore
        Entrada: não há
        Saida : não há
        */
        void posOrdem();
};