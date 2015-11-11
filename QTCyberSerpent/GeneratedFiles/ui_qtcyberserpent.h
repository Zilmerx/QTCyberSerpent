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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QTCyberSerpentClass
{
public:
    QAction *actionNouvellePartie;
    QAction *actionOptions;
    QAction *actionQuitter;
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *LayoutOptions;
    QLabel *label_CameraPath;
    QLineEdit *lineEdit_CameraNum;
    QLabel *label_MaxScore;
    QLabel *label_NbObstacles;
    QLabel *label_PortConnexion;
    QLineEdit *lineEdit_NbObstacles;
    QLineEdit *lineEdit_MaxScore;
    QLineEdit *lineEdit_PortConnexion;
    QPushButton *pushButton_ValiderInfos;
    QMenuBar *menuBar;
    QMenu *menuMain;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QTCyberSerpentClass)
    {
        if (QTCyberSerpentClass->objectName().isEmpty())
            QTCyberSerpentClass->setObjectName(QStringLiteral("QTCyberSerpentClass"));
        QTCyberSerpentClass->resize(784, 500);
        actionNouvellePartie = new QAction(QTCyberSerpentClass);
        actionNouvellePartie->setObjectName(QStringLiteral("actionNouvellePartie"));
        actionOptions = new QAction(QTCyberSerpentClass);
        actionOptions->setObjectName(QStringLiteral("actionOptions"));
        actionQuitter = new QAction(QTCyberSerpentClass);
        actionQuitter->setObjectName(QStringLiteral("actionQuitter"));
        centralWidget = new QWidget(QTCyberSerpentClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(9, 9, 451, 431));
        LayoutOptions = new QGridLayout(gridLayoutWidget);
        LayoutOptions->setSpacing(6);
        LayoutOptions->setContentsMargins(11, 11, 11, 11);
        LayoutOptions->setObjectName(QStringLiteral("LayoutOptions"));
        LayoutOptions->setContentsMargins(0, 0, 0, 0);
        label_CameraPath = new QLabel(gridLayoutWidget);
        label_CameraPath->setObjectName(QStringLiteral("label_CameraPath"));

        LayoutOptions->addWidget(label_CameraPath, 1, 0, 1, 1);

        lineEdit_CameraNum = new QLineEdit(gridLayoutWidget);
        lineEdit_CameraNum->setObjectName(QStringLiteral("lineEdit_CameraNum"));
        lineEdit_CameraNum->setContextMenuPolicy(Qt::PreventContextMenu);

        LayoutOptions->addWidget(lineEdit_CameraNum, 1, 1, 1, 1);

        label_MaxScore = new QLabel(gridLayoutWidget);
        label_MaxScore->setObjectName(QStringLiteral("label_MaxScore"));

        LayoutOptions->addWidget(label_MaxScore, 2, 0, 1, 1);

        label_NbObstacles = new QLabel(gridLayoutWidget);
        label_NbObstacles->setObjectName(QStringLiteral("label_NbObstacles"));

        LayoutOptions->addWidget(label_NbObstacles, 3, 0, 1, 1);

        label_PortConnexion = new QLabel(gridLayoutWidget);
        label_PortConnexion->setObjectName(QStringLiteral("label_PortConnexion"));

        LayoutOptions->addWidget(label_PortConnexion, 0, 0, 1, 1);

        lineEdit_NbObstacles = new QLineEdit(gridLayoutWidget);
        lineEdit_NbObstacles->setObjectName(QStringLiteral("lineEdit_NbObstacles"));

        LayoutOptions->addWidget(lineEdit_NbObstacles, 3, 1, 1, 2);

        lineEdit_MaxScore = new QLineEdit(gridLayoutWidget);
        lineEdit_MaxScore->setObjectName(QStringLiteral("lineEdit_MaxScore"));

        LayoutOptions->addWidget(lineEdit_MaxScore, 2, 1, 1, 2);

        lineEdit_PortConnexion = new QLineEdit(gridLayoutWidget);
        lineEdit_PortConnexion->setObjectName(QStringLiteral("lineEdit_PortConnexion"));

        LayoutOptions->addWidget(lineEdit_PortConnexion, 0, 1, 1, 2);

        pushButton_ValiderInfos = new QPushButton(gridLayoutWidget);
        pushButton_ValiderInfos->setObjectName(QStringLiteral("pushButton_ValiderInfos"));

        LayoutOptions->addWidget(pushButton_ValiderInfos, 4, 1, 1, 1);

        QTCyberSerpentClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QTCyberSerpentClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 784, 21));
        menuMain = new QMenu(menuBar);
        menuMain->setObjectName(QStringLiteral("menuMain"));
        QTCyberSerpentClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(QTCyberSerpentClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QTCyberSerpentClass->setStatusBar(statusBar);

        menuBar->addAction(menuMain->menuAction());
        menuMain->addAction(actionNouvellePartie);
        menuMain->addAction(actionQuitter);

        retranslateUi(QTCyberSerpentClass);

        QMetaObject::connectSlotsByName(QTCyberSerpentClass);
    } // setupUi

    void retranslateUi(QMainWindow *QTCyberSerpentClass)
    {
        QTCyberSerpentClass->setWindowTitle(QApplication::translate("QTCyberSerpentClass", "QTCyberSerpent", 0));
        actionNouvellePartie->setText(QApplication::translate("QTCyberSerpentClass", "Nouvelle partie", 0));
        actionOptions->setText(QApplication::translate("QTCyberSerpentClass", "Options", 0));
        actionQuitter->setText(QApplication::translate("QTCyberSerpentClass", "Quitter", 0));
        label_CameraPath->setText(QApplication::translate("QTCyberSerpentClass", "Numero de la cam\303\251ra", 0));
        label_MaxScore->setText(QApplication::translate("QTCyberSerpentClass", "Score maximal", 0));
        label_NbObstacles->setText(QApplication::translate("QTCyberSerpentClass", "Nombre d'obstacles", 0));
        label_PortConnexion->setText(QApplication::translate("QTCyberSerpentClass", "Port Connexion IRobot", 0));
        pushButton_ValiderInfos->setText(QApplication::translate("QTCyberSerpentClass", "Valider et commencer partie", 0));
        menuMain->setTitle(QApplication::translate("QTCyberSerpentClass", "Jeu", 0));
    } // retranslateUi

};

namespace Ui {
    class QTCyberSerpentClass: public Ui_QTCyberSerpentClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTCYBERSERPENT_H
