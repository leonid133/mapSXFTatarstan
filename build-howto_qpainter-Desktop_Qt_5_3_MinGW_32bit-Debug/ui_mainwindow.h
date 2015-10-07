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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *OpenFileButton;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QGroupBox *verticalGroupBox;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *checkBox_15;
    QCheckBox *checkBox_16;
    QFrame *line_3;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_6;
    QFrame *line;
    QCheckBox *checkBox_7;
    QCheckBox *checkBox_8;
    QCheckBox *checkBox_9;
    QCheckBox *checkBox_10;
    QCheckBox *checkBox_11;
    QFrame *line_2;
    QCheckBox *checkBox_12;
    QCheckBox *checkBox_13;
    QCheckBox *checkBox_14;
    QVBoxLayout *verticalLayout;
    QMenuBar *menuBar;
    QMenu *menuMapSXF;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(600, 425);
        OpenFileButton = new QAction(MainWindow);
        OpenFileButton->setObjectName(QStringLiteral("OpenFileButton"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalGroupBox = new QGroupBox(centralWidget);
        verticalGroupBox->setObjectName(QStringLiteral("verticalGroupBox"));
        verticalGroupBox->setMaximumSize(QSize(100, 16777215));
        verticalLayout_3 = new QVBoxLayout(verticalGroupBox);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setSizeConstraint(QLayout::SetMinimumSize);
        checkBox_15 = new QCheckBox(verticalGroupBox);
        checkBox_15->setObjectName(QStringLiteral("checkBox_15"));

        verticalLayout_3->addWidget(checkBox_15);

        checkBox_16 = new QCheckBox(verticalGroupBox);
        checkBox_16->setObjectName(QStringLiteral("checkBox_16"));

        verticalLayout_3->addWidget(checkBox_16);

        line_3 = new QFrame(verticalGroupBox);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line_3);

        checkBox = new QCheckBox(verticalGroupBox);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setChecked(true);

        verticalLayout_3->addWidget(checkBox);

        checkBox_2 = new QCheckBox(verticalGroupBox);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setChecked(true);

        verticalLayout_3->addWidget(checkBox_2);

        checkBox_3 = new QCheckBox(verticalGroupBox);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));
        checkBox_3->setChecked(true);

        verticalLayout_3->addWidget(checkBox_3);

        checkBox_4 = new QCheckBox(verticalGroupBox);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));
        checkBox_4->setChecked(true);

        verticalLayout_3->addWidget(checkBox_4);

        checkBox_5 = new QCheckBox(verticalGroupBox);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));
        checkBox_5->setChecked(true);

        verticalLayout_3->addWidget(checkBox_5);

        checkBox_6 = new QCheckBox(verticalGroupBox);
        checkBox_6->setObjectName(QStringLiteral("checkBox_6"));
        checkBox_6->setChecked(true);

        verticalLayout_3->addWidget(checkBox_6);

        line = new QFrame(verticalGroupBox);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line);

        checkBox_7 = new QCheckBox(verticalGroupBox);
        checkBox_7->setObjectName(QStringLiteral("checkBox_7"));
        checkBox_7->setChecked(true);

        verticalLayout_3->addWidget(checkBox_7);

        checkBox_8 = new QCheckBox(verticalGroupBox);
        checkBox_8->setObjectName(QStringLiteral("checkBox_8"));
        checkBox_8->setChecked(true);

        verticalLayout_3->addWidget(checkBox_8);

        checkBox_9 = new QCheckBox(verticalGroupBox);
        checkBox_9->setObjectName(QStringLiteral("checkBox_9"));
        checkBox_9->setChecked(true);

        verticalLayout_3->addWidget(checkBox_9);

        checkBox_10 = new QCheckBox(verticalGroupBox);
        checkBox_10->setObjectName(QStringLiteral("checkBox_10"));
        checkBox_10->setChecked(true);

        verticalLayout_3->addWidget(checkBox_10);

        checkBox_11 = new QCheckBox(verticalGroupBox);
        checkBox_11->setObjectName(QStringLiteral("checkBox_11"));
        checkBox_11->setChecked(true);

        verticalLayout_3->addWidget(checkBox_11);

        line_2 = new QFrame(verticalGroupBox);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line_2);

        checkBox_12 = new QCheckBox(verticalGroupBox);
        checkBox_12->setObjectName(QStringLiteral("checkBox_12"));
        checkBox_12->setChecked(true);

        verticalLayout_3->addWidget(checkBox_12);

        checkBox_13 = new QCheckBox(verticalGroupBox);
        checkBox_13->setObjectName(QStringLiteral("checkBox_13"));
        checkBox_13->setChecked(true);

        verticalLayout_3->addWidget(checkBox_13);

        checkBox_14 = new QCheckBox(verticalGroupBox);
        checkBox_14->setObjectName(QStringLiteral("checkBox_14"));
        checkBox_14->setChecked(true);

        verticalLayout_3->addWidget(checkBox_14);


        horizontalLayout->addWidget(verticalGroupBox);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menuMapSXF = new QMenu(menuBar);
        menuMapSXF->setObjectName(QStringLiteral("menuMapSXF"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuMapSXF->menuAction());
        menuMapSXF->addAction(OpenFileButton);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        OpenFileButton->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", 0));
        OpenFileButton->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        checkBox_15->setText(QApplication::translate("MainWindow", "\320\236\320\261\321\212\320\265\320\272\321\202\321\213(\321\202\320\276\321\207\320\272\320\270, \320\273\320\270\320\275\320\270\320\270)", 0));
        checkBox_16->setText(QApplication::translate("MainWindow", "\320\236\320\261\321\212\320\265\320\272\321\202\321\213 (\320\277\320\276\320\273\320\270\320\263\320\276\320\275\321\213, \320\274\320\265\321\202\320\272\320\270)", 0));
        checkBox->setText(QApplication::translate("MainWindow", "\320\236\320\227\320\225\320\240\320\220 (\320\237\320\236\320\241\320\242\320\236\320\257\320\235\320\235\320\253\320\225)", 0));
        checkBox_2->setText(QApplication::translate("MainWindow", "\320\222\320\236\320\224\320\236\320\245\320\240\320\220\320\235\320\230\320\233\320\230\320\251\320\220 \320\224\320\225\320\231\320\241\320\242\320\222\320\243\320\256\320\251\320\230\320\225", 0));
        checkBox_3->setText(QApplication::translate("MainWindow", "\320\240\320\225\320\232\320\230 \320\237\320\236\320\241\320\242\320\236\320\257\320\235\320\253\320\225 (\320\276\321\202 20-120 \320\274)", 0));
        checkBox_4->setText(QApplication::translate("MainWindow", "\320\232\320\220\320\235\320\220\320\233\320\253", 0));
        checkBox_5->setText(QApplication::translate("MainWindow", "\320\243\320\240\320\225\320\227\320\253 \320\222\320\236\320\224\320\253 ", 0));
        checkBox_6->setText(QApplication::translate("MainWindow", "\320\221\320\236\320\233\320\236\320\242\320\220 \320\235\320\225\320\237\320\240\320\236\320\245\320\236\320\224\320\230\320\234\320\253\320\225", 0));
        checkBox_7->setText(QApplication::translate("MainWindow", "\320\224\320\236\320\240\320\236\320\223\320\230 \320\223\320\240\320\243\320\235\320\242\320\236\320\222\320\253\320\225 \320\237\320\240\320\236\320\241\320\225\320\233\320\236\320\247\320\235\320\253\320\225", 0));
        checkBox_8->setText(QApplication::translate("MainWindow", "\320\224\320\236\320\240\320\236\320\223\320\230 \320\237\320\236\320\233\320\225\320\222\320\253\320\225,\320\233\320\225\320\241\320\235\320\253\320\225", 0));
        checkBox_9->setText(QApplication::translate("MainWindow", "\320\243\320\233\320\243\320\247\320\250\320\225\320\235\320\235\320\253\320\225 \320\223\320\240\320\243\320\235\320\242.\320\224\320\236\320\240\320\236\320\223\320\230 \320\224\320\225\320\231\320\241\320\242\320\222", 0));
        checkBox_10->setText(QApplication::translate("MainWindow", "\320\224\320\236\320\240\320\236\320\223\320\230 \320\242\320\240\320\243\320\224\320\235\320\236\320\237\320\240\320\236\320\225\320\227\320\226\320\230\320\225(\321\203\320\273\321\203\321\207.\320\263\321\200)", 0));
        checkBox_11->setText(QApplication::translate("MainWindow", "\320\234\320\236\320\241\320\242\320\253 \320\237\320\240\320\236\320\247\320\230\320\225", 0));
        checkBox_12->setText(QApplication::translate("MainWindow", "\320\250\320\236\320\241\320\241\320\225 \320\243\320\241\320\236\320\222\320\225\320\240\320\250\320\225\320\235\320\241\320\242\320\222.(\320\224\320\225\320\231\320\241\320\242\320\222.)", 0));
        checkBox_13->setText(QApplication::translate("MainWindow", "\320\250\320\236\320\241\320\241\320\225 \320\224\320\225\320\231\320\241\320\242\320\222\320\243\320\256\320\251\320\230\320\225", 0));
        checkBox_14->setText(QApplication::translate("MainWindow", "\320\234\320\236\320\241\320\242\320\253 \320\235\320\220 \320\240\320\220\320\227\320\236\320\221\320\251\320\225\320\235\320\235.\320\236\320\241\320\235\320\236\320\222\320\220\320\235\320\230\320\257\320\245 ", 0));
        menuMapSXF->setTitle(QApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
