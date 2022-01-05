#include "palettebutton.h"

#include <QMouseEvent>

PaletteButton::PaletteButton(const QColor &color)
{
    mColor = color;
    setMinimumSize(QSize(30, 30));
    setMaximumSize(QSize(30, 30));
    if (color.alpha() == 0){
        QPixmap pixmap(":/media/textures/transparent.jpg");
        setIcon(pixmap.scaled(20, 20, Qt::IgnoreAspectRatio));
        setStatusTip("Transparent");
    } else {
        QPixmap pixmap(20, 20);
        pixmap.fill(color);
        setIcon(pixmap);
        setStatusTip(color.name());
    }
    setObjectName("Picker");
    setStyleSheet("#Picker { border: 1px solid #bfbfbf; } ");
}

void PaletteButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        DataSingleton::Instance()->setPrimaryColor(mColor);
    else if(event->button() == Qt::RightButton)
        DataSingleton::Instance()->setSecondaryColor(mColor);

    emit colorPicked();
}
