#include "GUIUpdater.h"



GUIUpdater::GUIUpdater(const std::chrono::milliseconds refresh_rate, QObject *parent) 
: QObject(parent), 
  REFRESH_INTERVAL{ refresh_rate }
{
   lastRequest = std::chrono::steady_clock::now();
}

void GUIUpdater::newImage(const QImage &image)
{
   if ((std::chrono::steady_clock::now() - lastRequest) >= REFRESH_INTERVAL)
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
   emit requestListMessage(message);
}

void GUIUpdater::afficherOptions()
{
   emit requestAfficherOptions();
}

void GUIUpdater::afficherGameplay()
{
   emit requestAfficherGameplay();
}