#include"chessglobalconst.h"
#include"chessglobalvariable.h"
#include"chess_init_type.h"
#include"board.h"
#include"alphabeta.h"

int main(int argc, char *argv[])
{
    srand(time(0));
    QApplication a(argc, argv);
    Board w;
//    memset(w.board,0,sizeof(w.board));
    memset(chess_6_type,0,sizeof(chess_6_type));
    init_zobrist();
    init_Chess_6_Type();
    w.setButton();

//        board[4][4] = board[5][4] = board[6][4] = C_BLACK;
//    board[2][2] = board[3][3] = board[1][1] = C_WHITE;
//    R1 = R = 6;
//    q1[1] = q[1] = QPoint(4,4);col[1] = col[3] = col[5] = 2;
//    q1[2] = q[2] = QPoint(2,2);
//    q1[3] = q[3] = QPoint(5,4);
//    q1[4] = q[4] = QPoint(3,3);
//    q1[5] = q[5] = QPoint(6,4);
//    q1[6] = q[6] = QPoint(1,1);
//    w.update();
    w.show();


    return a.exec();
}
