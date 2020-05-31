#ifndef SCORE_COUNT_H
#define SCORE_COUNT_H
#include <bits/stdc++.h>
#include <mainwindow.h>
const int Max_point=1e5;
bool MainWindow::checks(int d_x,int d_y){
    for(int i=(d_x-3)>0?d_x-3:0;i<=d_x+3&&i<=14;i++){
        for(int j=(d_y-3)>0?d_y-3:0;j<=d_y+3&&j<=14;j++){
            if(!a[i][j]){
                return true;
            }
        }
    }
    return false;
}
void MainWindow::genarator_point(std::vector <std::pair<int,int> > &v){
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(a[i][j]==0&&checks(i,j)){
                std::pair <int,int> p;
                p.first=i;
                p.second=j;
                v.push_back(p);
            }
        }
    }
}
int MainWindow::score_table(int number,int emptys){
    if(number>=5)   return Max_point;
    if(number==4){
        if(emptys==2)   return Max_point/10;
        else{
            if(emptys==1)   return Max_point/100;
        }
    }
    if(number==3){
        if(emptys==2)   return Max_point/100;
        else{
            if(emptys==1)   return Max_point/1000;
        }
    }
    if(number==2){
        if(emptys==2)   return Max_point/1000;
        else{
            if(emptys==1)   return Max_point/10000;
        }
    }
    if(number==1&&emptys==2)    return Max_point/10000;
    return 0;
}
int MainWindow::count_score(std::vector<int> v_v, int turn){
    int temp_score=0;          //积分总数
    int Length=v_v.size();      //横排，竖排，上斜线，下斜线vector长度
    int emptys=0;           //空子个数
    int number=0;           //计算turn代表的人所握棋子个数，1是黑，2是白
    for(int i=0;i<Length;i++){
        if(v_v[i]==turn)    number++;
        else{
            if(!v_v[i]){
                if(!number) emptys=1;
                else{
                    temp_score+=score_table(number,emptys);
                    emptys=1;
                    number=0;
                }
            }else{
                temp_score+=score_table(number,emptys);
                emptys=1;
                number=0;
            }
        }
    }
    temp_score+=score_table(number,emptys);
    return temp_score;
}
#endif // SCORE_COUNT_H
