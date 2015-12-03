#pragma once

#include <chrono>
#include <qstring.h>

#include "opencv2\core.hpp"


////////////////// CORE ////////////////// 
static const bool IS_DEBUG = false;
static const bool BOUGER_ROBOT_AU_DEBUT = true;
static const bool BOXES_DETECTION = true;
static const int IMAGETYPE = CV_32FC1;

///////////////// IROBOT ///////////////// 
// D�lai entre chaque envoi de commande.
static const std::chrono::milliseconds INTERVAL_IROBOT = std::chrono::milliseconds(100);
// Pourcentage de tournure du robot, pendant la conduite. Va de -DEGREE_TOURNURE � DEGREE_TOURNURE.
static const int IROBOT_DEGREE_TOURNURE = 40;
// Incr�mentation de la tournure du robot � chaque pes�e de touche au clavier.
static const int IROBOT_DEGREE_INCREMENTATION = 20;

static const short VITESSE_IROBOT = 350;


////////////// VIDEOANALYZER ///////////// 

static bool TEMPLATEMATCHING_CALIBRE = false;
static double PRECISION_TEMPLATEMATCHING = 1; // Mis a 1 au d�but, puis modifi� avec la calibration


//////////////////// QT ////////////////// 
static const QString QT_DEFAULT_PORTIROBOT = "COM3";
static const QString QT_DEFAULT_MAXSCORE = "30";
static const QString QT_DEFAULT_NBOBSTACLE = "1";
static const QString QT_DEFAULT_CAMERANUM = "0";


static const std::chrono::milliseconds REFRESH_INTERVAL_MESSAGE = std::chrono::milliseconds(200);


//////////////// GAMEPLAY ///////////////
// Le nombre de points qui sont sur le terrain et peuvent �tre mang�s par le robot.
static const int NB_POINTS_SIMULTANEE = 5;
// Le nombre de blocs de la queue que l'on doit sauter, lors du calcul de collision.
static const int NB_QUEUE_NOCOLLISION = 6;
// Le nombre de blocs de la queue que l'on doit sauter avant d'imprimer le prochain.
// Si NB_QUEUE_SAUTE = 5, cela veut dire qu'une image sur 5 sera affich�e.
static const int NB_QUEUE_SAUTE = 80;
// Le nombre de blocs de la queue que l'on doit sauter lors de l'impression (espace entre le bot et la queue).
static const int NB_QUEUEIMPRIM_SAUTE = 3;
// Le nombre de detections hors zone qui doivent �tre fait avant de d�clarer le joueur perdant.
static const int NB_HORSZONE_MAX = 5;

const std::chrono::milliseconds REFRESH_INTERVAL_QUEUE = std::chrono::milliseconds(15);

const cv::Vec3b COULEUR_CONE_MIN = cv::Vec3b{ 0, 5, 108 };
const cv::Vec3b COULEUR_CONE_MAX = cv::Vec3b{ 53, 77, 176 };


//////////////// COLLISION ///////////////
const cv::Vec3b COULEUR_NONPRINT = cv::Vec3b{ 0, 255, 0 };