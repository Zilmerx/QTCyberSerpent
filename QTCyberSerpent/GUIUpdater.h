#include <qthread.h>
#include <chrono>
#include <qobject.h>

class GUIUpdater : public QObject 
{
   static const int INTERVAL = 500; // ms

   Q_OBJECT

public:
   std::chrono::steady_clock::time_point lastRequest;

   explicit GUIUpdater(QObject *parent = 0) : QObject(parent) 
   {
      lastRequest = std::chrono::steady_clock::now();
   }
   void newImage(const QPixmap &image) 
   { 
      if ((std::chrono::steady_clock::now() - lastRequest) >= std::chrono::milliseconds(500))
      {
         lastRequest = std::chrono::steady_clock::now();
         requestNewImage(image);
      }
   }
private:
signals:
   void requestNewImage(const QPixmap &);
};