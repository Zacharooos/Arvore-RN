//======================================================//
// Dependências - Versão 1.0                            //
//======================================================//

#include <stdio.h>
#include <stdlib.h>

//======================================================//
// Struct node - Versão 1.1                             //
//======================================================//

typedef struct node{
    int prioridade;     // Prioridade em relação ao quão antigo o cliente é, quanto mais fiel, menor o número
    struct node *esq;         // Ponteiro que aponta para o filho esquerdo
    struct node *dir;         // Ponteiro que aponta para o filho direito
    struct node *pai;         // Ponteiro que aponta para o pai
    char cor;           // Variável que guarda a cor, escolhi char por ser menor que o int. p = preto | v = vermelho

}node;

//======================================================//
// Funções Auxíliares - Versão 1.2                      //
//======================================================//

// Função que realiza a troca da cor do nó e de seus filhos
void aux_swapCor(node* alvo){
    if(alvo->cor == 'v'){           // Se for 'v', deve virar 'p'
        alvo->cor = 'p';            // Se for 'p', deve virar 'v'
    } else {
        alvo->cor = 'v';
    }

    if(alvo->esq != NULL){
        if(alvo->esq->cor = 'p'){
            alvo->cor = 'p';
        } else {
            alvo->cor = 'v';
        }
    }
}

// Função que percorrer todos os nós em préordem
void allNodes(node *raiz){ 
    if(raiz != NULL){
        allNodes(raiz->esq);
        if (raiz->pai == NULL) {
            printf("Found -> %d, pai = NULL\n", raiz->prioridade);
        } else {
            printf("Found -> %d, filho de -> %d\n", raiz->prioridade, raiz->pai->prioridade);
        }
        allNodes(raiz->dir);
    }
}

//======================================================//
// Funções de Manipulação - Versão 1.1                  // Corrigida
//======================================================//

// Função que cria o nó
node *man_createNode(int valorPrioridade){
    node * aux = (node *) malloc (sizeof(node));

    aux->prioridade = valorPrioridade;
    aux->esq = NULL;
    aux->dir = NULL;
    aux->pai = NULL;
    aux->cor = 'r';

    return aux;
}

// Função que insere o nó
node *man_insert(node *raiz, int valorPrioridade){
    
    // Caso a arvore esteja vazia, inicia uma nova árvore.
    if (raiz == NULL){
        return man_createNode(valorPrioridade);
    }

    // Caso contrário, percorre a árvore para inserir o valor entregado.
    if (valorPrioridade < raiz->prioridade){
        raiz->esq = man_insert(raiz->esq, valorPrioridade);
        raiz->esq->pai = raiz;                                  // Define o pai do novo filho como o alvo atual
                                                                // Como o novo filho é esquerdo, usamos ele como referencia
    } else if (valorPrioridade > raiz->prioridade){
        raiz->dir = man_insert(raiz->dir, valorPrioridade);
        raiz->dir->pai = raiz;                                  // Define o pai do novo filho como o alvo atual
    }                                                           // Como o novo filho é direito, usamos ele como referencia

    return raiz;
}

//void man_rbFix(node *alvo, )

//======================================================//
// Funções de Rotação - Versão 1.0                      //
//======================================================//

// Função de rotação para a esquerda
void rot_esq(node* alvo, node *raiz)
{
    node *aux = alvo->dir;
    alvo->dir = aux->esq;

    if (aux->esq != NULL){
        aux->esq->pai = alvo;
    }

    aux->pai = alvo->pai;

    if (alvo->pai == NULL){
        raiz = aux;
    } else if (alvo == alvo->pai->esq){
        alvo->pai->esq = aux;
    } else {
        alvo->pai->dir = aux;
    }

    aux->esq = alvo;
    alvo->pai = aux;
    return;
}

// Função de rotação para a direita
void rot_dir(node* alvo, node *raiz)
{
    node *aux = alvo->esq;
    alvo->esq = aux->dir;

    if (aux->dir != NULL){
        aux->dir->pai = alvo;
    }

    aux->pai = alvo->pai;

    if (!alvo->pai){
        raiz = aux;
    } else if (alvo == alvo->pai->dir){
        alvo->pai->esq = aux;
    } else {
        alvo->pai->dir = aux;
    }

    aux->dir = alvo;
    alvo->pai = aux;
    return;
}

//======================================================//
// Funções Main - Versão 1.0                            //
//======================================================//

int main (){
    printf("Fine!\n");

    // cria raiz
    node* raiz = NULL;
    raiz = man_insert(raiz, 50);
    man_insert(raiz, 30);
    man_insert(raiz, 20);
    man_insert(raiz, 40);
    man_insert(raiz, 70);
    man_insert(raiz, 60);
    man_insert(raiz, 80);
 
    // print inoder traversal of the BST
    allNodes(raiz);


    return 0;
}