/* 
 * File:   Forms.h
 * Author: joao
 *
 * Created on 23 de Novembro de 2016, 17:27
 */

#ifndef FORMS_H
#define	FORMS_H
#include<time.h>
#include"boxCurses.h"
#include "ADTTree.h"
void stampDate(char mes[], char dia[], char ano[], char hora[], char minuto[], char segundo[], int op);
void formIsertPoint();
void clearDBComand();

#ifdef	__cplusplus
extern "C" {
#endif

    /*----------------------------------------------------------------------------*/
    void menuForm() {
        char m[4], d[3], a[5];
        char h[3], mm[3], s[5];
        attron(COLOR_PAIR((11)));
        move(0, 57);
        stampDate(m, d, a, h, mm, s, 1);
        refresh();
        move(22, 0);
        spc(80, 1);
        move(22, 20);
        printw("||");
        move(22, 26);
        printw("||");
        move(22, 44);
        printw("||");
        move(22, 68);
        printw("||");
        attron(COLOR_PAIR((14)));
        move(23, 0);
        spc(79, 1);
        displayMsgCenter(23, "Enter a valid UNIX comand line or type <HELP>.");
        refresh();
    }
}

/*----------------------------------------------------------------------------*/
void clearDBComand() {
    attron(COLOR_PAIR((17)));
    for (int i = 0; i < 22; i++) {
        move(i, 0);
        spc(80, 1);
    }
    refresh();
    menuForm();
    move(1, 1);
    refresh();
}

/*----------------------------------------------------------------------------*/
void formIsertPoint() {
    move(2, 20);
    attron(COLOR_PAIR((3)));
    printw("Point Tag                        - X Cord - Y Cord");
    for (int i = 0; i < 32; i++) {
        move(3, 20 + i);
        addch(ACS_HLINE);
    }
    attron(COLOR_PAIR((11)));
}

/*----------------------------------------------------------------------------*/
void getNewPoint(No **r) {
    Point p[20];
    int px, py, tlAux = 0;
    char flag = 1;
    do {
        move(3 + tlAux, 20);
        attron(COLOR_PAIR((3)));
        printw("[");
        move(3 + tlAux, 21);
        spc(30, 1);
        move(3 + tlAux, 51);
        attron(COLOR_PAIR((3)));
        printw("]");
        move(3 + tlAux, 21);
        flushinp();
        getstr(p[tlAux].Tag);
        if (p[tlAux].Tag[0] != 'q') {
            move(3 + tlAux, 58);
            scanw("%d", &px);
            move(3 + tlAux, 66);
            scanw("%d", &py);
            p[tlAux].pX = px;
            p[tlAux].pY = py;
            tlAux++;
        } else {
            flag = 0;
            tlAux--;
        }

    } while (flag && tlAux < 20);

    for (int i = 0; i < tlAux; i++) {
        insereKD(&*r, p[i]);
    }
    clearDBComand();
}

/*----------------------------------------------------------------------------*/
void stampDate(char mes[], char dia[], char ano[], char hora[], char minuto[], char segundo[], int op) {
    time_t currentTime;
    struct tm *timeinfo;
    char *diaSemana[] = {"Dom", "Seg", "Ter", "Qua", "Qui", "Sex", "Sab"};

    /* Pega a hora atual do sistema e a converte em uma estrutura tm. */
    time(&currentTime);
    timeinfo = localtime(&currentTime);

    /* Atualiza os valores dia, mes e ano da estrutura. */
    sprintf(dia, "%d", timeinfo->tm_mday);
    sprintf(mes, "%d", timeinfo->tm_mon + 1);
    sprintf(ano, "%d", timeinfo->tm_year + 1900);

    //strcpy(diaS, diaSemana[timeinfo->tm_wday]);
    sprintf(hora, "%d", timeinfo->tm_hour);
    sprintf(minuto, "%d", timeinfo->tm_min);
    sprintf(segundo, "%d", timeinfo->tm_sec);
    if (op == 1)
        printw("%s/%s/%s - %s:%s:%s ", dia, mes, ano, hora, minuto, segundo);
    refresh();
}

/*----------------------------------------------------------------------------*/
void formAbout() {
    char strMSg[18][79];
    strcpy(strMSg[0], "C++ LiKe LaRGe SHiT MaKeR KD-TRee BaSeD DaTa BaSe SYSTeM VeRSioN 1.0");
    strcpy(strMSg[1], "This Software is Licensed to:");
    strcpy(strMSg[2], "Unoeste FIPP Lab Estrutura de Dados II");
    strcpy(strMSg[3], "João André MarTins Dias e Silva");
    strcpy(strMSg[4], "RA:0261234021");
    strcpy(strMSg[5], "Copyright(c) João André Martins Dias e Silva (2016).All Rights Reservd. ");
    strcpy(strMSg[6], "This program is free software: you can  redistribute  it  and/or modify   ");
    strcpy(strMSg[7], "it under the terms of the GNU General Public  License as  published  by   ");
    strcpy(strMSg[8], "the  Free  Software  Foundation,  either  version  3  of  the  License,   ");
    strcpy(strMSg[9], "or any later version.                                                     ");
    strcpy(strMSg[10], "This  program  is  distributed   in  the  hope that it will be useful,    ");
    strcpy(strMSg[11], "but  WITHOUT  ANY  WARRANTY;  without  even  the  implied  warranty of    ");
    strcpy(strMSg[12], "MERCHANTABILITY or  FITNESS  FOR  A  PARTICULAR   PURPOSE.    See  the    ");
    strcpy(strMSg[13], "GNU General Public License  for  more details.                            ");
    strcpy(strMSg[14], "You should have  received  a copy of the  GNU  General  Public License    ");
    strcpy(strMSg[15], "along with this program.  If not, see <http://www.gnu.org/licenses/>.     ");
    strcpy(strMSg[16], "Contact:                                                                  ");
    strcpy(strMSg[17], "e-mail:jamdes@hotmail.com                                                 ");
    move(1, 0);
    clearDBComand();
    attron(COLOR_PAIR((14)));
    for (int i = 0; i < 18; i++)
        displayMsgCenter(i + 1, strMSg[i]);
    refresh();
}

/*----------------------------------------------------------------------------*/
void formSearch() {
    makeWindow(16, 4, 64, 18, 3);
    attron(COLOR_PAIR((15)));
    displayMsgCenter(5, "*** Coordenadas para Busca ***");
    move(7, 19);
    printw("Ponto Central: (x,y)");
    move(8, 19);
    printw("X:[   ] Y[   ]");
    move(10, 19);
    printw("Raio de busca:");
    move(11, 19);
    printw("R:[   ]");
}

/*----------------------------------------------------------------------------*/
void formShowSearch(No *p, Point Centro, int raio) {
    char msg[3][30];
    strcpy(msg[0], "[Resultado Encontrado!]");
    strcpy(msg[1], "[Resultado nao Encontrado!]");
    makeWindow(20, 12, 60, 16, 3);
    if (p != NULL) {
        attron(COLOR_PAIR((15)));
        displayMsgCenter(12, msg[0]);
        move(13, 21);
        attron(COLOR_PAIR((11)));
        spc(39, 1);
        move(13, 21);
        exibeNo(p);
        move(14, 21);
        spc(39, 1);
        move(14, 21);
        printw("Distancia entre [%s] e C(%2d,%2d) e [%2d]", p->info.Tag, Centro.pX, Centro.pY, distEuclidiana(p->info, Centro));
    } else {
        attron(COLOR_PAIR((15)));
        displayMsgCenter(12, msg[1]);
        move(13, 21);
        attron(COLOR_PAIR((11)));
        spc(39, 1);
        move(13, 21);
        printw("Nenhuma ocorrencia em R[%2d] p/ C(%2d,%2d)", raio, Centro.pX, Centro.pY);
    }

}

/*----------------------------------------------------------------------------*/
Point getParamSearch(int *raio) {
    int px, py;
    attron(COLOR_PAIR((15)));
    move(8, 22);
    scanw("%d", &px);
    move(8, 29);
    scanw("%d", &py);
    move(11, 22);
    scanw("%d", &*raio);
    return criaP(px, py, "Centro");

}

/*----------------------------------------------------------------------------*/
void drwBase(int MaxPx, int MaxPy, int step) {
    clearDBComand();
    attron(COLOR_PAIR((10)));
    move(2, 6);
    for (int i = 2; i < 21; i++) {
        move(i, 6);
        addch(ACS_VLINE);
    }
    move(20, 6);
    for (int i = 6; i < 78; i++) {
        move(20, i);
        addch(ACS_HLINE);
    }
    move(20, 6);
    addch(ACS_LLCORNER);
    attron(COLOR_PAIR((15)));
    move(0, 2);
    printw("(%2d,%2d)", 0, MaxPy);
    move(21, 70);
    printw("(%2d,%2d)", MaxPx, 0);
    attron(COLOR_PAIR((10)));
    move(8, 2);
    printw("^");
    move(9, 2);
    addch(ACS_VLINE);
    move(10, 2);
    addch(ACS_VLINE);
    move(11, 2);
    printw("Y");
    move(21, 35);
    printw("X --->");
    attron(COLOR_PAIR((15)));
}
/*----------------------------------------------------------------------------*/
#ifdef	__cplusplus

#endif

#endif	/* FORMS_H */

