#include <chrono>
#include <qobject.h>
#include <string>
#include "MutexedVector.h"

typedef std::string Array;

// Classe qui s'occupe d'actualiser différentes parties de l'interface
// usager QT en se servant de signaux.
class GUIUpdater : public QObject 
{
   const std::chrono::milliseconds REFRESH_INTERVAL_IMAGE;

   Q_OBJECT

public:
   std::chrono::steady_clock::time_point lastRequest;

   explicit GUIUpdater(const std::chrono::milliseconds refresh_rate, QObject *parent = 0);
   
   void newImage(const QImage &image);

   void newError(const QString message);

   const std::chrono::milliseconds REFRESH_INTERVAL_MESSAGE = std::chrono::milliseconds(100);
   std::chrono::steady_clock::time_point lastRequestMessage;
   MutexedVector<QString> m_Vector;
   void newMessageInList(const QString message);

   void afficherOptions();

   void afficherGameplay();

private:
signals:
   void requestNewImage(const QImage &);
   void requestError(const QString &);
   void requestListMessage();
   void requestAfficherOptions();
   void requestAfficherGameplay();
};