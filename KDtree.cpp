/* 
 * File:   KDtree.cpp
 * Author: joao
 *
 * Created on 23 de Novembro de 2016, 16:51
 */

#include <stdlib.h>
#include "Forms.h"
#include "ADTTree.h"


/*----------------------------------------------------------------------------*/
char buscaStr(char line[], char strSearch[]);
char isParameterComnad(char linha[]);
char login(char login[], char password[], int *line);
void splitLine(char line[], char tokens[], char auxStr[20][60], int *tl);
void commandIterpreter();
void performTest(No **raiz);
/*----------------------------------------------------------------------------*/

//using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    //------------------
    initSetup();
    noecho();
    keypad(stdscr, TRUE);
    commandIterpreter();
    //------------------

    return 0;
}

void commandIterpreter() {
    int  lineConsole = 1,  raio;
    char strComando[30], userLogin[20], userPassword[9], userMachine[11],userCommand = -1;
    char mes[4], dia[3], ano[5], hora[3], minuto[3], segundo[5],end = 1;
    
    No *MainTree=NULL, *auxNode = NULL;
    Point pAux;
    
    strcpy(userMachine, "unixServer");
    echo();
    flushinp();
    formAbout();
    getch();
    clearDBComand();
    login(userLogin, userPassword, &lineConsole);
    while (end) {
        attron(COLOR_PAIR((14)));
        move(lineConsole++, 1);
        printw("%s@%s:~$", userLogin, userMachine);
        flushinp();
        getstr(strComando);
        userCommand = isParameterComnad(strComando);
        if (userCommand != -1) {
            switch (userCommand) {
                case 0:
                    attron(COLOR_PAIR((11)));
                    move(22, 1);
                    printw("createdb");
                    if (MainTree == NULL)
                        init(&MainTree);
                    else {
                        attron(COLOR_PAIR((14)));
                        lineConsole++;
                        move(lineConsole, 1);
                        printw("Use kill to destroy the ramaining data in active database!");
                        lineConsole++;
                    }
                    attron(COLOR_PAIR((14)));
                    break;
                case 1:
                    attron(COLOR_PAIR((11)));
                    move(22, 1);
                    printw("insertdata");
                    clearDBComand();
                    formIsertPoint();
                    getNewPoint(&MainTree);
                    

                    attron(COLOR_PAIR((14)));

                    break;
                case 2:
                    attron(COLOR_PAIR((11)));
                    move(22, 1);
                    printw("list");
                    attron(COLOR_PAIR((14)));
                    if (MainTree == NULL) {
                        lineConsole++;
                        move(lineConsole, 1);
                        printw("No data or active database in memory!");
                        lineConsole++;
                    } else {
                        attron(COLOR_PAIR((14)));
                        clearDBComand();
                        listAsTable(MainTree, &lineConsole);
                        lineConsole++;
                    }
                    break;
                case 3:
                    attron(COLOR_PAIR((11)));
                    move(22, 1);
                    printw("listastree");
                    attron(COLOR_PAIR((14)));
                    if (MainTree == NULL) {
                        lineConsole++;
                        move(lineConsole, 1);
                        printw("No data or active database in memory!");
                        lineConsole++;
                    } else {
                        attron(COLOR_PAIR((11)));
                        clearDBComand();
                        showTree(MainTree, 2, 40, 12);
                        lineConsole++;
                    }
                    break;
                case 4:
                    clearDBComand();
                    attron(COLOR_PAIR((11)));
                    move(22, 1);
                    printw("searchnear");
                    attron(COLOR_PAIR((14)));
                    formSearch();
                    pAux = getParamSearch(&raio);
                    //printw("<%d> (%d,%d)", raio, pAux.pX, pAux.pY);
                    busca(MainTree, pAux, raio, &auxNode);
                    formShowSearch(auxNode, pAux, raio);
                    free(auxNode);
                    auxNode = NULL;
                    lineConsole = 17;
                    break;
                case 5:
                    killKD(&MainTree);
                    attron(COLOR_PAIR((11)));
                    move(22, 1);
                    printw("kill");
                    attron(COLOR_PAIR((14)));
                    break;
                case 6:
                    attron(COLOR_PAIR((11)));
                    clearDBComand();
                    lineConsole = 1;
                    move(22, 1);
                    printw("clear");
                    attron(COLOR_PAIR((14)));
                    lineConsole = 1;
                    break;
                case 7:
                    clearDBComand();
                    drwBase(100, 100, 100);
                    plotGraph(MainTree,NULL,pAux);
                    //drawPoint(criaP(100,100,"A"));
                    flushinp();
                    getch();
                    break;
                case 8:
                    attron(COLOR_PAIR((11)));
                    move(22, 1);
                    printw("runtest");
                    performTest(&MainTree);
                    clearDBComand();
                    
                    attron(COLOR_PAIR((14)));
                    break;
                case 9:
                    attron(COLOR_PAIR((11)));
                    move(22, 1);
                    printw("exit");
                    clearDBComand();
                    end = 0;
                    attron(COLOR_PAIR((14)));
                    break;

            }
            move(0, 57);
            stampDate(mes, dia, ano, hora, minuto, segundo, 1);
            attron(COLOR_PAIR((14)));
            refresh();

        } else {
            move(lineConsole++, 1);
            printw("Comando ou nome de arquivo invalido!\n");
            userCommand = -1;
            attron(COLOR_PAIR((11)));
            move(0, 57);
            stampDate(mes, dia, ano, hora, minuto, segundo, 1);
            attron(COLOR_PAIR((14)));
            refresh();
        }
        move(0, 57);
        stampDate(mes, dia, ano, hora, minuto, segundo, 1);
        attron(COLOR_PAIR((14)));
        refresh();

    }
    refresh();
}

char isParameterComnad(char linha[]) {
    char tipo = -1;
    char tipos[10][12] = {"createdb", "insertdata", "list", "listasatree", "searchnear", "kill", "clear", "plotgraph","runtest","exit"};
    for (int i = 0; i < 10; i++)
        if (buscaStr(linha, tipos[i]))
            tipo = i;
    return tipo;
}

char buscaStr(char line[], char strSearch[]) {
    char auxL[40];
    char* busca = NULL;
    strcpy(auxL, line);
    busca = strstr(auxL, strSearch);
    return (busca != NULL);
}

char login(char login[], char password[], int *line) {
    int cont = 0;
    move(*line, 0);
    printw("login:");
    getstr(login);
    *line = *line + 1;
    move(*line, 0);
    printw("password:");
    noecho();
    while (cont < 8) {
        flushinp();
        password[cont++] = getch();
        move(*line, 9 + cont);
        printw("*");

    }
    flushinp();
    echo();
    password[cont] = '\0';
    *line = *line + 1;
    move(*line, 0);
    printw("login[%s] password:[%s]", login, password);
    *line = *line + 1;
}
/*----------------------------------------------------------------------------*/

/* splitLine By Joao Andre Martins copyleft C 2016
 * void splitLine(char[],char[],char[][],*int)
 * line =(linha original que se deseja quebrar em substrings
 * tokens =caracteres delimitadores das substrings
 * auxStr[20][30] vetor de strings, contem as substrings
 * tl =tamanho lógico do vetor de substrings, (numero de palavras)
 */
void splitLine(char line[], char tokens[], char auxStr[20][60], int *tl) {
    char *lineAux, *strBroke;
    int cont = 0;
    lineAux = line;
    strBroke = strtok(lineAux, tokens);
    while (strBroke != NULL) {
        strcpy(auxStr[cont++], strBroke);
        strBroke = strtok(NULL, tokens);
    }
    *tl = cont;
}

/*----------------------------------------------------------------------------*/
void performTest(No **raiz) {
    Point points[8];
    /*-----------------------------*/
    points[0] = criaP(50, 30, "A");
    points[1] = criaP(22, 63, "B");
    points[2] = criaP(80, 15, "C");
    points[3] = criaP(34, 10, "D");
    points[4] = criaP(10, 96, "E");
    points[5] = criaP(68, 45, "F");
    points[6] = criaP(53, 73, "G");
    points[7] = criaP(60, 88, "H");

    /*-----------------------------*/
    for (int i = 0; i < 8; i++)
        insereKD(&*raiz, points[i]);

}