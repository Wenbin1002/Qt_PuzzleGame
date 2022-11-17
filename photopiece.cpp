#include "photopiece.h"
#include <QtAlgorithms>

PhotoPiece::PhotoPiece(QString img)
{
    imgPath = img;
    QPixmap pix;
    pix.load(img);
    setIcon(pix);
    setIconSize(QSize(148,148));
}

//exchange photo
void PhotoPiece::photoSwap(PhotoPiece * btn)
{
    qSwap(this->imgPath,btn->imgPath);
    qSwap(this->photoNum,btn->photoNum);
    this->setIcon(QIcon(this->imgPath));
    btn->setIcon(QIcon(btn->imgPath));
}
