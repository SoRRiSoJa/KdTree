/* 
 * File:   boxCurses.h
 * Author: joao
 * API de manipulação de tela atraves da biblioteca nccurses
 * Criaçao de molduras, definicao de cores ,exibição de mensagens
 * Created on 24 de Agosto de 2016, 19:03
 */

#ifndef BOXCURSES_H
#define	BOXCURSES_H
#include<ncurses.h>
#include<string.h>



#endif	/* BOXCURSES_H */

//--------------------
void initSetup();
void exitWin();
void makeWindow(int rowStart,int lineStart,int rowEnd,int lineEnd,int color);
void displayMsgCenter(int line,char mesg[]);
void spc(register int nSpcs,register int typeBlock);

//---------------------------------------------------------------------------
void displayMsgCenter(int line,char mesg[]){
    int row,col;
        getmaxyx(stdscr,row,col);
        move(line,(col-strlen(mesg))/2);
        printw("%s",mesg);
        refresh();
}

//----------------------------------------------------------------------------
void makeWindow(int rowStart,int lineStart,int rowEnd,int lineEnd,int color){
        attron(COLOR_PAIR((color)));

        move(lineStart,rowStart);
        addch(ACS_ULCORNER);

        move(lineStart,rowEnd);
        addch(ACS_URCORNER);

        move(lineEnd,rowStart);
        addch(ACS_LLCORNER);

        move(lineEnd,rowEnd);
        addch(ACS_LRCORNER);

        for(int i=lineStart+1;i<lineEnd;i++){
            move(i,rowStart);
                addch(ACS_VLINE);
            move(i,rowEnd);
                addch(ACS_VLINE);
        }

        for(int i=rowStart+1;i<rowEnd;i++){
                move(lineStart,i);
                    addch(ACS_HLINE);
                move(lineEnd,i);
                    addch(ACS_HLINE);
        }
    refresh();
}
//--------------------
void spc(register int nSpcs,register int typeBlock){
    for(register int i=0;i<nSpcs;i++)
        if (typeBlock==0)
            addch(ACS_CKBOARD);
        else
            printw(" ");
refresh();
}
//--------------------
void initSetup(){
     initscr();
     start_color();
     use_default_colors();
     init_pair(1,COLOR_WHITE,COLOR_BLUE);
     init_pair(2,COLOR_BLUE,COLOR_WHITE);
     init_pair(3,COLOR_BLUE,COLOR_BLACK);
     init_pair(4,COLOR_BLUE,COLOR_BLUE);
     init_pair(5,COLOR_CYAN,COLOR_BLUE);
     init_pair(6,COLOR_BLUE,COLOR_CYAN);
     init_pair(7,COLOR_CYAN,COLOR_CYAN);
     init_pair(8,COLOR_BLACK,COLOR_WHITE);
     init_pair(9,COLOR_WHITE,COLOR_WHITE);
     init_pair(10,COLOR_WHITE,COLOR_BLACK);
     init_pair(11,COLOR_WHITE,COLOR_RED);
     init_pair(12,COLOR_RED,COLOR_BLUE);
     init_pair(13,COLOR_RED,COLOR_BLACK);
     init_pair(14,COLOR_GREEN,COLOR_BLACK);
     init_pair(15,COLOR_YELLOW,COLOR_BLACK);
     init_pair(16,COLOR_GREEN,COLOR_BLUE);
     init_pair(17,COLOR_BLACK,COLOR_BLACK);
     init_pair(18,COLOR_RED,COLOR_RED);
     init_pair(19,COLOR_YELLOW,COLOR_RED);
     init_pair(20,COLOR_YELLOW,COLOR_BLUE);
     init_pair(21,COLOR_YELLOW,COLOR_BLACK);
     init_pair(22,COLOR_BLACK,COLOR_YELLOW);
     init_pair(23,COLOR_RED,COLOR_WHITE);
     init_pair(24,COLOR_WHITE,COLOR_CYAN);

}
//--------------------
void exitWin(){
    endwin();
}
