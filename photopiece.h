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
    bool isMovable = false;

    void btnSwap(PhotoPiece * );

signals:

};

#endif // PHOTOPIECE_H
