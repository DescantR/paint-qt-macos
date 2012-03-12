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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

#include "easypaintenums.h"

QT_BEGIN_NAMESPACE
class QAction;
class QStatusBar;
class QTabWidget;
class ToolBar;
class ImageArea;
class QLabel;
QT_END_NAMESPACE

/**
 * @brief Main window class.
 *
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QStringList filePaths, QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private:
    void initializeMainMenu();
    void initializeStatusBar();
    void initializeToolBar();
    void initializeTabWidget();
    /**
     * @brief Initialize new tab for tab bar with new ImageArea and connect all needed slots.
     *
     * @param isOpen Flag which shows opens a new image or from file.
     * @param filePath File path
     */
    void initializeNewTab(const bool &isOpen = false, const QString &filePath = "");
    /**
     * @brief Get current ImageArea from current tab.
     *
     * @return ImageArea Geted ImageArea.
     */
    ImageArea* getCurrentImageArea();
    /**
     * @brief Get ImageArea from QTabWidget by index.
     *
     * @param index tab index
     * @return ImageArea, which corresponds to the index.
     */
    ImageArea* getImageAreaByIndex(int index);
    bool closeAllTabs();
    bool isSomethingModified();

    QStatusBar *mStatusBar;
    QTabWidget *mTabWidget;
    ToolBar *mToolbar;
    QLabel *mSizeLabel, *mPosLabel, *mColorLabel;

    QAction *mCursorAction, *mLasticAction, *mPipetteAction, *mLoupeAction,
            *mPenAction, *mLineAction, *mSprayAction, *mFillAction,
            *mRectAction, *mEllipseAction,
            *mSaveAction, *mSaveAsAction, *mCloseAction, *mPrintAction,
            *mUndoAction, *mRedoAction, *mCopyAction, *mCutAction;
    QMenu *mInstrumentsMenu, *mEffectsMenu, *mToolsMenu;

private slots:
    void activateTab(const int &index);
    void setNewSizeToSizeLabel(const QSize &size);
    void setNewPosToPosLabel(const QPoint &pos);
    void setCurrentPipetteColor(const QColor &color);
    void clearStatusBarColor();
    void setInstrumentChecked(InstrumentsEnum instrument);
    void newAct();
    void openAct();
    void helpAct();
    void saveAct();
    void saveAsAct();
    void printAct();
    void settingsAct();
    void effectGrayAct();
    void effectNegativeAct();
    void resizeImageAct();
    void resizeCanvasAct();
    void rotateLeftImageAct();
    void rotateRightImageAct();
    void closeTabAct();
    void closeTab(int index);
    void setAllInstrumentsUnchecked(QAction *action);
    void cursorAct(const bool &state);
    void lasticAct(const bool &state);
    void pipetteAct(const bool &state);
    void loupeAct(const bool &state);
    void penAct(const bool &state);
    void lineAct(const bool &state);
    void sprayAct(const bool &state);
    void fillAct(const bool &state);
    void rectAct(const bool &state);
    void ellipseAct(const bool &state);
    void enableActions(int index);

signals:
    void sendInstrumentChecked(InstrumentsEnum);

};

#endif // MAINWINDOW_H
