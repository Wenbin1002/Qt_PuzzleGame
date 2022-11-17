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

    PhotoPiece * btnArry[3][3];

    bool ifMove(PhotoPiece * );

    void moveBtn(PhotoPiece *);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
