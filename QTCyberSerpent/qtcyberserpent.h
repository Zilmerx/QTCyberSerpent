#ifndef QTCYBERSERPENT_H
#define QTCYBERSERPENT_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QApplication>
#include <QApplication>
#include <QMessageBox>
#include <QKeyEvent>
#include <qthread.h>
#include <qpixmap.h>
#include <qlistwidget.h>
#include <QApplication>
#include <qlabel.h>

#include <functional>
#include <memory>

#include "GUIUpdater.h"
#include "ui_qtcyberserpent.h"


class CyberSerpent;

typedef std::string Array;

class QTCyberSerpent : public QMainWindow
{
   Q_OBJECT

   friend class VideoAnalyzer;
   friend class CyberSerpent;
   friend class Gameplay;

   Ui::QTCyberSerpentClass ui;
   CyberSerpent* m_Game;

public:

   QTCyberSerpent(QWidget *parent = 0);
   ~QTCyberSerpent();

   void Initialize(CyberSerpent* linked);
   void Delete();

   #pragma region Update de UI
public:
   void UI_PutMessageInList(std::string message);
   void UI_PutImage(QImage image);
   void UI_PutError(std::string message);
   void UI_AfficherOptions();
   void UI_AfficherGameplay();
   void UI_AfficherWin();
   void UI_AfficherLose();

private slots:
   void UI_CB_AddMessageInList();
   void UI_CB_UpdateImage(QImage image);
   void UI_CB_CreateError(QString message);
   void UI_CB_UpdateAfficherOptions();
   void UI_CB_UpdateAfficherGameplay();
   void UI_CB_UpdateAfficherWin();
   void UI_CB_UpdateAfficherLose();

   void bttn_CommencerPartie();
   void bttn_Quitter();
   void bttn_Valider();

private:
   std::unique_ptr<QThread> qthread;
   std::unique_ptr<GUIUpdater> updater;

   std::unique_ptr<QLabel> m_LabelGameplay;

   std::unique_ptr<QListWidget> m_WidgetList;
   #pragma endregion

   #pragma region Detection clavier
private:
   std::map<int, std::function<void()>> m_FuncList;
protected:
    bool eventFilter(QObject* obj, QEvent* event);
public:
    void SetFunc(int key, std::function<void()> func);
    void ClearFunc();
   #pragma endregion
};

#endif // QTCYBERSERPENT_H
