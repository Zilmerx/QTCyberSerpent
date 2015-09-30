#include "qtcyberserpent.h"
#include <string>

QTCyberSerpent::QTCyberSerpent(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.centralWidget->

    installEventFilter(this); // Active l'événement de lecture de touches.

    m_FuncList = std::map<int, std::function<void()>>();
}

QTCyberSerpent::~QTCyberSerpent()
{

}

bool QTCyberSerpent::eventFilter(QObject* obj, QEvent* event)
{
   if (event->type() == QEvent::KeyPress) 
   {
      QKeyEvent* key = static_cast<QKeyEvent*>(event);

      try
      {
         m_FuncList[key->key()]();
      }
      catch (...)
      {
         return QObject::eventFilter(obj, event);
      }
      return true;
   }
   else 
   {
      return QObject::eventFilter(obj, event);
   }
   return false;
}

void QTCyberSerpent::SetFunc(int key, std::function<void()> func)
{
   m_FuncList.insert(std::pair<int, std::function<void()>>(key, func));
}

void QTCyberSerpent::Error(std::string Message)
{
   QMessageBox b;
   b.setText("HERPDERP");
   b.show();
}

QImage QTCyberSerpent::putImage(const cv::Mat& mat)
{
   // 8-bits unsigned, NO. OF CHANNELS=1
   if (mat.type() == CV_8UC1)
   {
      // Set the color table (used to translate colour indexes to qRgb values)
      QVector<QRgb> colorTable;
      for (int i = 0; i<256; i++)
         colorTable.push_back(qRgb(i, i, i));
      // Copy input Mat
      const uchar *qImageBuffer = (const uchar*)mat.data;
      // Create QImage with same dimensions as input Mat
      QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
      img.setColorTable(colorTable);
   }
   // 8-bits unsigned, NO. OF CHANNELS=3
   if (mat.type() == CV_8UC3)
   {
      // Copy input Mat
      const uchar *qImageBuffer = (const uchar*)mat.data;
      // Create QImage with same dimensions as input Mat
      QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
      ui.Label1->setPixmap(QPixmap::fromImage(img.rgbSwapped()));
      ui.Label1->show();
   }
   else
   {
      return QImage();
   }
}