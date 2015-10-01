#include <qthread.h>
#include <chrono>
#include <qobject.h>

class GUIUpdater : public QObject 
{
   const std::chrono::milliseconds REFRESH_INTERVAL;

   Q_OBJECT

public:
   std::chrono::steady_clock::time_point lastRequest;

   explicit GUIUpdater(const std::chrono::milliseconds refresh_rate, QObject *parent = 0) : QObject(parent), REFRESH_INTERVAL{ refresh_rate }
   {
      lastRequest = std::chrono::steady_clock::now();
   }
   void newImage(const QPixmap &image)
   { 
      if ((std::chrono::steady_clock::now() - lastRequest) >= REFRESH_INTERVAL)
      {
         lastRequest = std::chrono::steady_clock::now();
         emit requestNewImage(image);
      }
   }

private:
signals:
   void requestNewImage(const QPixmap &);
};