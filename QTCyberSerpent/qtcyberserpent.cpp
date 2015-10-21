#include "qtcyberserpent.h"
#include <string>
#include "CyberSerpent.h"
#include "Utility.h"
#include <qlist.h>
#include <qfiledialog.h>
#include <qgridlayout.h>

QTCyberSerpent::QTCyberSerpent(QWidget *parent)
   : QMainWindow(parent)
{
    ui.setupUi(this);

    installEventFilter(this); // Active l'événement de lecture de touches.

    m_FuncList = std::map<int, std::function<void()>>();

    this->setFixedSize(700, 522);

    ui.gridLayoutWidget->setGeometry(QRect(50, 62, 400, 400));
    ui.lineEdit_MaxScore->setValidator(new QIntValidator(0, 1000, this));
    ui.lineEdit_NbObstacles->setValidator(new QIntValidator(0, 3, this));
    ui.lineEdit_CameraPath->setReadOnly(true);

    ui.lineEdit_PortConnexion->setText(QString::fromStdString("COM1"));
    ui.lineEdit_NbObstacles->setText(QString::fromStdString("1"));
    ui.lineEdit_MaxScore->setText(QString::fromStdString("1000"));
    ui.lineEdit_CameraPath->setText(QString::fromStdString("image.bmp"));

    m_LabelGameplay = std::make_unique<QLabel>(this);
    m_LabelGameplay->setGeometry(QRect(0, 22, 500, 500));
    m_LabelGameplay->setScaledContents(true);

    m_WidgetList = std::make_unique<QListWidget>(this);
    m_WidgetList->setGeometry(QRect(500, 22, 200, 500));

    UI_CB_UpdateAfficherOptions();
}

QTCyberSerpent::~QTCyberSerpent()
{
}

void QTCyberSerpent::Initialize(CyberSerpent* linked)
{
   m_Game = linked;

   qthread = std::make_unique<QThread>(this);
   updater = std::make_unique<GUIUpdater>(m_Game->REFRESH_RATE);
   updater->moveToThread(qthread.get());
   connect(updater.get(), SIGNAL(requestNewImage(QImage)), this, SLOT(UI_CB_UpdateImage(QImage)));
   connect(updater.get(), SIGNAL(requestError(std::string)), this, SLOT(UI_CB_CreateError(std::string)));
   connect(updater.get(), SIGNAL(requestListMessage(std::string)), this, SLOT(UI_CB_AddMessageInList(std::string)));
   connect(updater.get(), SIGNAL(requestAfficherOptions()), this, SLOT(UI_CB_UpdateAfficherOptions()));
   connect(updater.get(), SIGNAL(requestAfficherGameplay()), this, SLOT(UI_CB_UpdateAfficherGameplay()));

   connect(ui.actionNouvellePartie, SIGNAL(triggered()), this, SLOT(bttn_CommencerPartie()));
   connect(ui.actionQuitter, SIGNAL(triggered()), this, SLOT(bttn_Quitter()));
   connect(ui.pushButton_FileFinder, SIGNAL(released()), this, SLOT(bttn_FileFinder()));
   connect(ui.pushButton_ValiderInfos, SIGNAL(released()), this, SLOT(bttn_Valider()));

   connect(qthread.get(), SIGNAL(destroyed()), updater.get(), SLOT(deleteLater()));
}

void QTCyberSerpent::Delete()
{
   disconnect(updater.get(), SIGNAL(requestNewImage(QImage)), this, SLOT(UI_CB_UpdateImage(QImage)));
   disconnect(updater.get(), SIGNAL(requestError(std::string)), this, SLOT(UI_CB_CreateError(std::string)));
   disconnect(updater.get(), SIGNAL(requestListMessage(std::string)), this, SLOT(UI_CB_AddMessageInList(std::string)));
   disconnect(updater.get(), SIGNAL(requestAfficherOptions()), this, SLOT(UI_CB_UpdateAfficherOptions()));
   disconnect(updater.get(), SIGNAL(requestAfficherGameplay()), this, SLOT(UI_CB_UpdateAfficherGameplay()));

   disconnect(ui.actionNouvellePartie, SIGNAL(triggered()), this, SLOT(bttn_CommencerPartie()));
   disconnect(ui.actionQuitter, SIGNAL(triggered()), this, SLOT(bttn_Quitter()));
   disconnect(ui.pushButton_FileFinder, SIGNAL(triggered()), this, SLOT(bttn_FileFinder()));
   disconnect(ui.pushButton_ValiderInfos, SIGNAL(triggered()), this, SLOT(bttn_Valider()));

   m_Game->m_QTApplication.processEvents();

   qthread->terminate();
   while (qthread->isRunning());
}

#pragma region Boutons
void QTCyberSerpent::bttn_CommencerPartie()
{
   m_Game->Stop();
   updater->afficherOptions();
}

void QTCyberSerpent::bttn_Quitter()
{
   m_Game->m_QTApplication.quit();
}

void QTCyberSerpent::bttn_FileFinder()
{
   ui.lineEdit_CameraPath->setText(QFileDialog::getOpenFileName(this, tr("Trouver le chemin"), "./", "All files (*.*);;"));
}

void QTCyberSerpent::bttn_Valider()
{
   m_Game->Start();
   updater->afficherGameplay();
}
#pragma endregion

#pragma region Update de UI
void QTCyberSerpent::UI_PutImage(QImage image)
{
   updater->newImage(image);
}

void QTCyberSerpent::UI_PutError(const std::string message)
{
   updater->newError(message);
}

void QTCyberSerpent::UI_PutMessageInList(const std::string message)
{
   updater->newMessageInList(message);
}

void QTCyberSerpent::UI_AfficherOptions()
{
   updater->afficherOptions();
}
void QTCyberSerpent::UI_AfficherGameplay()
{
   updater->afficherGameplay();
}
#pragma endregion

#pragma region UI_CallBack
void QTCyberSerpent::UI_CB_UpdateImage(QImage image)
{
   m_LabelGameplay->setPixmap(QPixmap::fromImage(image));
}

void QTCyberSerpent::UI_CB_CreateError(const std::string message)
{
   QMessageBox b;
   b.setText(QString::fromStdString(message));
   b.exec();
}

void QTCyberSerpent::UI_CB_UpdateAfficherOptions()
{
   m_LabelGameplay->hide();
   ui.gridLayoutWidget->show();
   m_WidgetList->clear();
}

void QTCyberSerpent::UI_CB_UpdateAfficherGameplay()
{
   ui.gridLayoutWidget->hide();
   m_LabelGameplay->setPixmap(QPixmap::QPixmap());
   m_LabelGameplay->show();
   m_WidgetList->setFocus();
}

void QTCyberSerpent::UI_CB_AddMessageInList(const std::string message)
{
   QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(message));
   item->setFlags(Qt::ItemIsEnabled);
   m_WidgetList->addItem(item);
   m_WidgetList->scrollToBottom();
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

void QTCyberSerpent::ClearFunc()
{
   m_FuncList.clear();
}
#pragma endregion