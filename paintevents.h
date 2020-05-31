#ifndef PAINTEVENTS_H
#define PAINTEVENTS_H
#include <mainwindow.h>
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    int i,j;
    for (i = 0; i < SIZE; i++)
    {
        p.drawLine(x_o,y_o+i*WIDTH,x_o+WIDTH*(SIZE-1),y_o+i*WIDTH);//GEN GAI
        p.drawLine(x_o+i*WIDTH,y_o,x_o+i*WIDTH,y_o+WIDTH*(SIZE-1));
    }
    QBrush brush;
       brush.setStyle(Qt::SolidPattern);
       for (i = 0; i < SIZE; i++)
       {
           for (j = 0; j < SIZE; j++)
           {
               if (a[i][j] == 1)
               {
                   brush.setColor(Qt::black);
                   p.setBrush(brush);
                   p.drawEllipse(QPoint(x_o+i*WIDTH,y_o+j*WIDTH), 15, 15);
               }
               else if (a[i][j] == 2)
               {
                   brush.setColor(Qt::white);
                   p.setBrush(brush);
                   p.drawEllipse(QPoint(x_o+i*WIDTH,y_o+j*WIDTH), 15, 15);
               }
//               else if (a[i][j] == 3)
//               {
//                   brush.setColor(Qt::red);
//                   p.setBrush(brush);
//                   p.drawEllipse(QPoint((i + 1) * 40, (j + 1) * 40), 15, 15);
//               }
//               else if (a[i][j] == 4)
//               {
//                   brush.setColor(Qt::blue);
//                   p.setBrush(brush);
//                   p.drawEllipse(QPoint((i + 1) * 40, (j + 1) * 40), 15, 15);
//               }
//               else if (a[i][j] == 5)
//               {
//                   brush.setColor(Qt::yellow);
//                   p.setBrush(brush);
//                   p.drawEllipse(QPoint((i + 1) * 40, (j + 1) * 40), 15, 15);
//               }

           }
       }
}

#endif // PAINTEVENTS_H
