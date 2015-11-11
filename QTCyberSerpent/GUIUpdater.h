#include <chrono>
#include <qobject.h>
#include <string>
#include "MutexedVector.h"

typedef std::string Array;

// Classe qui s'occupe d'actualiser différentes parties de l'interface
// usager QT en se servant de signaux.
class GUIUpdater : public QObject 
{
   Q_OBJECT

public:
   explicit GUIUpdater(QObject *parent = 0);
   
   void newImage(const QImage &image);

   void newError(const QString message);

   const std::chrono::milliseconds REFRESH_INTERVAL_MESSAGE = std::chrono::milliseconds(30);
   std::chrono::steady_clock::time_point lastRequestMessage;
   MutexedVector<QString> m_Vector;
   void newMessageInList(const QString message);

   void afficherOptions();

   void afficherGameplay();

   void afficherWin();

   void afficherLose();

private:
signals:
   void requestNewImage(const QImage &);
   void requestError(const QString &);
   void requestListMessage();
   void requestAfficherOptions();
   void requestAfficherGameplay();
   void requestAfficherWin();
   void requestAfficherLose();
};