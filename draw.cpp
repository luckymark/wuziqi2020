#include"gobang.h"
#include"ui_widget.h"
#include<QPainter>
#include<QMouseEvent>
#include<QIcon>
#include<QDesktopWidget>
void GoBang::setAlignment()
{
    QRect rec = QApplication::desktop()->screenGeometry();
    int left = (rec.width() - this->width()) >> 1;
    int top = (rec.height() - this->height()) >> 1;
    this->move(left, top);
}

void GoBang::initGUI()
{
    this->setFixedSize(740, 660);
    this->setAutoFillBackground(true);
    this->setWindowTitle("GoBang");
    QPalette palette;
    palette.setColor(QPalette::Background, QColor("#B1723C"));
    this->setPalette(palette);
    setMouseTracking(true);
    ui->titleLabel->move(90,0);
    ui->timeLabel->move(640, 150);
    ui->stepLabel->move(640, 500);
    setWindowIcon(QIcon(":res/monisha.ico"));
    setAlignment();
}

void GoBang::mouseMoveEvent(QMouseEvent* e)
{
    moveI = (e->y() - 40) / 40;
    moveJ = (e->x()+20 - 40) / 40;
    update();
    QWidget::mouseMoveEvent(e);
}
void GoBang::paintEvent(QPaintEvent* e) {

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QPen pen = painter.pen();
    pen.setColor(QColor("#8D5822"));
    pen.setWidth(7);
    painter.setPen(pen);


    QBrush brush;
    brush.setColor(QColor("#EEC085"));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(20, 40, 600, 600);

    pen.setColor(Qt::black);
    pen.setWidth(1);
    painter.setPen(pen);
    for (int i = 0; i < NUMBER; ++i) {
        painter.drawLine(40 + i * 40, 60, 40 + i * 40, 620);
        painter.drawLine(40, 60 + i * 40, 600, 60 + i * 40);
    }
    brush.setColor(Qt::black);
    painter.setBrush(brush);
    painter.drawRect(155, 175, 10, 10);
    painter.drawRect(475, 175, 10, 10);
    painter.drawRect(155, 495, 10, 10);
    painter.drawRect(475, 495, 10, 10);
    painter.drawRect(315, 335, 10, 10);

    for (int i = 0; i < NUMBER; ++i) {
        for (int j = 0; j < NUMBER; ++j) {
            if (chess[i][j] == C_BLACK) {
                brush.setColor(Qt::black);
                painter.setBrush(brush);
                painter.drawEllipse(QPoint((j + 1) * 40, (i + 1) * 40 + 20), 18, 18);
            }
            if (chess[i][j] == C_WHITE) {
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.setPen(Qt::NoPen);
                painter.drawEllipse(QPoint((j + 1) * 40, (i + 1) * 40 + 20), 18, 18);
            }
        }
    }
    pen.setColor(Qt::red);
    pen.setWidth(1);
    painter.setPen(pen);
    if ((moveI * 40 + 40) >= 20 && (moveI * 40 + 40) <= 620 && moveJ>=0 && (moveJ * 40 + 20) <= 600) {
        painter.drawLine((moveJ + 1) * 40 - 20, (moveI + 1) * 40, (moveJ + 1) * 40 - 10, (moveI + 1) * 40);
        painter.drawLine((moveJ + 1) * 40 + 20, (moveI + 1) * 40, (moveJ + 1) * 40 + 10, (moveI + 1) * 40);
        painter.drawLine((moveJ + 1) * 40 - 20, (moveI + 1) * 40 + 40, (moveJ + 1) * 40 - 10, (moveI + 2) * 40);
        painter.drawLine((moveJ + 1) * 40 + 20, (moveI + 1) * 40 + 40, (moveJ + 1) * 40 + 10, (moveI + 2) * 40);

        painter.drawLine((moveJ + 1) * 40 - 20, (moveI + 1) * 40, (moveJ + 1) * 40 - 20, (moveI + 1) * 40 + 10);
        painter.drawLine((moveJ + 1) * 40 + 20, (moveI + 1) * 40, (moveJ + 1) * 40 + 20, (moveI + 1) * 40 + 10);
        painter.drawLine((moveJ + 1) * 40 - 20, (moveI + 1) * 40 + 40, (moveJ + 1) * 40 - 20, (moveI + 1) * 40 + 30);
        painter.drawLine((moveJ + 1) * 40 + 20, (moveI + 1) * 40 + 40, (moveJ + 1) * 40 + 20, (moveI + 1) * 40 + 30);
    }
    if (currentI != -1) {
        painter.drawLine((currentJ + 1) * 40 - 1, (currentI + 1) * 40 + 20, (currentJ + 1) * 40 - 6, (currentI + 1) * 40 + 20);
        painter.drawLine((currentJ + 1) * 40 + 1, (currentI + 1) * 40 + 20, (currentJ + 1) * 40 + 6, (currentI + 1) * 40 + 20);
        painter.drawLine((currentJ + 1) * 40, (currentI + 1) * 40 + 19, (currentJ + 1) * 40, (currentI + 1) * 40 + 14);
        painter.drawLine((currentJ + 1) * 40, (currentI + 1) * 40 + 21, (currentJ + 1) * 40, (currentI + 1) * 40 + 26);
    }

    ui->timeLabel->setText(QString("Time: ")+QString::number(seconds));
    ui->stepLabel->setText(QString("Steps: ") + QString::number(steps));

    QWidget::paintEvent(e);
}
