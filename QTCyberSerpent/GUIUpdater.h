#include <chrono>
#include <qobject.h>

// Classe qui s'occupe d'actualiser différentes parties de l'interface
// usager QT en se servant de signaux.
class GUIUpdater : public QObject 
{
   const std::chrono::milliseconds REFRESH_INTERVAL;

   Q_OBJECT

public:
   std::chrono::steady_clock::time_point lastRequest;

   explicit GUIUpdater(const std::chrono::milliseconds refresh_rate, QObject *parent = 0);
   
   void newImage(const QPixmap &image);

   void newError(const std::string message);

private:
signals:
   void requestNewImage(const QPixmap &);
   void requestError(const std::string &);
};