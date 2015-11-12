#include <qobject.h>
#include <string>
#include <mutex>

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

   std::chrono::steady_clock::time_point lastRequestMessage;
   std::recursive_mutex m_MutexMessage;
   std::vector<QString> m_Vector;
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