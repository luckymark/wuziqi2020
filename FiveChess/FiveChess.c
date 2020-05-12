//棋盘 待美化
//AI 待完成
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <synchapi.h>

int boardData[17][17];
int turn;
int place_x,place_y;

void initBoard(){
    memset(boardData,0,17*17* sizeof(int));
    turn=1;
    system("cls");
    printf("Welcome!\n");
    Sleep(1000);
    system("cls");
}

void drawBoard(){
    printf("\n");
    for(int i=1;i<=15;i++){
        for(int j=1;j<=15;j++){
            if(boardData[i][j]==1) printf(" B");
            else if (boardData[i][j]==-1) printf(" W");
            else printf(" *");
        }
        printf("\n");
    }
    printf("\n");
}

void placeChess(){
    if(turn==1) printf("It is turn to Black chess player\n");
    else printf("It is turn to White chess player\n");
    do{
        printf("Input x and y:");
        scanf(" %d %d",&place_x,&place_y);
    }while (place_x<=0 || place_x>=16 || place_y<=0 || place_y>=16 || boardData[place_x][place_y]!=0);
    boardData[place_x][place_y]=turn;
}

int theDirectCount(int x,int y,int xAdd,int yAdd,int count){
    if(x>0 && x<16 && y>0 && y<16 && boardData[x+xAdd][y+yAdd]==boardData[x][y]) return theDirectCount(x+xAdd,y+yAdd,xAdd,yAdd,++count);
    else return count;
}

int theColorChessWin(){
    int add[4][2]={{1,0},{1,1},{0,1},{-1,1}};
    for(int i=0;i<4;i++)
        if((theDirectCount(place_x,place_y,add[i][0],add[i][1],0) + theDirectCount(place_x,place_y,-add[i][0],-add[i][1],0))>=4) return boardData[place_x][place_y];
    return 0;
}
//个人觉得此处代码优美
void ifWin(){
    if(theColorChessWin()==1){
        printf("Congratulations! Black chess player win!");
        exit(0);
    } else if (theColorChessWin()==-1){
        printf("Congratulations! White chess player win!");
        exit(0);
    }
}

void turnSwitch(){
    if(turn==1) turn=-1;
    else turn=1;
}

int main() {
    initBoard();
    drawBoard();
    for(;;){
        placeChess();
        drawBoard();
        ifWin();
        turnSwitch();
        system("cls");
    }
}
