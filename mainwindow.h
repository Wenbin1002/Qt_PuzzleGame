#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "photopiece.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    PhotoPiece * photoArray[3][3];

    QString strStd = "123456780";
    QString strPhoto = "123456780";
    QString answer;

    int row = 2,cl = 2;

    bool ifMove(PhotoPiece * );

    void movePhoto(PhotoPiece *);
    void random();
    void solve(QString start);
    int f(QString state);
    void showSolution();
    void solutionStep(int nowStep);

    bool isSolved = false;


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
