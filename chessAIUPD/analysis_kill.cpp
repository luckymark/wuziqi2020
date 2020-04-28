////
//// Created by hw730 on 2020/4/19.
////
//
//#include "analysis_kill.h"
////
//// Created by hw730 on 2020/4/8.
////
//
//
//
//
//bool analysis(int (&board)[CHESS_HEIGHT][CHESS_LENGTH],int depth)
//{
//    bool flag = false;
//    if(depth == 0)
//    {
//        boardStatus result = evaluateBoard(board);
//        if(result.status == 1) return true;
//        return false;
//    }
//    if(depth % 2 == 0)
//    {
//        decision P = killPosition(board);
//        int sameBoard[CHESS_HEIGHT][CHESS_LENGTH];
//        copychess(board,sameBoard);
//        for(int i = 1;i <= MAX_CHOICE;i++)
//        {
//            sameBoard[P.pos[i].x][P.pos[i].y] = C_WHITE;
////            q[++R] = P.pos[i];
//            q[++R] = QPoint(P.pos[i].x,P.pos[i].y);
//            if(analysis(sameBoard,depth - 1)) flag = true;
//            sameBoard[P.pos[i].x][P.pos[i].y] = C_NONE;
//            R--;
//            if(flag) return true;
//        }
//    }
//    else
//    {
//        int reverseBoard[CHESS_HEIGHT][CHESS_LENGTH];
//        revBoard(board, reverseBoard);
//        decision P = findPoints(reverseBoard);
//        if(analysis(reverseBoard,depth - 1)) return true;
//    }
//    return false;
//}
//
//bool judgechesstype(int x,int y)
//{
//    for(int k = 0;k < 4;k++)
//    {
//        for(int t = 0;t <= 5;t+=5)
//        {
//            int min_x = x - dir[k][0] * t,min_y = y - dir[k][1] * t;
//            int max_x = x - dir[k][0] * (t - 5), max_y = y - dir[k][1] * (t - 5);
//            if((!judgePoints(min_x,min_y)) || (!judgePoints(max_x,max_y))) continue;
//            int score = chess_6_type[board[x - dir[k][0] * t][y - dir[k][1] * t]][board[x - dir[k][0] * (t - 1)][y - dir[k][1] * (t - 1)]][board[x - dir[k][0] * (t - 2)][y - dir[k][1] * (t - 2)]][board[x - dir[k][0] * (t - 3)][y - dir[k][1] * (t - 3)]][board[x - dir[k][0] * (t - 4)][y - dir[k][1] * (t - 4)]][board[x - dir[k][0] * (t - 5)][y - dir[k][1] * (t - 5)]];
//            if(score >= WHITE_LIVE_3) return true;
//        }
//    }
//    return false;
//}
//
//decision killPosition(int (&board)[CHESS_HEIGHT][CHESS_LENGTH])
//{
//    decision P;
//    int cnt = 0;
//    for(int i = 1;i <= R;i++)
//    {
//        int x = q[i].x(),y = q[i].y();
//        for(int d = 0;d < 8;d++)
//        {
//            if(judgePoints(x + dir[d][0],y + dir[d][1]) &&
//               board[x + dir[d][0]][y + dir[d][1]] == C_NONE
//               &&judgechesstype(x + dir[d][0],y + dir[d][1]))
//            {
//                P.pos[++cnt].x = x + dir[d][0];
//                P.pos[++cnt].y = y + dir[d][1];
//            }
//        }
//    }
//    return P;
//}
