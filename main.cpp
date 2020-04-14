#include"chessglobalconst.h"
#include"board.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Board w;
//    memset(w.board,0,sizeof(w.board));
    memset(w.chess_6_type,0,sizeof(w.chess_6_type));
    w.init_Chess_6_Type();
    w.setButton();

//    w.board[4][4] = w.board[5][4] = w.board[6][4] = C_WHITE;
//    w.board[10][10] = w.board[15][15] = w.board[1][1] = C_BLACK;
//    w.R = 6;
//    w.q[1] = QPoint(4,4);
//    w.q[2] = QPoint(10,10);
//    w.q[3] = QPoint(4,5);
//    w.q[4] = QPoint(15,15);
//    w.q[5] = QPoint(4,6);
//    w.q[6] = QPoint(1,1);
    w.show();


    return a.exec();
}

