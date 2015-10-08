#pragma once

#include <iostream>
#include <windows.h>

namespace IRobot
{

	enum DirectionY
	{
		HAUT,
		BAS,
	};

	enum DirectionX
	{
		GAUCHE,
		AVANT_GAUCHE,
		AVANT_DROITE,
		DROITE
	};

	enum CodeSensor
	{
		BUMPER,
		WHEEL,
		CLIFF,
		CLIFF_SIGNAL,
		WALL,
		WALL_SIGNAL,
		VIRTUAL_WALL,
		BATTERY_CHARGE,
		BATTERY_CAPACITY,
		DISTANCE,
		ANGLE
	};

	enum SuivreLigneState
	{
		TROP_A_DROITE,
		TROP_A_GAUCHE,
		INTERSECTION,
		CENTRE
	};


	class IRobot
	{

	public:

	   // Fonctions de mouvement du robot.
	   void Avant( short Vitesse ) const;
	   void Arriere( short Vitesse ) const;
	   void Stop () const;
	   // Tourner sur place.
	   void HDroite( short Vitesse ) const;
	   void HGauche( short Vitesse ) const;
	   // Tourner avec un pourcentage de vitesse de moins sur une route.
	   void Droite( short Vitesse, char TournurePourcentage ) const;
	   void Gauche( short Vitesse, char TournurePourcentage ) const;
	   // Tourner sur place jusqu'à ce que l'on aie atteint l'angle.
	   void ADroite ( short Vitesse, char Angle) const;
	   void AGauche ( short Vitesse, char Angle) const;




	   // Fonction SuivreLigne, permet de suivre une ligne sur le sol à la vitesse entrée en paramètre.
	   char SuivreLigne( int Vitesse, int Luminosite_Plancher, int Luminosite_Bande) const;


	   // Fonction pour conduire un peu plus complexe. 
	   void Drive( short VitesseGauche, short VitesseDroite) const;


	   // Fonction qui permet de lire les valeurs de retour des sensors. 
	   int Sensor(CodeSensor sensor) const;
	   int Sensor(CodeSensor sensor, DirectionX precision) const;

	   // Fonction qui fait 5 verification de la valeur des sensors et retourne la moyenne.
	   int S_Sensor(CodeSensor sensor) const;
	   int S_Sensor(CodeSensor sensor, DirectionX precision) const;

	   // Fonction qui fait jouer une musique.
	   void Music(int Numero) const;

	   // Permet de connecter déconnecter. True = Connection reussie.
	   bool Initialize();
	   void Deconnecter() const;

	   // Constructeur --- Destructeur.
	   IRobot();
	   ~IRobot();

	private:

	   // Membres.
	   HANDLE PortSerie;
	   const int m_Temps_Ecriture;
	   const int m_Temps_Lecture;


	   // Fonction de démarrage - Throws runtime_error
	   void SetConnection();
	   // Sette les paramètres de communication. - Throws runtime_error
	   void ComSetup(HANDLE PortSerie, int BaudRate, short ByteSize, short Parity, short StopBits) const;
	   // Sette les paramètres pour le timeout de la communication. - Throws runtime_error
	   void ComTimeoutSetup( int IT, int RTTM, int RTTC, int WTTM, int WTTC) const;
	   // Envoie un message de salutation sonore.
	   void Bonjour() const;
	   // Permet de mettre des musiques dans le robot.
	   /*
	   1. Charge.
	   2. Erreur.
	   3. Song of storm.
	   */
	   void SetMusique() const;
	   // Enleve les messages à l'allumage du robot.
	   void Flush(int Quantité) const;

	   // Fonction d'écriture, permet d'envoyer le nombre de valeurs voulues au robot.
	   void Send(char arg1, ...) const;

	   // Fonction de lecture, permet d'envoyer des valeurs au robot et de lire le message de retour.
	   int Read(bool HighByte, char arg1, ...) const;

	   // Envoi de message d'erreur à l'utilisateur.
	   void Erreur(std::ostream& stream, std::string message, bool SendException) const;

	   // Transformation d'un short en un char, en choisissant si on veut le quartet HAUT ou BAS.
	   char ShortToChar(short Valeur, int PositionQuartet) const;
	};

}

