/*
 * This source file is part of EasyPaint.
 *
 * Copyright (c) 2012 EasyPaint <https://github.com/Gr1N/EasyPaint>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "colorchooser.h"

#include <QColor>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>
#include <QColorDialog>

ColorChooser::ColorChooser(const int &r, const int &g, const int &b, QWidget *parent) :
    QLabel(parent)
{
    setFrameStyle(QFrame::Raised | QFrame::Box);
    mCurrentColor = new QColor(r, g, b);
    mPixmapColor = new QPixmap(20, 20);
    mPainterColor = new QPainter(mPixmapColor);
    mPainterColor->fillRect(0, 0, 20, 20, QColor(255,255,255,255));
    mPainterColor->fillRect(0, 0, 20, 20, *mCurrentColor);
    mPainterColor->end();
    setMargin(3);
    setAlignment(Qt::AlignHCenter);
    if (mCurrentColor->alpha() == 0){
        QPixmap pixmap(":/media/textures/transparent.jpg");
        setPixmap(pixmap.scaled(20, 20, Qt::IgnoreAspectRatio));
    } else {
      setPixmap(*mPixmapColor);
    }
}

ColorChooser::~ColorChooser()
{
    delete mCurrentColor;
    delete mPainterColor;
    delete mPixmapColor;
}

void ColorChooser::setColor(const QColor &color)
{
    *mCurrentColor = color;
    if (mCurrentColor->alpha() == 0) {
        QPixmap pixmap(":/media/textures/transparent.jpg");
        setPixmap(pixmap.scaled(20, 20, Qt::IgnoreAspectRatio));
    } else {
        mPainterColor->begin(mPixmapColor);
        mPainterColor->fillRect(0, 0, 20, 20, QColor(255,255,255,255));
        mPainterColor->fillRect(0, 0, 20, 20, *mCurrentColor);
        mPainterColor->end();
        setPixmap(*mPixmapColor);
    }
}

void ColorChooser::emitUndoStackUpdate(const QColor &color)
{
    ColorChooser* self = this;
    emit sendUndoStackColorUpdate(*mCurrentColor, color, self);
}

void ColorChooser::emitColor(const QColor &color)
{
    emit sendColor(color);
}

const QColor ColorChooser::getColor()
{
    return *mCurrentColor;
}

void ColorChooser::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        QColor color = QColorDialog::getColor(*mCurrentColor, this, QString("Pick a Color"), 
        {QColorDialog::ShowAlphaChannel, QColorDialog::DontUseNativeDialog});
        if(color.isValid())
        {
            emitUndoStackUpdate(color);
            setColor(color);
            emitColor(color);
        }
    }
}
