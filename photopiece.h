#ifndef PHOTOPIECE_H
#define PHOTOPIECE_H

#include <QPushButton>

class PhotoPiece : public QPushButton
{
    Q_OBJECT
public:
    PhotoPiece(QString img = ":/res/img-0.png");

    QString imgPath;
    int photoNum;
    int posX,posY;

    void photoSwap(PhotoPiece * );

signals:

};

#endif // PHOTOPIECE_H
