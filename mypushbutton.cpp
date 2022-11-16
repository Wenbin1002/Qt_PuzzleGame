#include "mypushbutton.h"

MyPushButton::MyPushButton(QString img)
{
    QPixmap pix;
    pix.load(img);
    setIcon(pix);
    setIconSize(QSize(148,148));
}
