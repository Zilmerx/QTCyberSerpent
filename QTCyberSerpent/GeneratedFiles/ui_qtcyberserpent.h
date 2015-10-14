/********************************************************************************
** Form generated from reading UI file 'qtcyberserpent.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTCYBERSERPENT_H
#define UI_QTCYBERSERPENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QTCyberSerpentClass
{
public:
    QAction *actionCommencerPartie;
    QAction *actionOptions;
    QAction *actionQuitter;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuMain;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QTCyberSerpentClass)
    {
        if (QTCyberSerpentClass->objectName().isEmpty())
            QTCyberSerpentClass->setObjectName(QStringLiteral("QTCyberSerpentClass"));
        QTCyberSerpentClass->resize(550, 500);
        actionCommencerPartie = new QAction(QTCyberSerpentClass);
        actionCommencerPartie->setObjectName(QStringLiteral("actionCommencerPartie"));
        actionOptions = new QAction(QTCyberSerpentClass);
        actionOptions->setObjectName(QStringLiteral("actionOptions"));
        actionQuitter = new QAction(QTCyberSerpentClass);
        actionQuitter->setObjectName(QStringLiteral("actionQuitter"));
        centralWidget = new QWidget(QTCyberSerpentClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QTCyberSerpentClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QTCyberSerpentClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 550, 21));
        menuMain = new QMenu(menuBar);
        menuMain->setObjectName(QStringLiteral("menuMain"));
        QTCyberSerpentClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(QTCyberSerpentClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QTCyberSerpentClass->setStatusBar(statusBar);

        menuBar->addAction(menuMain->menuAction());
        menuMain->addAction(actionCommencerPartie);
        menuMain->addAction(actionOptions);
        menuMain->addAction(actionQuitter);

        retranslateUi(QTCyberSerpentClass);

        QMetaObject::connectSlotsByName(QTCyberSerpentClass);
    } // setupUi

    void retranslateUi(QMainWindow *QTCyberSerpentClass)
    {
        QTCyberSerpentClass->setWindowTitle(QApplication::translate("QTCyberSerpentClass", "QTCyberSerpent", 0));
        actionCommencerPartie->setText(QApplication::translate("QTCyberSerpentClass", "Commencer la partie", 0));
        actionOptions->setText(QApplication::translate("QTCyberSerpentClass", "Options", 0));
        actionQuitter->setText(QApplication::translate("QTCyberSerpentClass", "Quitter", 0));
        menuMain->setTitle(QApplication::translate("QTCyberSerpentClass", "Jeu", 0));
    } // retranslateUi

};

namespace Ui {
    class QTCyberSerpentClass: public Ui_QTCyberSerpentClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTCYBERSERPENT_H
