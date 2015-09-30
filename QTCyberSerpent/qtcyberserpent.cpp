#include "qtcyberserpent.h"
#include <string>
#include "CyberSerpent.h"
#include "Utility.h"

QTCyberSerpent::QTCyberSerpent(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    installEventFilter(this); // Active l'événement de lecture de touches.

    m_FuncList = std::map<int, std::function<void()>>();

    m_LabelImage = std::make_unique<QLabel>(this);
    m_LabelImage->setGeometry(QRect(QPoint(100, 100),QSize(200, 50)));
    m_LabelImage->setScaledContents(true);

    QThread *thread = new QThread(this);
    updater = new GUIUpdater();
    updater->moveToThread(thread);
    connect(updater, SIGNAL(requestNewImage(QPixmap)), this, SLOT(UpdateImage(QPixmap)));
    connect(thread, SIGNAL(destroyed()), updater, SLOT(deleteLater()));

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

QPixmap QTCyberSerpent::Mat2QPixmap(const cv::Mat& mat)
{
   return QPixmap::fromImage(Mat2QImage(mat));
}

QImage QTCyberSerpent::Mat2QImage(const cv::Mat& mat)
{
   switch (mat.type())
   {
      // 8-bit, 4 channel
   case CV_8UC4:
   {
      QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB32);

      return image;
   }

      // 8-bit, 3 channel
   case CV_8UC3:
   {
      QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);

      return image.rgbSwapped();
   }

      // 8-bit, 1 channel
   case CV_8UC1:
   {
      static QVector<QRgb>  sColorTable;

      // only create our color table once
      if (sColorTable.isEmpty())
      {
         for (int i = 0; i < 256; ++i)
            sColorTable.push_back(qRgb(i, i, i));
      }

      QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);

      image.setColorTable(sColorTable);

      return image;
   }

   default:
      break;
   }

   return QImage();
}

void QTCyberSerpent::PutImagesFromVideoAnalyzerToQLabel()
{
   cv::Mat img;
   while (true)
   {
      try
      {
         img = m_Game->m_VideoAnalyzer.GetImage();

         updater->newImage(Mat2QPixmap(img));
      }
      catch (...)
      {
      }
   }
}

void QTCyberSerpent::UpdateImage(QPixmap image)
{
   m_LabelImage = std::make_unique<QLabel>(this);
   m_LabelImage->setPixmap(image);
   m_LabelImage->show();
   m_LabelImage->move(QPoint(Utility::RandMinMax(0, 500), Utility::RandMinMax(0, 500)));
}

void QTCyberSerpent::Initialize(CyberSerpent* linked)
{
   m_Game = linked;
   GenerateurEventUpdateVideo = std::thread(&QTCyberSerpent::PutImagesFromVideoAnalyzerToQLabel, this);
}