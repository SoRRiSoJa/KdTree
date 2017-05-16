/* 
 * File:   ADTTree.h
 * Author: joao
 *
 * Created on 23 de Novembro de 2016, 19:36
 */

#ifndef ADTTREE_H
#define	ADTTREE_H
#include <string.h>
#include <math.h>
#ifdef	__cplusplus
extern "C" {
#endif

    struct Point {
        int pX, pY;
        char Tag[30];
    };
    typedef struct Point point;

    struct KDNode {
        point info;
        char discriminator;
        struct KDNode *esq, *dir;
    };
    typedef struct KDNode No;

    /*Tipo abstrato para pilha auxiliar*/
    struct Stack {
        No *info;
        struct Stack *prox;
    };
    typedef struct Stack st;

    /*------------------------------------------------------------------------*/
    Point criaP(int x, int y, char *info); //retorna uma nova estrutura do tipo point
    No* criaNo(Point p, char disc); //Retorna uma nova estrutura do tipo No da KDtree
    void init(No **raiz); //Inicializa uma estrtura do tipo KDtree
    void insereKD(No **raiz, Point p); //Insere um novo ponto na Arvore KDtreee
    int comparaPontos(Point pA, Point pB, char disc); //Copara duas estruturas Point dado seu discriminador
    void exibeNo(No *node);
    void inOrden(No *raiz);
    void showTree(No *raiz, int y, int x, int dist); //Exibe uma Arvore no formato de diagrama
    void busca(No *raiz, Point centro, int raio, No **p);
    int distEuclidiana(Point pA, Point pB);
    void initStack(st **pilha);
    void push(st **p, No *info);
    void pop(st **p, No **info);
    char isEmpty(st *st);
    long map(long x, long in_min, long in_max, long out_min, long out_max);//Regra de 3 semelhante ao map dop arduino
    void drawPoint(Point p);
    void drawPointAndLine(Point p);
    void plotGraph(No *raiz, No *pAux, Point centro);
    /*------------------------------------------------------------------------*/

    /* Retorna uma estrutura do tipo Point devidamente preenchida
     * Point criaP(int , int , char *)
     * x coordenada do ponto X
     * y coordenada do ponto Y
     * info Tag ou informação relativa oa ponto
     */

    Point criaP(int x, int y, char *info) {
        Point novo;
        novo.pX = x;
        novo.pY = y;
        strcpy(novo.Tag, info);
        return novo;
    }

    /*------------------------------------------------------------------------*/

    /* Retorna uma estrutura do tipo ponteiro No* para um novo no da KDtree
     * No* criaNo(Point, char )
     * p estrutura do tipo Point com as coordenasdas e a Tag do nó
     * disc Discriminador para insercao e comparacao (0 p/X e 1 p/Y)
     */

    No* criaNo(Point p, char disc) {
        No *np = (No*) malloc(sizeof (No));
        np->esq = np->dir = NULL;
        np->info = p;
        np->discriminator = disc;
        return np;
    }
    /* Inicializa uma estrutura do tipo KDtree
     * void init(No **)
     * raiz estrutura do tipo ponteiro *No
     */

    /*------------------------------------------------------------------------*/
    void init(No **raiz) {
        *raiz = NULL;
    }
    /* Insere um novo Ponto na arvore KDtree
     * void insereKD(No **, Point )
     * raiz estrutura do tipo ponteiro *No
     * p estutura do tipo Point com as Coordenadas e a Tag
     */
    /*------------------------------------------------------------------------*/
    void insereKD(No **raiz, Point p) {
        No *pAux, *pAnt = NULL;
        if (*raiz == NULL) {
            *raiz = criaNo(p, 0);
        } else {
            pAux = *raiz;
            while (pAux != NULL) {
                pAnt = pAux;
                if (comparaPontos(p, pAnt->info, pAnt->discriminator) != -1) {
                    pAnt = pAux;
                    pAux = pAux->dir;
                } else {
                    pAnt = pAux;
                    pAux = pAux->esq;
                }
            }
            if (comparaPontos(p, pAnt->info, pAnt->discriminator) != -1) {
                pAnt->dir = criaNo(p, !pAnt->discriminator);
            } else {
                pAnt->esq = criaNo(p, !pAnt->discriminator);

            }
        }
    }
    /*------------------------------------------------------------------------*/

    /* Exibe as informacoes de uma estrutura de um No
     * void exibeNo(No *)
     * node
     * p estutura do tipo Point com as Coordenadas e a Tag
     */

    void exibeNo(No *node) {
        printw("(%.2d,%.2d) -[%s]", node->info.pX, node->info.pY, node->info.Tag);
    }

    /*------------------------------------------------------------------------*/
    void inOrden(No *raiz) {
        if (raiz != NULL) {
            inOrden(raiz->esq);
            exibeNo(raiz);
            inOrden(raiz->dir);
        }
    }
    /*------------------------------------------------------------------------*/

    /* Retorna a comparacao de duas estruturas tipo Point dado seu Discriminador
     * int comparaPontos(Point, Point, char )
     * pA estrutura do tipo Point com as coordenasdas e a Tag 
     * pB estrutura do tipo Point com as coordenasdas e a Tag
     * disc Discriminador para comparacao (0 p/X e 1 p/Y)
     * Retorna 0 se pA==pB,1 Se pA>pB,-1 se Pa < pB
     */

    int comparaPontos(Point pA, Point pB, char disc) {
        if (disc == 1) {
            if (pA.pY == pB.pY)
                return 0;
            else {
                return (pA.pY > pB.pY) ? 1 : -1;
            }

        } else {
            if (pA.pX == pB.pX)
                return 0;
            else {
                return (pA.pX > pB.pX) ? 1 : -1;
            }
        }
    }
    /*------------------------------------------------------------------------*/

    /* Exibe uma arvore KDTree em Forma de Diagram de arvore
     * void showTree(No *, int , int , int )
     * raiz ponteiro para uma estrutura do tipo raiz 
     * y linha para inicio da impressao do diagrama
     * x coluna para inicio da impressao do diagrama
     * dist distancia de incremento das colunas entre os nós
     */

    void showTree(No *raiz, int y, int x, int dist) {
        if (raiz != NULL) {
            move(y, x);
            attron(COLOR_PAIR((14)));
            //printw("(%.2d,%.2d)", raiz->info.pX, raiz->info.pY);
            printw("[%s]", raiz->info.Tag);
            if (raiz->esq != NULL) {
                move(y + 1, x - dist / 2);
                printw("/");
            }
            if (raiz->dir != NULL) {
                move(y + 1, x + dist / 2);
                printw("\\");
            }
            showTree(raiz->esq, y + 2, x - dist, dist / 2);
            showTree(raiz->dir, y + 2, x + dist, dist / 2);
        }
        refresh();
    }

    /*------------------------------------------------------------------------*/
    void busca(No *raiz, Point centro, int raio, No **p) {
        int r;
        if (raiz != NULL) {
            r = distEuclidiana(raiz->info, centro);

            if (r < raio) {//ponto pertence a circumferência (disntancia menor ou igual ao raio)
                *p = raiz;
            } else {
                if (raiz->discriminator == 0) {//discriminador par (nivel par)
                    if ((centro.pX - raio) < raiz->info.pX)
                        busca(raiz->esq, centro, raio, &*p);
                    else
                        if ((centro.pX + raio) >= raiz->info.pX)
                        busca(raiz->dir, centro, raio, &*p);
                } else {//discriminador impar (nivel impar)
                    if ((centro.pY - raio) < raiz->info.pY)
                        busca(raiz->esq, centro, raio, &*p);
                    else
                        if ((centro.pY + raio) >= raiz->info.pY)
                        busca(raiz->dir, centro, raio, &*p);
                }
            }
        }
    }

    /*----------------------------------------------------------------------------*/
    int distEuclidiana(Point pA, Point pB) {
        int ppa=(pA.pX - pB.pX),ppb=(pA.pY - pB.pY);
        ppa*=ppa;ppb*=ppb;
        return (int) sqrt(ppa+ppb);
        
    }

    /*------------------------------------------------------------------------*/
    void initStack(st **pilha) {
        *pilha = NULL;
    }

    /*------------------------------------------------------------------------*/
    char isEmpty(st *st) {
        return st == NULL;
    }

    /*------------------------------------------------------------------------*/
    void push(st **p, No *info) {
        st *nova = (st*) malloc(sizeof (st));
        nova->info = info;
        nova->prox = *p;
        *p = nova;
    }

    /*------------------------------------------------------------------------*/
    void pop(st **p, No **info) {
        st *aux;
        if (!isEmpty(*p)) {
            aux = *p;
            *info = (*p)->info;
            *p = (*p)->prox;
            free(aux);
        } else {
            *info = NULL;
        }
    }

    /*------------------------------------------------------------------------*/
    void listAsTable(No *raiz, int *cLine) {
        st *p;
        int line = 0;
        initStack(&p);
        push(&p, raiz);
        //move(2,2+line);
        //printf("TAG                           - ( X , Y )");
        while (!isEmpty(p)) {
            if (raiz != NULL) {
                pop(&p, &raiz);
                while (raiz != NULL) {
                    push(&p, raiz);
                    raiz = raiz->esq;
                }
            }
            pop(&p, &raiz);
            move(2 + line, 2);
            printw("[%s] - (%2d,%2d) ", raiz->info.Tag, raiz->info.pX, raiz->info.pY);
            line++;
            raiz = raiz->dir;
            if (raiz != NULL)
                push(&p, raiz);
        }
        *cLine += line;
    }

    /*------------------------------------------------------------------------*/
    void killKD(No **raiz) {
        if (*raiz != NULL) {
            killKD(&(*raiz)->esq);
            killKD(&(*raiz)->dir);
            free(*raiz);
            *raiz = NULL;
        }

    }

    /*------------------------------------------------------------------------*/
    void plotGraph(No *raiz, No *pAux, Point centro) {
        st *p;
        int line = 0;
        initStack(&p);
        push(&p, raiz);
        while (!isEmpty(p)) {
            if (raiz != NULL) {
                pop(&p, &raiz);
                while (raiz != NULL) {
                    push(&p, raiz);
                    raiz = raiz->esq;
                }
            }
            pop(&p, &raiz);
            drawPointAndLine(raiz->info);
            line++;
            raiz = raiz->dir;
            if (raiz != NULL)
                push(&p, raiz);
        }
        //*cLine += line;
    }

    /*------------------------------------------------------------------------*/
    void drawPoint(Point p) {
        long px = map(p.pX, 0, 100, 6, 77), py = map(p.pY, 0, 100, 2, 20);
        move(21 - py, px);
        printw("[%s] (%d,%d)", p.Tag, p.pX, p.pY);
    }

    /*------------------------------------------------------------------------*/
    void drawPointAndLine(Point p) {
        long px = map(p.pX, 0, 100, 6, 77), py = map(p.pY, 0, 100, 2, 20);
        move(21 - py, px + 1);
        printw("[%s] (%d,%d)", p.Tag, p.pX, p.pY);

        for (int i = (21 - py); i < 20; i++) {
            move(i, px);
            addch(ACS_VLINE);
        }

        for (int i = 6; i < px; i++) {
            move(21 - py, i);
            addch(ACS_HLINE);
        }


        move(21 - py, px);
        addch(ACS_URCORNER);
        move(21 - py, 6);
        addch(ACS_LTEE);
        move(20, px);
        addch(ACS_BTEE);
    }

    /*------------------------------------------------------------------------*/
    long map(long x, long in_min, long in_max, long out_min, long out_max) {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }


#ifdef	__cplusplus
}
#endif

#endif	/* ADTTREE_H */

