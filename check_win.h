#ifndef CHECK_WIN_H
#define CHECK_WIN_H
#include <mainwindow.h>
int MainWindow::jiance(int i, int j,int team,int x,int y)
{

    int jieguo= 0;
    int nextteam;
    int footx = i;
    int footy = j;
    int huanxiang =0;
    while(1)                                  //x向检测
    {
        if(huanxiang ==0)
        {
            nextteam = a[x+footx][y+footy];
        }
        else if(huanxiang ==1)
        {
            nextteam = a[x-footx][y-footy];
        }
        else break;

        if(nextteam == team)
        {
            jieguo++;
            footx += i;
            footy += j;

        }
        else
        {
            footx = i;
            footy = j;
            huanxiang++;
        }

    }
    return jieguo;



}
#endif // CHECK_WIN_H
