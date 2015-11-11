#include <chrono>
#include <string>
#include <qstring.h>


////////////////// CORE ////////////////// 
const bool IS_DEBUG = true;

///////////////// IROBOT ///////////////// 
// D�lai entre chaque envoi de commande.
const std::chrono::milliseconds INTERVAL_IROBOT = std::chrono::milliseconds(200);
// Pourcentage de tournure du robot, pendant la conduite. Va de -DEGREE_TOURNURE � DEGREE_TOURNURE.
const int IROBOT_DEGREE_TOURNURE = 75;
// Incr�mentation de la tournure du robot � chaque pes�e de touche au clavier.
const int IROBOT_DEGREE_INCREMENTATION = 25;

const short VITESSE_IROBOT = 350;


////////////// VIDEOANALYZER ///////////// 
const double PRECISION_TEMPLATEMATCHING = 0.8;


//////////////////// QT ////////////////// 
const QString QT_DEFAULT_PORTIROBOT = "COM3";
const QString QT_DEFAULT_MAXSCORE = "1000";
const QString QT_DEFAULT_NBOBSTACLE = "1";
const QString QT_DEFAULT_CAMERANUM = "0";



//////////////// GAMEPLAY ///////////////
const int NB_POINTS_SIMULTANEE = 5;
// Le nombre de blocs de la queue que l'on doit sauter, lors du calcul de collision.
const int NB_QUEUE_NOCOLLISION = 4;
// Le nombre de blocs de la queue que l'on doit sauter avant d'imprimer le prochain.
// Si NB_QUEUE_SAUTE = 5, cela veut dire qu'une image sur 5 sera affich�e.
const int NB_QUEUE_SAUTE = 5;
// Le nombre de blocs de la queue que l'on doit sauter lors de l'impression.
const int NB_QUEUEIMPRIM_SAUTE = 3;
// Le nombre de points de la queue retenus en m�moire, au maximum.
const int NB_QUEUE_INVIS_MAX = 500;
