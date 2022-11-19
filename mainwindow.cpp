#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QDebug>
#include <QtGlobal>
#include <QHash>
#include <QQueue>
#include <QtAlgorithms>
#include <QPair>
#include <QTimer>
#include <QMessageBox>


int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};
QChar op[] = {'d','u','r','l'};

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/res/icon.jpg"));
    setWindowTitle("Puzzle");

    //ui->groupBox->setStyleSheet("QGroupBox{border:none}");
    ui->groupBox->setStyleSheet(QObject::tr("#groupBox{border: 0px solid;}"));

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

    connect(ui->solveBtn,&QPushButton::clicked,[=](){
        solve(strPhoto);
    });

    connect(ui->showBtn,&QPushButton::clicked,[=](){
        showSolution();
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
            //Record the position of the blank block
            row = pht->posX;
            cl = pht->posY;

            QString str = QString::number(pht->photoNum);
            strPhoto.replace(str,"@");
            strPhoto.replace("0",str);
            strPhoto.replace("@","0");

            pht->photoSwap(photoArray[x][y]);

            qDebug() << str;
            qDebug() << strPhoto;

        }
    }

    if(strPhoto == strStd)
    {
        QMessageBox::information(this, tr("info"), tr("Succeed!"));
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

// A*
void MainWindow::solve(QString start)
{
    if(start == strStd)
    {
        QMessageBox::warning(this, tr("Erro"), tr("Please scramble the picture first"));
        return;
    }

    answer = "";
    QString end = "123456780";
    QHash<QString,int> dist;
    QHash<QString,QPair<QString,QChar> > prev;
    QVector<QPair<int,QString> > heap;

    heap.append({f(start),start});
    dist[start] = 0;

    while(heap.size())
    {
        auto t = heap[0];
        heap.pop_front();

        std::sort(heap.begin(),heap.end());

        QString state = t.second;

        if(state == end) break;

        int step = dist[state];
        int x,y;

        for(int i=0;i<state.size();i++)
            if(state[i]== '0')
            {
                x = i/3;
                y = i%3;
                break;
            }

        QString source = state;

        for(int i=0;i<4;i++)
        {
            int a = x + dx[i],b = y + dy[i];
            if(a <0 || a==3 || b<0 || b==3) continue;

            qSwap(state[x*3 + y],state[a*3 + b]);
            if(!dist.count(state) || dist[state] > step + 1)
            {
                dist[state] = step + 1;
                prev[state] = {source,op[i]};
                heap.push_back({dist[state] + f(state),state});
            }
            qSwap(state[x*3 + y],state[a*3 + b]);
        }
    }
//urddluurrdd
    while(end != start)
    {
        answer += prev[end].second;
        end = prev[end].first;
    }
    qDebug() << answer;
    std::reverse(answer.begin(),answer.end());
    qDebug() << answer;
    QMessageBox::information(this, tr("info"), tr("Succeed!"));
    isSolved = true;
}

//Compute the sum of the Manhattan distances of each number to its standard location
int MainWindow::f(QString state)
{
    int res = 0;
    for (int i = 0; i < state.size(); i ++ )
        if (state[i] != '0')
        {
           int t = state[i].toLatin1() - '1';
           res += abs(i / 3 - t / 3) + abs(i % 3 - t % 3);
        }

    return res;
}

//Show problem-solving steps
void MainWindow::showSolution()
{
    qDebug() << "show function";

    if(isSolved == false)
    {
        qDebug() << "you haven't solve";
        QMessageBox::warning(this, tr("Erro"), tr("Please solve first!"));
        return;
    }
    QTimer * timer = new QTimer(this);
    static int nowStep = 0;

    connect(timer,&QTimer::timeout,[=](){
        solutionStep(nowStep++);

        if(strPhoto == strStd)
        {
            nowStep = 0;
            timer->stop();
        }
    });

    timer->start(300);

    isSolved = false;
}

void MainWindow::solutionStep(int nowStep)
{
    char opt = answer[nowStep].toLatin1();

    if(opt == 'u') movePhoto(photoArray[row-1][cl]);
    if(opt == 'd') movePhoto(photoArray[row+1][cl]);
    if(opt == 'l') movePhoto(photoArray[row][cl-1]);
    if(opt == 'r') movePhoto(photoArray[row][cl+1]);
}
