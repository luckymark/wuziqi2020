#pragma GCC optimize(3)
#pragma G++ optimize(3)
//关于为什么要开O3，其实是因为O2对map的优化效果很大
//然后开了O2之后就不由自主地想开O3
#include<QApplication>
#include"gobang.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GoBang w;
    w.show();
    return a.exec();
    //进入消息循环
}
