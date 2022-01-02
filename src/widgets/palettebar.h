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

#ifndef PALETTEBAR_H
#define PALETTEBAR_H

#include "toolbar.h"
#include "palettebutton.h"

#include <QToolBar>
#include <QGridLayout>

/**
  * @brief Toolbar with some number of differrent colors
  *
  */
class PaletteBar : public QToolBar
{
    Q_OBJECT

public:
    PaletteBar(ToolBar *toolBar);
    /**
      * @brief Color buttons initializing
      *
      */
    void initializeItems(QList<PaletteButton *> *barSwatches, QGridLayout *sLayout, QWidget *gridWidget, QList<PaletteButton *> *gridSwatches);
    void hideGridPalette();
    void showGridPalette();
    void hideBarPalette();
    void showBarPalette();

private:
    /**
     * @brief Create new QToolButton
     *
     * @param name Color name
     * @param color Color of button
     * @return QToolButton Created QToolButton.
     */
    QList<QAction *> actionlist;
    PaletteButton *mColorButton;
    QAction *swatch;
    ToolBar *mToolBar;
    bool mIsRightButtonCLicked;
    bool mStartRepaint;
    bool mRepaintedGrid;
    void paintEvent(QPaintEvent *event);
    void moveEvent(QMoveEvent *event);

private slots:
    void colorClicked();

protected:
    void contextMenuEvent(QContextMenuEvent *);
};

#endif // PALETTEBAR_H
