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


class CyberSerpent;

class QTCyberSerpent : public QMainWindow
{
   Q_OBJECT

   Ui::QTCyberSerpentClass ui;
   CyberSerpent* m_Game;

public:

   QTCyberSerpent(QWidget *parent = 0);
   ~QTCyberSerpent();

   void Initialize(CyberSerpent* linked);
   void Stop();

   #pragma region Update de UI
public:
   void PutImage(QPixmap image);
   void PutError(const std::string message);

private slots:
   void UpdateImage(QPixmap image);
   void CreateError(const std::string message);

private:
   std::unique_ptr<QThread> qthread;
   std::unique_ptr<GUIUpdater> updater;

   std::unique_ptr<QLabel> m_LabelImage;
   #pragma endregion

   #pragma region Detection clavier
private:
   std::map<int, std::function<void()>> m_FuncList;
protected:
    bool eventFilter(QObject* obj, QEvent* event);
public:
    void SetFunc(int key, std::function<void()> func);
   #pragma endregion
};

#endif // QTCYBERSERPENT_H
