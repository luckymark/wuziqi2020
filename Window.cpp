#include <QApplication>
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include <cmath>
#include "Window.h"

const int kBoardMargin = 30;
const int kRadius = 15;
const int kCenterSize = 6;
const int kMarkSize = 6;
const int kBlockSize = 40;
const int kPosDelta = 20;

const int kCenter[5][2] = {{7, 7}, {3, 3}, {3, 11}, {11, 3}, {11, 11}};

Window::Window(QWidget *parent) : QMainWindow(parent) {
    setFixedSize(kBoardMargin * 2 + kBlockSize * (kBoardSizeNum - 1), kBoardMargin * 2 + kBlockSize * (kBoardSizeNum - 1));
    setStyleSheet("background-color:#DEB887;");

    setMouseTracking(true);
}

void Window::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    for (int i = 0; i < kBoardSizeNum; i++) {
        painter.drawLine(kBoardMargin + kBlockSize * i, kBoardMargin, kBoardMargin + kBlockSize * i, size().height() - kBoardMargin);
        painter.drawLine(kBoardMargin, kBoardMargin + kBlockSize * i, size().width() - kBoardMargin, kBoardMargin + kBlockSize * i);
    }

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    painter.setBrush(brush);
    for (auto i : kCenter) {
        painter.drawEllipse(kBoardMargin + kBlockSize * i[1] - kCenterSize, kBoardMargin + kBlockSize * i[0] - kCenterSize, kCenterSize * 2, kCenterSize * 2);
    }

    if (clickPosRow >= 0 && clickPosRow <= kBoardSizeNum &&
        clickPosCol >= 0 && clickPosCol <= kBoardSizeNum &&
        game.map[clickPosRow][clickPosCol] == SPACE) {
        if (game.player == PERSON) {
            brush.setColor(Qt::black);
            painter.setBrush(brush);
            painter.drawRect(kBoardMargin + kBlockSize * clickPosCol - kMarkSize / 2, kBoardMargin + kBlockSize * clickPosRow - kMarkSize / 2, kMarkSize, kMarkSize);
        }
    }

    for (int i = 0; i < kBoardSizeNum; i++) {
        for (int j = 0; j < kBoardSizeNum; j++) {
            if (game.map[i][j] == BLACK) {
                brush.setColor(Qt::black);
                painter.setBrush(brush);
                painter.drawEllipse(kBoardMargin + kBlockSize * j - kRadius, kBoardMargin + kBlockSize * i - kRadius, kRadius * 2, kRadius * 2);
            } else if (game.map[i][j] == WHITE) {
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(kBoardMargin + kBlockSize * j - kRadius, kBoardMargin + kBlockSize * i - kRadius, kRadius * 2, kRadius * 2);
            }
        }
    }

}

void Window::mouseMoveEvent(QMouseEvent *event) {
    int x = event->x();
    int y = event->y();

    if (game.player == PERSON &&
        x >= kBoardMargin / 2 &&
        x < size().width() - kBoardMargin / 2 &&
        y >= kBoardMargin / 2 &&
        y < size().height()- kBoardMargin / 2) {
        int col = x / kBlockSize;
        int row = y / kBlockSize;

        int leftTopPosX = kBoardMargin + kBlockSize * col;
        int leftTopPosY = kBoardMargin + kBlockSize * row;

        clickPosRow = -1;
        clickPosCol = -1;
        int len;

        len = int(sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY)));
        if (len < kPosDelta) {
            clickPosRow = row;
            clickPosCol = col;
        }
        len = int(sqrt((x - leftTopPosX - kBlockSize) * (x - leftTopPosX - kBlockSize) + (y - leftTopPosY) * (y - leftTopPosY)));
        if (len < kPosDelta) {
            clickPosRow = row;
            clickPosCol = col + 1;
        }
        len = int(sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - kBlockSize) * (y - leftTopPosY - kBlockSize)));
        if (len < kPosDelta) {
            clickPosRow = row + 1;
            clickPosCol = col;
        }
        len = int(sqrt((x - leftTopPosX - kBlockSize) * (x - leftTopPosX - kBlockSize) + (y - leftTopPosY - kBlockSize) * (y - leftTopPosY - kBlockSize)));
        if (len < kPosDelta) {
            clickPosRow = row + 1;
            clickPosCol = col + 1;
        }

        update();
    }
}

void Window::mousePressEvent(QMouseEvent *event) {
    if (game.player == PERSON) {
        if (game.chessByPerson(clickPosRow, clickPosCol)) {
            repaint();
            if (game.isWin == PERSON) {
                QMessageBox::StandardButton btnValue = QMessageBox::information(this, "Congratulations", "You win!");
                if (btnValue == QMessageBox::Ok) {
                    QApplication::exit(0);
                }
            } else {
                game.chessByAI();
                repaint();
                if (game.isWin == AI) {
                    QMessageBox::StandardButton btnValue = QMessageBox::information(this, "Sorry", "You lose :)");
                    if (btnValue == QMessageBox::Ok) {
                        QApplication::exit(0);
                    }
                }
            }
        }
    }
}
