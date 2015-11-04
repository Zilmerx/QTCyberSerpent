#include "GUIUpdater.h"



GUIUpdater::GUIUpdater(const std::chrono::milliseconds refresh_rate, QObject *parent) 
: QObject(parent), 
  REFRESH_INTERVAL_IMAGE{ refresh_rate }
{
   lastRequest = std::chrono::steady_clock::now();
}

void GUIUpdater::newImage(const QImage &image)
{
   if ((std::chrono::steady_clock::now() - lastRequest) >= REFRESH_INTERVAL_IMAGE)
   {
      lastRequest = std::chrono::steady_clock::now();
      emit requestNewImage(image);
   }
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