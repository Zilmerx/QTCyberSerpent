#ifndef QTCYBERSERPENT_H
#define QTCYBERSERPENT_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QApplication>
#include <QMessageBox>
#include <map>
#include <functional>
#include "ui_qtcyberserpent.h"
#include <QKeyEvent>
#include <qthread.h>
#include <qpixmap.h>
#include <QApplication>
#include <qlabel.h>
#include "GUIUpdater.h"
#include <memory>
#include <qlistwidget.h>


class CyberSerpent;

class QTCyberSerpent : public QMainWindow
{
   Q_OBJECT

   friend class CyberSerpent;

   Ui::QTCyberSerpentClass ui;
   CyberSerpent* m_Game;

public:

   QTCyberSerpent(QWidget *parent = 0);
   ~QTCyberSerpent();

   void Initialize(CyberSerpent* linked);
   void Delete();

   #pragma region Update de UI
public:
   void UI_PutMessageInList(const std::string message);
   void UI_PutImage(QImage image);
   void UI_PutError(const std::string message);
   void UI_AfficherOptions();
   void UI_AfficherGameplay();

private slots:
   void UI_CB_AddMessageInList(const std::string message);
   void UI_CB_UpdateImage(QImage image);
   void UI_CB_CreateError(const std::string message);
   void UI_CB_UpdateAfficherOptions();
   void UI_CB_UpdateAfficherGameplay();

   void bttn_CommencerPartie();
   void bttn_Quitter();
   void bttn_FileFinder();
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
