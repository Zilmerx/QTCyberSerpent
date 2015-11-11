#include <chrono>
#include <string>
#include <qstring.h>


///////////////// IROBOT ///////////////// 
// D�lai entre chaque envoi de commande.
const std::chrono::milliseconds INTERVAL_IROBOT = std::chrono::milliseconds(1000);
// Pourcentage de tournure du robot, pendant la conduite. Va de -DEGREE_TOURNURE � DEGREE_TOURNURE.
const int IROBOT_DEGREE_TOURNURE = 50;
// Incr�mentation de la tournure du robot � chaque pes�e de touche au clavier.
const int IROBOT_DEGREE_INCREMENTATION = 25;


////////////// VIDEOANALYZER ///////////// 
const double PRECISION_TEMPLATEMATCHING = 0.8;


//////////////////// QT ////////////////// 
const QString QT_DEFAULT_PORTIROBOT = "COM1";
const QString QT_DEFAULT_MAXSCORE = "1000";
const QString QT_DEFAULT_NBOBSTACLE = "1";
const QString QT_DEFAULT_CAMERANUM = "0";