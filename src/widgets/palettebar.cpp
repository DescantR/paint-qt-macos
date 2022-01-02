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

#include "palettebar.h"
#include "../datasingleton.h"

#include <iostream>

PaletteBar::PaletteBar(ToolBar *toolbar) :
    QToolBar(tr("Colors"))
{
    mToolBar = toolbar;
    setMovable(true);
    setStyleSheet("QToolBar { background-color: #FFFFFF; border: 0; } ");
}

void PaletteBar::initializeItems(QList<PaletteButton *> *barSwatches, QGridLayout *sLayout, QWidget *gridWidget, QList<PaletteButton *> *gridSwatches)
{
    sLayout->setContentsMargins(3, 3, 3, 3);
  
    for (int i = 0; i < 16; i++) {
        actionlist.append(addWidget(barSwatches->at(i)));
        connect(barSwatches->at(i), &PaletteButton::colorPicked, this, &PaletteBar::colorClicked);
        sLayout->addWidget(gridSwatches->at(i), i/2, i%2);
        connect(gridSwatches->at(i), &PaletteButton::colorPicked, this, &PaletteBar::colorClicked);
    }
    
    gridWidget->setLayout(sLayout);
    swatch = addWidget(gridWidget);
    actionlist.append(swatch);
    
    hideGridPalette();
}

void PaletteBar::showBarPalette()
{
    for(int i = 0; i < 16; i++){
        actionlist.at(i)->setVisible(true);
    }
}

void PaletteBar::hideBarPalette()
{
    for(int i = 0; i < 16; i++){
        actionlist.at(i)->setVisible(false);
    }
}

void PaletteBar::showGridPalette()
{
    actionlist.at(16)->setVisible(true);
}

void PaletteBar::hideGridPalette()
{
    actionlist.at(16)->setVisible(false);
}

void PaletteBar::moveEvent(QMoveEvent *event)
{
    if(!isFloating()){
        mStartRepaint = true;
        update();
    }
}

void PaletteBar::paintEvent(QPaintEvent *event)
{
    if(mStartRepaint && qMax(contentsRect().height(), contentsRect().width()) == contentsRect().width() && !isFloating()){
        hideGridPalette();
        showBarPalette();
        mStartRepaint = false;
    }
    if(mStartRepaint && qMax(childrenRect().width(), childrenRect().height()) == childrenRect().height() && childrenRect().width()*2 < contentsRect().width() && !isFloating()){
        hideBarPalette();
        showGridPalette();
        mStartRepaint = false;
    }
}

void PaletteBar::colorClicked()
{
    mToolBar->setPrimaryColorView();
    mToolBar->setSecondaryColorView();
}

void PaletteBar::contextMenuEvent(QContextMenuEvent *) { }
