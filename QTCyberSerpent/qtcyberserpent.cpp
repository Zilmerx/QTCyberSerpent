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

void QTCyberSerpent::PutImage(QPixmap image)
{
   updater->newImage(image);
}

void QTCyberSerpent::PutError(const std::string message)
{
   updater->newError(message);
}


void QTCyberSerpent::UpdateImage(QPixmap image)
{
   std::unique_ptr<QLabel> temp = std::make_unique<QLabel>(this);
   temp->setPixmap(image);
   temp->setGeometry(QRect(QPoint(Utility::RandMinMax(0, 500), Utility::RandMinMax(0, 500)), QSize(image.width(), image.height())));

   m_LabelImage.swap(temp);
   m_LabelImage->show();
}

void QTCyberSerpent::CreateError(const std::string message)
{
   QMessageBox b;
   b.setText(QString::fromStdString(message));
   b.show();
   std::this_thread::sleep_for(std::chrono::seconds(1));
}

void QTCyberSerpent::Initialize(CyberSerpent* linked)
{
   m_Game = linked;

   qthread = std::make_unique<QThread>(this);
   updater = std::make_unique<GUIUpdater>(m_Game->REFRESH_RATE);
   updater->moveToThread(qthread.get());
   connect(updater.get(), SIGNAL(requestNewImage(QPixmap)), this, SLOT(UpdateImage(QPixmap)));
   connect(updater.get(), SIGNAL(requestError(std::string)), this, SLOT(CreateError(std::string)));
   connect(qthread.get(), SIGNAL(destroyed()), updater.get(), SLOT(deleteLater()));
}

void QTCyberSerpent::Stop()
{
   disconnect(updater.get(), SIGNAL(requestNewImage(QPixmap)), this, SLOT(UpdateImage(QPixmap)));
   disconnect(updater.get(), SIGNAL(requestError(std::string)), this, SLOT(CreateError(std::string)));

   m_Game->m_QTApplication.processEvents();

   qthread->terminate();
   while (qthread->isRunning());
}