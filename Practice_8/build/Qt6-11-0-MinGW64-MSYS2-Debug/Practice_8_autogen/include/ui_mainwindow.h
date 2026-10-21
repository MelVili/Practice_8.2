/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *leftPanelLayout;
    QLabel *lblTitle;
    QLabel *lblStats;
    QPushButton *btnStartStop;
    QPushButton *btnClear;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *chartsLayout;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1050, 680);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow { background-color: #0d1117; }\n"
"QLabel#lblTitle { color: #58a6ff; font-size: 16px; font-weight: bold; padding-bottom: 5px; }\n"
"QLabel#lblStats {\n"
"    background-color: #161b22; color: #c9d1d9;\n"
"    border: 1px solid #30363d; border-radius: 8px;\n"
"    padding: 12px; font-family: Consolas, monospace; font-size: 13px;\n"
"}\n"
"QPushButton {\n"
"    background-color: #21262d; color: #c9d1d9;\n"
"    border: 1px solid #30363d; border-radius: 6px;\n"
"    padding: 10px; font-size: 13px; font-weight: bold;\n"
"}\n"
"QPushButton:hover { background-color: #30363d; border-color: #8b949e; }\n"
"QPushButton:pressed { background-color: #161b22; }"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(16);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(16, 16, 16, 16);
        leftPanelLayout = new QVBoxLayout();
        leftPanelLayout->setSpacing(12);
        leftPanelLayout->setObjectName("leftPanelLayout");
        lblTitle = new QLabel(centralwidget);
        lblTitle->setObjectName("lblTitle");
        lblTitle->setAlignment(Qt::AlignCenter);

        leftPanelLayout->addWidget(lblTitle);

        lblStats = new QLabel(centralwidget);
        lblStats->setObjectName("lblStats");
        lblStats->setMinimumSize(QSize(260, 230));
        lblStats->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        leftPanelLayout->addWidget(lblStats);

        btnStartStop = new QPushButton(centralwidget);
        btnStartStop->setObjectName("btnStartStop");

        leftPanelLayout->addWidget(btnStartStop);

        btnClear = new QPushButton(centralwidget);
        btnClear->setObjectName("btnClear");

        leftPanelLayout->addWidget(btnClear);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        leftPanelLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(leftPanelLayout);

        chartsLayout = new QVBoxLayout();
        chartsLayout->setSpacing(12);
        chartsLayout->setObjectName("chartsLayout");

        horizontalLayout->addLayout(chartsLayout);

        horizontalLayout->setStretch(1, 1);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\265\320\274\320\275\320\260\321\217 \321\201\321\202\320\260\320\275\321\206\320\270\321\217: \320\242\320\265\320\273\320\265\320\274\320\265\321\202\321\200\320\270\321\217 \320\221\320\237\320\233\320\220", nullptr));
        lblTitle->setText(QCoreApplication::translate("MainWindow", "\320\237\320\243\320\233\320\254\320\242 \320\242\320\225\320\233\320\225\320\234\320\225\320\242\320\240\320\230\320\230", nullptr));
        lblStats->setText(QCoreApplication::translate("MainWindow", "\320\236\320\266\320\270\320\264\320\260\320\275\320\270\320\265 \320\264\320\260\320\275\320\275\321\213\321\205...", nullptr));
        btnStartStop->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\203\320\267\320\260 \321\202\320\265\320\273\320\265\320\274\320\265\321\202\321\200\320\270\320\270", nullptr));
        btnClear->setText(QCoreApplication::translate("MainWindow", "\320\241\320\261\321\200\320\276\321\201\320\270\321\202\321\214 \320\270\321\201\321\202\320\276\321\200\320\270\321\216", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
