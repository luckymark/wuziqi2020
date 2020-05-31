#ifndef MOUSEVEENTS_H
#define MOUSEVEENTS_H
#include <mainwindow.h>
void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    int x, y,j1,j2,j3,j4;
//    if(e->x() >= x_o && e->x() < x_o+WIDTH*(SIZE-1) && e->y() >= 20 && e->y() < 1900)
      if(e->x()>=x_o&&e->x()<=x_o+WIDTH*(SIZE-1)&&e->y()>=y_o&&e->y()<y_o+WIDTH*(SIZE-1))
      {
          int x1=(e->x())-x_o;
          int y1=e->y()-y_o;
          int rest_x=x1/WIDTH;
          int x_x=x1%WIDTH;
          int rest_y=y1/WIDTH;
          int y_y=y1%WIDTH;
          if(x_x>WIDTH/2){
              if(y_y>WIDTH/2){
                 x1=rest_x+1;
                 y1=rest_y+1;
              }else{
                 x1=rest_x+1;
                 y1=rest_y-1;
              }
          }else{
              if(y_y>WIDTH/2){
                 x1=rest_x-1;
                 y1=rest_y+1;
              }else{
                 x1=rest_x-1;
                 y1=rest_y-1;
              }
          }
          x=(x1<0)?0:x1;
          y=(y1<0)?0:y1;
//          x = (e->x() - 20) / 40;
//          y = (e->y() - 20) / 40;
          if (a[x][y] == 0)
          {
              a[x][y] = player++;
//              if(player == renshu+1)
//                  player =1;
          }

          j1 = jiance(1,0,a[x][y],x,y);        //检测x
          j2 = jiance(0,1,a[x][y],x,y);        //检测y
          j3 = jiance(1,1,a[x][y],x,y);        //检测45度
          j4 = jiance(1,-1,a[x][y],x,y);       //检测135度
          if(j1 ==4||j2==4||j3==4||j4==4)
          {
              this->update();
              //setEnabled(false);
              if(a[x][y] == 1)
              {
                    QMessageBox::information(this, "Win", "Black Win!", QMessageBox::Ok);
              }
              if(a[x][y] == 2)
              {
                    QMessageBox::information(this, "Win", "White Win!", QMessageBox::Ok);
              }
//              if(a[x][y] == 3)
//              {
//                    QMessageBox::information(this, "Win", "Red Win!", QMessageBox::Ok);
//              }
//              if(a[x][y] == 4)
//              {
//                    QMessageBox::information(this, "Win", "Blue Win!", QMessageBox::Ok);
//              }
//              if(a[x][y] == 5)
//              {
//                    QMessageBox::information(this, "Win", "Yellow Win!", QMessageBox::Ok);
//              }
              emit gameover();

          }

      }
      this->update();
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->delta() / 8;//滚动的角度，*8就是鼠标滚动的距离
    int numSteps = numDegrees / 15;//滚动的步数，*15就是鼠标滚动的角度
    if (event->orientation() == Qt::Horizontal)
    {
      qDebug()<<"horiz";

    }
    else
    {
      qDebug()<<"llll"<<numSteps<<"   "<<numDegrees;
    }
    event->accept();      //接收该事件


}

#endif // MOUSEVEENTS_H
