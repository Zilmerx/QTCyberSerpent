#pragma once

#include <chrono>
#include <qstring.h>

#include "opencv2\core.hpp"


////////////////// CORE ////////////////// 
const bool IS_DEBUG = true;

///////////////// IROBOT ///////////////// 
// Délai entre chaque envoi de commande.
const std::chrono::milliseconds INTERVAL_IROBOT = std::chrono::milliseconds(100);
// Pourcentage de tournure du robot, pendant la conduite. Va de -DEGREE_TOURNURE à DEGREE_TOURNURE.
const int IROBOT_DEGREE_TOURNURE = 60;
// Incrémentation de la tournure du robot à chaque pesée de touche au clavier.
const int IROBOT_DEGREE_INCREMENTATION = 25;

const short VITESSE_IROBOT = 350;


////////////// VIDEOANALYZER ///////////// 

static bool TEMPLATEMATCHING_CALIBRE = false;
static double PRECISION_TEMPLATEMATCHING = 1; // Mis a 1 au début, puis modifié avec la calibration


//////////////////// QT ////////////////// 
const QString QT_DEFAULT_PORTIROBOT = "COM3";
const QString QT_DEFAULT_MAXSCORE = "30";
const QString QT_DEFAULT_NBOBSTACLE = "1";
const QString QT_DEFAULT_CAMERANUM = "0";


const std::chrono::milliseconds REFRESH_INTERVAL_MESSAGE = std::chrono::milliseconds(200);


//////////////// GAMEPLAY ///////////////
// Le nombre de points qui sont sur le terrain et peuvent être mangés par le robot.
const int NB_POINTS_SIMULTANEE = 5;
// Le nombre de blocs de la queue que l'on doit sauter, lors du calcul de collision.
const int NB_QUEUE_NOCOLLISION = 6;
// Le nombre de blocs de la queue que l'on doit sauter avant d'imprimer le prochain.
// Si NB_QUEUE_SAUTE = 5, cela veut dire qu'une image sur 5 sera affichée.
const int NB_QUEUE_SAUTE = 80;
// Le nombre de blocs de la queue que l'on doit sauter lors de l'impression (espace entre le bot et la queue).
const int NB_QUEUEIMPRIM_SAUTE = 3;
// Le nombre de detections hors zone qui doivent être fait avant de déclarer le joueur perdant.
const int NB_HORSZONE_MAX = 5;

const std::chrono::milliseconds REFRESH_INTERVAL_QUEUE = std::chrono::milliseconds(15);

const cv::Vec3b COULEUR_CONE_MIN = cv::Vec3b{ 0, 115, 235 };
const cv::Vec3b COULEUR_CONE_MAX = cv::Vec3b{ 0, 135, 255 };


//////////////// COLLISION ///////////////
const cv::Vec3b COULEUR_NONPRINT = cv::Vec3b{ 0, 255, 0 };