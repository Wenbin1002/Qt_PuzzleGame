#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QDebug>
#include <QtAlgorithms>

int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/res/icon.jpg"));
    setWindowTitle("Puzzle");

    //set puzzle default position
    for(int i=0;i<9;i++)
    {
        QString str = QString(":/res/img-%1.png").arg((i+1)%9);
        PhotoPiece * btn = new PhotoPiece(str);
        btnArry[i/3][i%3] = btn;
        btn->photoNum = (i+1)%9;
        btn->setParent(ui->mianWidget);
        btn->setFixedSize(150,150);
        btn->move(i%3 * 150,i/3 * 150);
        btn->posX = i/3;
        btn->posY = i%3;

        //click to move button
        connect(btn,&QPushButton::clicked,[=](){
            for(int i=0;i<3;i++)
                for(int j=0;j<3;j++)
                    btnArry[i][j]->isMovable = ifMove(btnArry[i][j]);

            qDebug() << QString("photoNum : %1").arg(btn->photoNum);
            qDebug() << QString("pos : %1 %2").arg(btn->posX).arg(btn->posY);
            moveBtn(btn);
        });
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// A button can be moved if and only if it has a blank button around it
bool MainWindow::ifMove(PhotoPiece * btn)
{
    bool ret = false;

    for(int i=0;i<4;i++)
    {
        int x = btn->posX + dx[i];
        int y = btn->posY + dy[i];

        if(x<0 || x==3 || y<0 || y==3) continue;

        if(btnArry[x][y]->photoNum == 0) ret = true;
    }

    return ret;
}

// swap two button
void MainWindow::moveBtn(PhotoPiece * btn)
{
    if(btn->isMovable == false)
    {
        qDebug() << "can't move";
        return;
    }

    for(int i=0;i<4;i++)
    {
        int x = btn->posX + dx[i];
        int y = btn->posY + dy[i];

        if(x<0 || x==3 || y<0 || y==3) continue;

        if(btnArry[x][y]->photoNum == 0)
        {
            btn->btnSwap(btnArry[x][y]);
        }
    }
}
