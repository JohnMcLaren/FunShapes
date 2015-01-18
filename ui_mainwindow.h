/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionTriangle;
    QAction *actionRectangle;
    QAction *actionCircle;
    QAction *actionDelete;
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionAboutQt;
    QAction *actionText;
    QAction *actionImage;
    QAction *actionGeometry;
    QAction *actionRotate;
    QAction *actionLink;
    QWidget *centralWidget;
    QLabel *lblXY;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuObject;
    QMenu *menuHelp;
    QMenu *menuEditing_Mode;
    QToolBar *toolFile;
    QStatusBar *statusBar;
    QToolBar *toolEdit;
    QToolBar *toolObject;
    QToolBar *toolMode;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(777, 393);
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QStringLiteral("actionUndo"));
        actionUndo->setEnabled(true);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/Undo.png"), QSize(), QIcon::Normal, QIcon::On);
        actionUndo->setIcon(icon);
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QStringLiteral("actionRedo"));
        actionRedo->setEnabled(true);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/Redo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRedo->setIcon(icon1);
        QFont font;
        actionRedo->setFont(font);
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName(QStringLiteral("actionCut"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/cut.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCut->setIcon(icon2);
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QStringLiteral("actionCopy"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/copy.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCopy->setIcon(icon3);
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName(QStringLiteral("actionPaste"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/paste.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPaste->setIcon(icon4);
        actionTriangle = new QAction(MainWindow);
        actionTriangle->setObjectName(QStringLiteral("actionTriangle"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/Triangle.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTriangle->setIcon(icon5);
        actionRectangle = new QAction(MainWindow);
        actionRectangle->setObjectName(QStringLiteral("actionRectangle"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/images/Rectangle.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRectangle->setIcon(icon6);
        actionCircle = new QAction(MainWindow);
        actionCircle->setObjectName(QStringLiteral("actionCircle"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/images/Circle.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCircle->setIcon(icon7);
        actionDelete = new QAction(MainWindow);
        actionDelete->setObjectName(QStringLiteral("actionDelete"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/images/Delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete->setIcon(icon8);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/images/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon9);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/images/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon10);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon11);
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        actionAboutQt = new QAction(MainWindow);
        actionAboutQt->setObjectName(QStringLiteral("actionAboutQt"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/images/Qt.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAboutQt->setIcon(icon12);
        actionText = new QAction(MainWindow);
        actionText->setObjectName(QStringLiteral("actionText"));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/images/Text.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionText->setIcon(icon13);
        actionImage = new QAction(MainWindow);
        actionImage->setObjectName(QStringLiteral("actionImage"));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/images/Image.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionImage->setIcon(icon14);
        actionGeometry = new QAction(MainWindow);
        actionGeometry->setObjectName(QStringLiteral("actionGeometry"));
        actionGeometry->setCheckable(true);
        actionGeometry->setChecked(true);
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/images/geometry_edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGeometry->setIcon(icon15);
        actionRotate = new QAction(MainWindow);
        actionRotate->setObjectName(QStringLiteral("actionRotate"));
        actionRotate->setCheckable(true);
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/images/rotate2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRotate->setIcon(icon16);
        actionLink = new QAction(MainWindow);
        actionLink->setObjectName(QStringLiteral("actionLink"));
        actionLink->setCheckable(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lblXY = new QLabel(centralWidget);
        lblXY->setObjectName(QStringLiteral("lblXY"));
        lblXY->setGeometry(QRect(520, 280, 46, 20));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        lblXY->setFont(font1);
        lblXY->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 777, 20));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuObject = new QMenu(menuBar);
        menuObject->setObjectName(QStringLiteral("menuObject"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuEditing_Mode = new QMenu(menuBar);
        menuEditing_Mode->setObjectName(QStringLiteral("menuEditing_Mode"));
        MainWindow->setMenuBar(menuBar);
        toolFile = new QToolBar(MainWindow);
        toolFile->setObjectName(QStringLiteral("toolFile"));
        toolFile->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolFile);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolEdit = new QToolBar(MainWindow);
        toolEdit->setObjectName(QStringLiteral("toolEdit"));
        toolEdit->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolEdit);
        toolObject = new QToolBar(MainWindow);
        toolObject->setObjectName(QStringLiteral("toolObject"));
        toolObject->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolObject);
        toolMode = new QToolBar(MainWindow);
        toolMode->setObjectName(QStringLiteral("toolMode"));
        toolMode->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolMode);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuObject->menuAction());
        menuBar->addAction(menuEditing_Mode->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_As);
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);
        menuEdit->addSeparator();
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuObject->addAction(actionTriangle);
        menuObject->addAction(actionRectangle);
        menuObject->addAction(actionCircle);
        menuObject->addAction(actionText);
        menuObject->addAction(actionImage);
        menuObject->addSeparator();
        menuObject->addAction(actionDelete);
        menuHelp->addAction(actionAboutQt);
        menuEditing_Mode->addAction(actionGeometry);
        menuEditing_Mode->addAction(actionRotate);
        menuEditing_Mode->addAction(actionLink);
        toolFile->addAction(actionNew);
        toolFile->addAction(actionOpen);
        toolFile->addAction(actionSave);
        toolEdit->addAction(actionCut);
        toolEdit->addAction(actionCopy);
        toolEdit->addAction(actionPaste);
        toolEdit->addSeparator();
        toolEdit->addAction(actionUndo);
        toolEdit->addAction(actionRedo);
        toolObject->addAction(actionTriangle);
        toolObject->addAction(actionRectangle);
        toolObject->addAction(actionCircle);
        toolObject->addAction(actionText);
        toolObject->addAction(actionImage);
        toolObject->addSeparator();
        toolObject->addAction(actionDelete);
        toolMode->addAction(actionGeometry);
        toolMode->addAction(actionRotate);
        toolMode->addAction(actionLink);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        actionUndo->setText(QApplication::translate("MainWindow", "Undo", 0));
        actionUndo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", 0));
        actionRedo->setText(QApplication::translate("MainWindow", "Redo", 0));
        actionRedo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Y", 0));
        actionCut->setText(QApplication::translate("MainWindow", "Cut", 0));
        actionCut->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", 0));
        actionCopy->setText(QApplication::translate("MainWindow", "Copy", 0));
        actionCopy->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", 0));
        actionPaste->setText(QApplication::translate("MainWindow", "Paste", 0));
        actionPaste->setShortcut(QApplication::translate("MainWindow", "Ctrl+V", 0));
        actionTriangle->setText(QApplication::translate("MainWindow", "Triangle", 0));
        actionTriangle->setShortcut(QApplication::translate("MainWindow", "Ctrl+1", 0));
        actionRectangle->setText(QApplication::translate("MainWindow", "Rectangle", 0));
        actionRectangle->setShortcut(QApplication::translate("MainWindow", "Ctrl+2", 0));
        actionCircle->setText(QApplication::translate("MainWindow", "Circle", 0));
        actionCircle->setShortcut(QApplication::translate("MainWindow", "Ctrl+3", 0));
        actionDelete->setText(QApplication::translate("MainWindow", "Delete", 0));
        actionDelete->setShortcut(QApplication::translate("MainWindow", "Del", 0));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0));
        actionNew->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0));
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        actionSave_As->setText(QApplication::translate("MainWindow", "Save As..", 0));
        actionAboutQt->setText(QApplication::translate("MainWindow", "About Qt", 0));
        actionText->setText(QApplication::translate("MainWindow", "Text", 0));
#ifndef QT_NO_TOOLTIP
        actionText->setToolTip(QApplication::translate("MainWindow", "Text", 0));
#endif // QT_NO_TOOLTIP
        actionImage->setText(QApplication::translate("MainWindow", "Image", 0));
#ifndef QT_NO_TOOLTIP
        actionImage->setToolTip(QApplication::translate("MainWindow", "Image", 0));
#endif // QT_NO_TOOLTIP
        actionGeometry->setText(QApplication::translate("MainWindow", "Geometry", 0));
        actionRotate->setText(QApplication::translate("MainWindow", "Rotate", 0));
        actionLink->setText(QApplication::translate("MainWindow", "Link", 0));
        lblXY->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0));
        menuObject->setTitle(QApplication::translate("MainWindow", "Object", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
        menuEditing_Mode->setTitle(QApplication::translate("MainWindow", "Editing Mode", 0));
        toolEdit->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
        toolObject->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
        toolMode->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
