#include "ai.h"

void Widget::start1(){
    if(isstarted==0){
        win=0;
        isstarted=1;
        flag=1;
    }
}
void Widget::start2(){
    if(isstarted==0){
        isstarted=1;
        flag=2;
        Map[7][7]=1;
        update();
        win=0;
    }
}
void Widget::restart(){
    isstarted=0;
    win=0;
    memset(Map,0,sizeof(Map));
    this->update();
}
void Widget::AI(){
    int layer=1; //层数
    max1=-INF;max2=0;
    DFS(layer);
    Map[xx][yy]=3-flag;
//    int val=value(1);
//    int val2=value(2);
//    qDebug()<<"black"<<val<<" white"<<val2<<endl;
    update();
}

void Widget::DFS(int layer){
    if(layer==5){
        if(vv[4]>vmax[4]) {
            vmax[4]=vv[4];
        }return;
    }
    //max4=0;//第三个子下完后所有的第四步中最大的那个
    vmax[layer]=-9999;
    for(int i=0;i<GRIDCOUNT;i++){
        for(int j=0;j<GRIDCOUNT;j++){
            if(isempty(i,j)){
                Map[i][j]= layer%2? 3-flag:flag;
                if(layer==1){
                    vv[layer]=value(3-flag);
                    if(win==1){
                        xx=i;yy=j; return;
                    }
                }else if(layer%2){
                    vv[layer]=value((3-flag));
                }else if(layer%2==0){
                    vv[layer]=value(flag);
                }
                DFS(layer+1);
                if(greater==1){
                    greater=0;xx=i;yy=j;
                }
                Map[i][j]=0;
                if(layer==4||layer==3||layer==2){
                    if(vv[layer-1]-vmax[layer]<vmax[layer-1]){
                        return;
                    }
                }
            }
        }
    }
    if(layer==4||layer==3){
        vv[layer-1]-=vmax[layer];
        if(vv[layer-1]>vmax[layer-1]) vmax[layer-1]=vv[layer-1];
    }
    if(layer==2){
        vv[layer-1]-=vmax[layer];
        if(vv[layer-1]>vmax[layer-1]) {vmax[layer-1]=vv[layer-1];greater=1;}
        if(vv[layer-1]==vmax[layer-1]) { int temp=rand()%3;if(!temp) greater=1; }
    }
    return;
}

bool Widget::isempty(int x,int y){ //方圆5*5内是否有棋
    if(!Map[x][y]){
        for(int i=-1;i<2;i++){
            for(int j=-1;j<2;j++){
                if(x+i<GRIDCOUNT&&x+i>=0&&y+j<GRIDCOUNT&&y+j>=0)
                    if(Map[x+i][y+j]) return true;
            }
        }
    }return false;
}
void Widget::foo(int i,int j,const int type,int &count,int &val,int &die){
    if(Map[i][j]==type) count++;
    else if(Map[i][j]==3-type){
        if(!die&&count){
            count--;
            val+=pow(10,count);
        }
        die=1;
        count=0;
    }else if(Map[i][j]==0){
        if(count){
            if(die) count--;
            val+=pow(10,count);
        }
        die=0;
        count=0;
    }if(count==5){
        val+=99999;
        win=1;
    }
}
int Widget::value(int type){
    win=0;
    int val=0;  //type为1为评估黑棋，2为评估白棋
    int die,die2,count,count2,die3,die4,count3,count4;  //1为死 0为活
    for(int i=0;i<GRIDCOUNT;i++){//横竖
        die=1,die2=1,count=0,count2=0;
        for(int j=0;j<GRIDCOUNT;j++){
            foo(i,j,type,count,val,die);
            foo(j,i,type,count2,val,die2);
        }
    }
    for(int i=0;i<GRIDCOUNT;i++){//斜线
        die=1,die2=1,count=0,count2=0;
        die3=1,die4=1,count3=0,count4=0;
        for(int j=0;j+i<GRIDCOUNT;j++){
            foo(j,j+i,type,count,val,die);
            if(i!=0) foo(j+i,j,type,count2,val,die2);
            foo(14-j-i,j,type,count3,val,die3);
            if(i!=0) foo(14-j,j+i,type,count4,val,die4);
        }
   }
    return val;
}
