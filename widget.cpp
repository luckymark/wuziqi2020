#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    Init();

    QPushButton *btn=new QPushButton("先手",this);
    btn->move(190,745);
    btn->resize(100,50);
    QPushButton *btn2=new QPushButton("后手",this);
    btn2->move(500,745);
    btn2->resize(100,50);
    QPushButton *btn3=new QPushButton("重来",this);
    btn3->move(350,765);
    btn3->resize(90,40);
    connect(btn,&QPushButton::clicked,this,&Widget::start1);
    connect(btn2,&QPushButton::clicked,this,&Widget::start2);
    connect(btn3,&QPushButton::clicked,this,&Widget::restart);
}

void Widget::paintEvent(QPaintEvent *){
    QPainter painter(this);
    setFixedSize(800,850);
    setWindowTitle("Chess-Gobang");
    //背景颜色 蓝色（135,206,250）  粉色（255,182,193）  紫色（238,130,238）
    QBrush brush(QColor(135,206,250));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(0,0,size().width(),size().height());
    //画棋盘
    QPen pen;
    pen.setColor(LineColor);
    pen.setStyle(LineStyle);
    pen.setWidth(LineWidth);
    painter.setPen(pen);
    for(int i=0;i<GRIDCOUNT;i++){
        painter.drawLine(startx,starty+i*gridlength,startx+sidelength,starty+i*gridlength);
        painter.drawLine(startx+i*gridlength,starty,startx+i*gridlength,starty+sidelength);
    }
    //画棋子
    for(int i=0;i<GRIDCOUNT;i++){
        for(int j=0;j<GRIDCOUNT;j++){
            if(Map[i][j]){
                QString checker= Map[i][j]==1? black:white;
                QRect rect(QPoint(startx+(i-0.4)*gridlength,starty+(j-0.4)*gridlength),QPoint(startx+(i+0.4)*gridlength,starty+(j+0.4)*gridlength));
                QPixmap pix(checker);
                painter.drawPixmap(rect,pix);
            }
        }
    }
}
void Widget::resizeEvent(QResizeEvent *event){
    sidelength=event->size().width()<event->size().height()? event->size().width():event->size().height();
    gridlength=sidelength/(GRIDCOUNT+3);
    sidelength=(GRIDCOUNT-1)*gridlength;
    startx=2*gridlength;
    starty=2*gridlength;
}
void Widget::mousePressEvent(QMouseEvent *event){
    int a=event->x();
    int b=event->y();
    if(isstarted&&!win&&a>=startx-gridlength/2&&a<=startx+sidelength+gridlength/2&&b>=starty-gridlength/2&&b<=starty+sidelength+gridlength/2){
        int x=(a-startx+gridlength/2)/gridlength;
        int y=(b-starty+gridlength/2)/gridlength;
        //qDebug()<<x<<" "<<y<<endl;
        if(Map[x][y]==0){
            Map[x][y]=flag;
            update();
            value(flag);
            if(win) {
                QPushButton *btn= new QPushButton;
                btn->resize(400,100);
                btn->setText("呜呜呜呜呜呜呜呜呜呜呜呜呜呜 你欺负我（x）");
                btn->show();
            }else{
                AI();
                value(3-flag);
                if(win) {
                    QPushButton *btn= new QPushButton;
                    btn->resize(400,100);
                    btn->setText("哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈你输了！");
                    btn->show();
                }
            }

        }
    }
}
void Widget::Init(){
    LineColor=Qt::black;
    LineStyle=Qt::SolidLine;
    LineWidth=3;
    black=":/image/b.png";
    white=":/image/w.png";
    flag=1;
    isstarted=0;
    memset(Map,0,sizeof(Map));
    win=0;
}
Widget::~Widget()
{
    delete ui;
}
