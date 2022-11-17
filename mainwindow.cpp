#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QDebug>
#include <QtAlgorithms>
#include <QtGlobal>

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
        PhotoPiece * pht = new PhotoPiece(str);
        photoArray[i/3][i%3] = pht;
        pht->photoNum = (i+1)%9;
        pht->setParent(ui->mianWidget);
        pht->setFixedSize(150,150);
        pht->move(i%3 * 150,i/3 * 150);
        pht->posX = i/3;
        pht->posY = i%3;

        //click to move button
        connect(pht,&QPushButton::clicked,[=](){

            qDebug() << QString("photoNum : %1").arg(pht->photoNum);
            qDebug() << QString("pos : %1 %2").arg(pht->posX).arg(pht->posY);
            movePhoto(pht);
        });
    }

    connect(ui->randomBtn,&QPushButton::clicked,[=](){
        random();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

// A button can be moved if and only if it has a blank button around it
bool MainWindow::ifMove(PhotoPiece * pht)
{
    bool ret = false;

    for(int i=0;i<4;i++)
    {
        int x = pht->posX + dx[i];
        int y = pht->posY + dy[i];

        if(x<0 || x==3 || y<0 || y==3) continue;

        if(photoArray[x][y]->photoNum == 0) ret = true;
    }

    return ret;
}

// swap two button
void MainWindow::movePhoto(PhotoPiece * pht)
{
    for(int i=0;i<4;i++)
    {
        int x = pht->posX + dx[i];
        int y = pht->posY + dy[i];

        if(x<0 || x==3 || y<0 || y==3) continue;

        if(photoArray[x][y]->photoNum == 0)
        {

            QString str = QString::number(pht->photoNum);
            strPhoto.replace(str,"@");
            strPhoto.replace("0",str);
            strPhoto.replace("@","0");

            pht->photoSwap(photoArray[x][y]);

            qDebug() << str;
            qDebug() << strPhoto;

        }
    }
}

void MainWindow::random()
{
    int i = 2,j = 2;
    for(int k=0;k<50;k++)
    {
        int u = rand() % 4;

        int x = i+dx[u];
        int y = j+dy[u];

        if(x<0 || x==3 || y<0 || y==3) continue;
        movePhoto(photoArray[x][y]);
        i = x;
        j = y;
    }
}
