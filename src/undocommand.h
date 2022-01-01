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

#ifndef UNDOCOMMAND_H
#define UNDOCOMMAND_H

#include <QUndoCommand>
#include <QColor>
#include <QImage>

#include "imagearea.h"
#include "widgets/colorchooser.h"

/**
 * @brief Class which provides undo/redo actions
 *
 * In future it should be changed according to architecture changing
 */
class UndoCommand : public QUndoCommand
{
public:
    enum CommandType {IMAGE, COLOR_PICKER};
    UndoCommand(const QImage *img, ImageArea *imgArea, QUndoCommand *parent = 0);
    UndoCommand(const QColor prevColor, const QColor currColor, ColorChooser *colorChooser, QUndoCommand *parent = 0);

    virtual void undo();
    virtual void redo();
private:
    QImage mPrevImage;
    QImage mCurrImage;
    QColor mPrevColor;
    QColor mCurrColor;
    ImageArea *mImageArea;
    ColorChooser *mColorChooser;
    
    CommandType mType;
};

#endif // UNDOCOMMAND_H
