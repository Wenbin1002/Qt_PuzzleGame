#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mypushbutton.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/res/icon.jpg"));
    setWindowTitle("Puzzle");

    for(int i=0;i<9;i++)
    {
        QString str = QString(":/res/img-%1.png").arg((i+1)%9);
        MyPushButton * btn = new MyPushButton(str);
        btn->setParent(ui->mianWidget);
        btn->setFixedSize(150,150);
        btn->move(i%3 * 150,i/3 * 150);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

