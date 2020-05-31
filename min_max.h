#ifndef MIN_MAX_H
#define MIN_MAX_H
#include <mainwindow.h>
#include <score_count.h>

int MainWindow::evaluate_minmax(){      //这是评估函数
    int scoreAI=0;
    int scoreplayer=0;
    for(int i=0;i<SIZE;i++){    //横排
        std::vector <int> v;
        for(int j=0;j<SIZE;j++)
            v.push_back(a[i][j]);
        scoreplayer+=count_score(n,1);
        scoreAI+=count_score(n,2);
        v.clear();
    }
    for(int j=0;j<SIZE;j++){    //竖排
        std::vector <int> v;
        for(int i=0;i<SIZE;i++)
            v.push_back(a[i][j]);
        scoreplayer+=count_score(n,1);
        scoreAI+=count_score(n,2);
        v.clear();
    }
    for(int i=0;i<SIZE;i++){    //上半正斜线
        int x,y;
        std::vector <int> v;
        for(x=i,y=0;x<SIZE&&y<SIZE;++x,++y)
            v.push_back(a[y][x]);
        scoreplayer+=count_score(n,1);
        scoreAI+=count_score(n,2);
        v.clear();
    }
    for(int j=1;j<SIZE;j++){    //下半正斜线
        int x,y;
        std::vector <int> v;
        for(x=0,y=j;y<SIZE&&x<SIZE;x++,y++)
            v.push_back(a[y][x]);
        scoreplayer+=count_score(n,1);
        scoreAI+=count_score(n,2);
        v.clear();
    }
    for(int i=0;i<SIZE;i++){      //上半反斜线
        std::vector <int> v;
        int x,y;
        for(y=i,x=0;y>=0&&x<SIZE;y--,x++)
            v.push_back(a[y][x]);
        scoreplayer+=count_score(n,1);
        scoreAI+=count_score(n,2);
        v.clear();
    }
    for(int j=1;j<SIZE;j++){
        std::vector <int> v;
        int x,y;
        for(y=j,x=SIZE-1;y<16&&x>=0;y++,x--)
            v.push_back(a[x][y]);
        scoreplayer+=count_score(n,1);
        scoreAI+=count_score(n,2);
        v.clear();
    }
    return scorecomputer-scorehumber;
}
int MainWindow::min_search(int depths,int beta){
    int res=evaluate_minmax();
    if(depth<=0){
        return res;
    }
    std::vector < std::pair<int,int> > vv;
    genarator_point(vv);
    int Length=vv.size();
    int best=INT_MAX;
    for(int i=0;i<Length;i++){
        int t1=vv[i].first;
        int t2=vv[i].second;
        a[t1][t2]=1;
        int temps=max_search(depths-1,best < alpha ? best : alpha);
        if(temps<best)  best=temps;
        if(temps<beta)  break;  //剪枝
        a[t1][t2]=0;
    }
    return best;
}
int MainWindow::max_search(int depths,int alpha){
    int res=evaluate_minmax();
    if(depth<=0){
        return res;
    }
    std::vector < std::pair<int,int> > vv;
    genarator_point(vv);
    int Length=vv.size();
    int best=INT_MIN;
    for(int i=0;i<Length;i++){
        int t1=vv[i].first;
        int t2=vv[i].second;
        a[t1][t2]=1;
        int temps=min_search(depths-1,best > beta ? best : beta);
        if(temps>best)  best=temps;
        if(temps>alpha) break;//剪枝
        a[t1][t2]=0;
    }
    return best;
}

void MainWindow::AImax_search(int &xxx, int &yyy, int depths){
    std::vector <std::pair <int,int> >  vv;
    genarator_point(vv);
    int best=INT_MIN;
    int Length=vv.size();
    std::vector <std::pair <int,int> > vv2;
    for(int i=0;i<Length;i++){
        int t1=vv[i].first();
        int t2=vv[i].second();
        a[t1][t2]=2;
        int temp=min_search(depths-1,0);
        if(temp>best){
            best=temp;
            vv2.clear();
            vv2.push_back(vv1);
        }else{
            if(temp==best){
                vv2.push_back(vv1);
            }
        }
        a[t1][t2]=0;
    }
    int Length2=vv2.size();
    int choose=(int)(rand()%Length2);
    xxx=v2[choose].first();
    yyy=v2[choose].second();
}

#endif // MIN_MAX_H
