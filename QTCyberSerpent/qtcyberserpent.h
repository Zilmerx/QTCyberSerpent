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

#include "opencv2\core.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"

class QTCyberSerpent : public QMainWindow
{
   Q_OBJECT

   std::map<int, std::function<void()>> m_FuncList;

   std::thread GenerateurEventUpdateVideo;

public:
    QTCyberSerpent(QWidget *parent = 0);
    ~QTCyberSerpent();

    void SetFunc(int key, std::function<void()> func);

    void Error(std::string Message);

    QImage putImage(const cv::Mat& mat);

private:
    Ui::QTCyberSerpentClass ui;

protected:
    bool eventFilter(QObject* obj, QEvent* event);
};

#endif // QTCYBERSERPENT_H
