/**
 * @author Artificial01
 * @date 2020-6-9
 * @version 2.0
 * */

/*
 * 棋盘感觉比较好看
 *
 * 棋盘 竖向为 x 横向为 y
 *
 * 不知道为什么 运行复制到git管理的文件夹下的源代码时 会出现中文乱码 而 运行被复制的那份源代码时 没有问题
 *
 * */

#ifndef FIVECHESS_BOARD_H
#define FIVECHESS_BOARD_H
#endif

#define DEEP 6  //层数 (DEEP==4 时：速度超级快; DEEP==6 时：后期速度较慢)

int boardData[17][17],place_x,place_y,turn;  //棋盘棋子的信息(这里采用 17*17 是为了方便 实际是 15*15(0号与16号 不用))、落棋的坐标、当前的执棋者

void initBoard();  //初始化棋盘
void drawBoard();  //打印棋盘棋子
int theDirectCount(int x,int y,int xAdd,int yAdd,int count);  //某个棋子 在某个射线方向上 的连续长度
int theColorChessWin();  //判断 是否胜利 以及 哪方胜利
void ifWin();  //胜利之后 的程序结束处理
void turnSwitch();  //交换 执棋者
void placeChess();  //玩家 以及 AI 下棋操作

void initBoard(){
    memset(boardData,0,17*17* sizeof(int));
    turn=-1;
    place_x=0,place_y=0;
    system("cls");
    printf("Welcome!\n");
    Sleep(1000);
    system("cls");
}

void drawBoard(){
    setlocale(LC_ALL,"chs");
    wchar_t black=L'○',white=L'●',nothing=L'·';
    printf("\n");
    for(int i=0;i<10;i++)
        printf(" 0%d",i);
    for(int i=10;i<17;i++)
        printf(" %d",i);
    printf("\n");
    for(int i=1;i<10;i++){
        printf(" 0%d",i);
        for(int j=1;j<=15;j++){
            if(boardData[i][j]==1) wprintf(L" %c ",black);
            else if (boardData[i][j]==-1) wprintf(L" %c ",white);
            else wprintf(L" %c ",nothing);
        }
        printf(" 0%d\n",i);
    }
    for(int i=10;i<16;i++){
        printf(" %d",i);
        for(int j=1;j<=15;j++){
            if(boardData[i][j]==1) wprintf(L" %c ",black);
            else if (boardData[i][j]==-1) wprintf(L" %c ",white);
            else wprintf(L" %c ",nothing);
        }
        printf(" %d\n",i);
    }
    for(int i=0;i<10;i++)
        printf(" 0%d",i);
    for(int i=10;i<17;i++)
        printf(" %d",i);
    wprintf(L"\n (Black-> %c | White-> %c)\n\n",black,white);
}

int theDirectCount(int x,int y,int xAdd,int yAdd,int count){
    if(boardData[x+xAdd][y+yAdd]==boardData[x][y]) return theDirectCount(x+xAdd,y+yAdd,xAdd,yAdd,++count);
    else return count;
}

int theColorChessWin(){
    int add[4][2]={{1,0},{1,1},{0,1},{-1,1}};
    for(int i=0;i<4;i++)
        if((theDirectCount(place_x,place_y,add[i][0],add[i][1],0) + theDirectCount(place_x,place_y,-add[i][0],-add[i][1],0))>=4) return boardData[place_x][place_y];
    return 0;
}

void ifWin(){
    if(theColorChessWin()==1){
        printf("Black chess player win!");
        exit(0);
    } else if (theColorChessWin()==-1){
        printf("White chess player win!");
        exit(0);
    }
}

void turnSwitch(){
    if(turn==1) turn=-1;
    else turn=1;
}

void placeChess(){
    if(turn==1){
        printf("It is turn to Black chess player\n");
        do{
            printf("Input x and y:");
            scanf(" %d %d",&place_x,&place_y);
        }while (place_x<1 || place_x>15 || place_y<1 || place_y>15 || boardData[place_x][place_y]);
    }else{
        printf("It is turn to White chess player\n");
        AI_MaxMin(boardData,DEEP,&place_x,&place_y);
    }
    boardData[place_x][place_y]=turn;
}
