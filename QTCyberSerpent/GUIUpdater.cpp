#include "GUIUpdater.h"



GUIUpdater::GUIUpdater(QObject *parent) 
: QObject(parent)
{
}

void GUIUpdater::newImage(const QImage &image)
{
   emit requestNewImage(image);
}

void GUIUpdater::newError(const QString message)
{
   emit requestError(message);
}

void GUIUpdater::newMessageInList(const QString message)
{
   {
      std::lock_guard<std::mutex> lock(m_Vector.m_Mutex);
      m_Vector.m_Vector.push_back(message);
      if ((std::chrono::steady_clock::now() - lastRequestMessage) >= REFRESH_INTERVAL_MESSAGE)
      {
         lastRequestMessage = std::chrono::steady_clock::now();
         emit requestListMessage();
      }
   }
}

void GUIUpdater::afficherOptions()
{
   emit requestAfficherOptions();
}

void GUIUpdater::afficherGameplay()
{
   emit requestAfficherGameplay();
}

void GUIUpdater::afficherWin()
{
   emit requestAfficherWin();
}

void GUIUpdater::afficherLose()
{
   emit requestAfficherLose();
}