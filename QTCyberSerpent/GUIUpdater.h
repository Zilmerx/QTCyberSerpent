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
   
   void newImage(const QImage &image);

   void newError(const std::string message);

   void newMessageInList(const std::string message);

   void afficherOptions();

   void afficherGameplay();

private:
signals:
   void requestNewImage(const QImage &);
   void requestError(const std::string &);
   void requestListMessage(const std::string &);
   void requestAfficherOptions();
   void requestAfficherGameplay();
};