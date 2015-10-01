#ifndef QTCYBERSERPENT_H
#define QTCYBERSERPENT_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QApplication>
#include <QMessageBox>
#include <map>
#include <functional>
#include "ui_qtcyberserpent.h"
#include <QKeyEvent>
#include <thread>
#include <qpixmap.h>
#include <QApplication>
#include <qlabel.h>
#include "GUIUpdater.h"
#include <memory>

#include "opencv2\core.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"

class CyberSerpent;

class QTCyberSerpent : public QMainWindow
{
   Q_OBJECT

   CyberSerpent* m_Game;

   std::unique_ptr<QThread> qthread;
   std::unique_ptr<GUIUpdater> updater;

   std::map<int, std::function<void()>> m_FuncList;

private slots:
   void UpdateImage(QPixmap image);

private :
   std::unique_ptr<QLabel> m_LabelImage;

public:

   void Initialize(CyberSerpent* linked);

   void Stop();

   void PutImage(QPixmap image);

    QTCyberSerpent(QWidget *parent = 0);
    ~QTCyberSerpent();

    void SetFunc(int key, std::function<void()> func);

    void Error(std::string Message);

private:
    Ui::QTCyberSerpentClass ui;

protected:
    bool eventFilter(QObject* obj, QEvent* event);
};

#endif // QTCYBERSERPENT_H
