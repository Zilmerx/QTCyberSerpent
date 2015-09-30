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
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QTCyberSerpentClass
{
public:
    QAction *actionCECI_EST_UN_BOUTONN;
    QAction *actionOptions;
    QAction *actionQuitter;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuHERPDERP;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QTCyberSerpentClass)
    {
        if (QTCyberSerpentClass->objectName().isEmpty())
            QTCyberSerpentClass->setObjectName(QStringLiteral("QTCyberSerpentClass"));
        QTCyberSerpentClass->resize(819, 631);
        actionCECI_EST_UN_BOUTONN = new QAction(QTCyberSerpentClass);
        actionCECI_EST_UN_BOUTONN->setObjectName(QStringLiteral("actionCECI_EST_UN_BOUTONN"));
        actionOptions = new QAction(QTCyberSerpentClass);
        actionOptions->setObjectName(QStringLiteral("actionOptions"));
        actionQuitter = new QAction(QTCyberSerpentClass);
        actionQuitter->setObjectName(QStringLiteral("actionQuitter"));
        centralWidget = new QWidget(QTCyberSerpentClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QTCyberSerpentClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QTCyberSerpentClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 819, 21));
        menuHERPDERP = new QMenu(menuBar);
        menuHERPDERP->setObjectName(QStringLiteral("menuHERPDERP"));
        QTCyberSerpentClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QTCyberSerpentClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QTCyberSerpentClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QTCyberSerpentClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QTCyberSerpentClass->setStatusBar(statusBar);

        menuBar->addAction(menuHERPDERP->menuAction());
        menuHERPDERP->addAction(actionCECI_EST_UN_BOUTONN);
        menuHERPDERP->addAction(actionOptions);
        menuHERPDERP->addAction(actionQuitter);

        retranslateUi(QTCyberSerpentClass);

        QMetaObject::connectSlotsByName(QTCyberSerpentClass);
    } // setupUi

    void retranslateUi(QMainWindow *QTCyberSerpentClass)
    {
        QTCyberSerpentClass->setWindowTitle(QApplication::translate("QTCyberSerpentClass", "QTCyberSerpent", 0));
        actionCECI_EST_UN_BOUTONN->setText(QApplication::translate("QTCyberSerpentClass", "Commencer la partie", 0));
        actionOptions->setText(QApplication::translate("QTCyberSerpentClass", "Options", 0));
        actionQuitter->setText(QApplication::translate("QTCyberSerpentClass", "Quitter", 0));
        menuHERPDERP->setTitle(QApplication::translate("QTCyberSerpentClass", "Jeu", 0));
    } // retranslateUi

};

namespace Ui {
    class QTCyberSerpentClass: public Ui_QTCyberSerpentClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTCYBERSERPENT_H
