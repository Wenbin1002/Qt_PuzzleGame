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

    QString strPhoto = "123456780";

    bool ifMove(PhotoPiece * );

    void movePhoto(PhotoPiece *);
    void random();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
