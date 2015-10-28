#include <chrono>
#include <qobject.h>
#include <string>

typedef std::string Array;

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

   void newError(const QString message);

   void newMessageInList(const QString message);

   void afficherOptions();

   void afficherGameplay();

private:
signals:
   void requestNewImage(const QImage &);
   void requestError(const QString &);
   void requestListMessage(const QString &);
   void requestAfficherOptions();
   void requestAfficherGameplay();
};