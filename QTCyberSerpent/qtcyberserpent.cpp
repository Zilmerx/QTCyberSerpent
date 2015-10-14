#include "qtcyberserpent.h"
#include <string>
#include "CyberSerpent.h"
#include "Utility.h"
#include <qlist.h>

QTCyberSerpent::QTCyberSerpent(QWidget *parent)
   : QMainWindow(parent)
{
    ui.setupUi(this);

    installEventFilter(this); // Active l'événement de lecture de touches.

    m_FuncList = std::map<int, std::function<void()>>();

    this->setFixedSize(700, 522);

    m_LabelImage = std::make_unique<QLabel>(this);
    m_LabelImage->setGeometry(QRect(QPoint(0, 22), QSize(500, 500)));
    m_LabelImage->setScaledContents(true);

    m_WidgetList = std::make_unique<QListWidget>(this);
    m_WidgetList->setGeometry(QRect(QPoint(500, 22), QSize(200, 500)));

    qthread = std::make_unique<QThread>(this);
    updater = std::make_unique<GUIUpdater>(m_Game->REFRESH_RATE);
    updater->moveToThread(qthread.get());
    connect(updater.get(), SIGNAL(requestNewImage(QImage)), this, SLOT(UpdateImage(QImage)));
    connect(updater.get(), SIGNAL(requestError(std::string)), this, SLOT(CreateError(std::string)));
    connect(updater.get(), SIGNAL(requestListMessage(std::string)), this, SLOT(AddMessageInList(std::string)));
    connect(qthread.get(), SIGNAL(destroyed()), updater.get(), SLOT(deleteLater()));
}

QTCyberSerpent::~QTCyberSerpent()
{
}

void QTCyberSerpent::Initialize(CyberSerpent* linked)
{
   m_Game = linked;
}

void QTCyberSerpent::Stop()
{
   disconnect(updater.get(), SIGNAL(requestNewImage(QImage)), this, SLOT(UpdateImage(QImage)));
   disconnect(updater.get(), SIGNAL(requestError(std::string)), this, SLOT(CreateError(std::string)));
   disconnect(updater.get(), SIGNAL(requestListMessage(std::string)), this, SLOT(AddMessageInList(std::string)));

   m_Game->m_QTApplication.processEvents();

   qthread->terminate();
   while (qthread->isRunning());
}

#pragma region Update de UI
void QTCyberSerpent::PutImage(QImage image)
{
   updater->newImage(image);
}

void QTCyberSerpent::PutError(const std::string message)
{
   updater->newError(message);
}

void QTCyberSerpent::PutMessageInList(const std::string message)
{
   updater->newMessageInList(message);
}

void QTCyberSerpent::UpdateImage(QImage image)
{
   m_LabelImage->setPixmap(QPixmap::fromImage(image));
   m_LabelImage->show();
}

void QTCyberSerpent::CreateError(const std::string message)
{
   QMessageBox b;
   b.setText(QString::fromStdString(message));
   b.exec();
}

void QTCyberSerpent::AddMessageInList(const std::string message)
{
   QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(message));
   item->setFlags(Qt::ItemIsEnabled);
   m_WidgetList->addItem(item);
   m_WidgetList->scrollToBottom();
   m_WidgetList->show();
   this->setFocus(); // Empêche le bug ou le focus se met sur la liste, et bloque Up et Down arrow.
}
#pragma endregion

#pragma region Detection clavier
bool QTCyberSerpent::eventFilter(QObject* obj, QEvent* event)
{
   if (event->type() == QEvent::KeyPress)
   {
      QKeyEvent* key = static_cast<QKeyEvent*>(event);

      try
      {
         m_FuncList[key->key()]();
         return true;
      }
      catch (...)
      {
         return QObject::eventFilter(obj, event);
      }
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
#pragma endregion