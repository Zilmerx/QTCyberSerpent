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

   GUIUpdater *updater;

   std::map<int, std::function<void()>> m_FuncList;

private:
   std::thread GenerateurEventUpdateVideo;
   void PutImagesFromVideoAnalyzerToQLabel();
private slots:
   void UpdateImage(QPixmap image);

private :
   std::unique_ptr<QLabel> m_LabelImage;

public:

   void Initialize(CyberSerpent* linked);

    QTCyberSerpent(QWidget *parent = 0);
    ~QTCyberSerpent();

    void SetFunc(int key, std::function<void()> func);

    void Error(std::string Message);

    static QImage Mat2QImage(const cv::Mat &mat);
    static QPixmap Mat2QPixmap(const cv::Mat& mat);

private:
    Ui::QTCyberSerpentClass ui;

protected:
    bool eventFilter(QObject* obj, QEvent* event);
};

#endif // QTCYBERSERPENT_H
