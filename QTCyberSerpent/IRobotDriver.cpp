#include "IRobotDriver.h"
#include <stdarg.h>
#include <exception>
#include <string>

namespace IRobot
{
//________________________________________________________________________________________________________________________________________________________________
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                               // -- FONCTIONS PUBLIQUES -- //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//����������������������������������������������������������������������������������������������������������������������������������������������������������������


/////////////////////////////////////            DRIVE               //////////////////////////////////////////
//�������������������������������������������������������������������������������������������������������������
// Fonctions d�riv�es de Drive, pour conduire le robot.
void IRobot::Avant( short Vitesse ) const
{
   if (Vitesse <= 500 && Vitesse >= 0)
   {
      Drive(Vitesse,Vitesse);
   }
   else
   {
      Erreur(std::cout, "Une valeur de vitesse n'est pas correcte. (Avant)", false);
   }
}
void IRobot::Arriere( short Vitesse ) const
{
   if (Vitesse <= 500 && Vitesse >= 0)
   {
      Drive(-Vitesse,-Vitesse);
   }
   else
   {
      Erreur(std::cout, "Une valeur de vitesse n'est pas correcte. (Arriere)", false);
   }
}
void IRobot::Stop() const
{
   Drive(0,0);
}
// Tourner sur place.
void IRobot::HDroite ( short Vitesse ) const
{
   if (Vitesse <= 500 && Vitesse >= 0)
   {
      Drive(Vitesse,-Vitesse);
   }
   else
   {
      Erreur(std::cout, "Une valeur de vitesse n'est pas correcte. (HDroite)", false);
   }
}
void IRobot::HGauche ( short Vitesse ) const
{
   if (Vitesse <= 500 && Vitesse >= 0)
   {
      Drive(-Vitesse,Vitesse);
   }
   else
   {
      Erreur(std::cout, "Une valeur de vitesse n'est pas correcte. (HGauche)", false);
   }
}
// Tourner avec un pourcentage de vitesse sur une roue.
void IRobot::Droite ( short Vitesse, char TournurePourcentage ) const
{
   if (Vitesse <= 500 && Vitesse >= -500 && TournurePourcentage <= 100 && TournurePourcentage >= 0)
   {
      short VitesseReduite = Vitesse * TournurePourcentage / 100;

      Drive(Vitesse,VitesseReduite);
   }
   else
   {
      Erreur(std::cout, "Une valeur de vitesse n'est pas correcte, ou le % de tournure n'est pas entre 0 ou 100. (Droite)", false);
   }
}
void IRobot::Gauche ( short Vitesse, char TournurePourcentage ) const
{
   if (Vitesse <= 500 && Vitesse >= -500 && TournurePourcentage <= 100 && TournurePourcentage >= 0)
   {
      short VitesseReduite = Vitesse * TournurePourcentage / 100;

      Drive(VitesseReduite,Vitesse);
   }
   else
   {
      Erreur(std::cout, "Une valeur de vitesse n'est pas correcte, ou le % de tournure n'est pas entre 0 ou 100. (Gauche)", false);
   }
}
// Tourner sur place jusqu'� un angle.
void IRobot::ADroite ( short Vitesse, char Angle) const
{
   std::cout << "Herp";
   if (Vitesse >= 0 && Vitesse <= 500 && Angle <= 180 && Angle >= 0)
   {
      Sensor(ANGLE); // Reset de la valeur Angle � 0..

      int ValeurAngle = 0;

      while (ValeurAngle >= -Angle)
      {
         HDroite(Vitesse);
		 std::cout << ValeurAngle << Angle;
         ValeurAngle += Sensor(ANGLE);
      }
      Stop();
   }
}
void IRobot::AGauche ( short Vitesse, char Angle) const
{
	std::cout << "Derp";
   if (Vitesse >= 0 && Vitesse <= 500 && Angle <= 180 && Angle >= 0)
   {
      Sensor(ANGLE); // Reset de la valeur Angle � 0..

      int ValeurAngle = 0;

      while (ValeurAngle <= Angle)
      {
         HGauche(Vitesse);
		 std::cout << ValeurAngle << Angle;
         ValeurAngle += Sensor(ANGLE);
      }
      Stop();
   }
}


// Drive permet de conduire le robot.
void IRobot::Drive( short VitesseGauche, short VitesseDroite) const
{
   if (VitesseGauche < -500 || VitesseGauche > 500 || VitesseDroite < -500 || VitesseDroite > 500)
   {
      Erreur(std::cout, "Une valeur de vitesse n'est pas correcte. (Drive)", false);
   }
   else
   {
      // Modification des valeurs pour avoir les vitesses en deux chars.
      char VitesseGaucheBas = ShortToChar(VitesseGauche, BAS);
      char VitesseGaucheHaut = ShortToChar(VitesseGauche, HAUT);
      char VitesseDroiteBas = ShortToChar(VitesseDroite, BAS);
      char VitesseDroiteHaut = ShortToChar(VitesseDroite, HAUT);

      // Envoi de la commande.
      Send(128, 132, 145, VitesseDroiteHaut, VitesseDroiteBas, VitesseGaucheHaut, VitesseGaucheBas);

   }
}


/////////////////////////////////////         SUIVRE LIGNE           //////////////////////////////////////////
//�������������������������������������������������������������������������������������������������������������
// Permet de suivre une ligne noire sur le sol.
char IRobot::SuivreLigne( int Vitesse, int Luminosite_Plancher, int Luminosite_Bande) const
{
   int Limite_Luminosite = (Luminosite_Plancher + Luminosite_Bande) / 2;

   if (Vitesse <= 500 || Vitesse >= 20)
   {
	  SuivreLigneState EtatCourant = SuivreLigneState::CENTRE;
      int Cliff_Signal_Droit = 0;
      int Cliff_Signal_Gauche = 0;

	  std::cout << "SuivreLigne - Recherche de la ligne.." << std::endl;

	  int ValeurDroite = S_Sensor(CLIFF_SIGNAL, AVANT_DROITE);

      while(ValeurDroite >= Limite_Luminosite )	// INVERSER >= pour <= APR�S LES TESTS.
      {
		  ValeurDroite = S_Sensor(CLIFF_SIGNAL, AVANT_DROITE);

		  HGauche(20);
		  Sleep(300);
      }

	  int ValeurGauche = S_Sensor(CLIFF_SIGNAL, AVANT_GAUCHE);

      while(ValeurGauche >= Limite_Luminosite )
      {
		  ValeurGauche = S_Sensor(CLIFF_SIGNAL, AVANT_GAUCHE);

		  HDroite(20);
		  Sleep(300);
      }
      Stop();

	  Sleep(1000);

      //Boucle pour suivre la bande jusqu'a intersection.
      while ( EtatCourant != INTERSECTION)
      {
         Cliff_Signal_Droit = S_Sensor(CLIFF_SIGNAL, AVANT_DROITE);  // 3 verification et moyenne des valeurs par l'utilisation de S_Sensor.
         Cliff_Signal_Gauche = S_Sensor(CLIFF_SIGNAL, AVANT_GAUCHE);
		 
         if (Cliff_Signal_Droit <= Limite_Luminosite && Cliff_Signal_Gauche <= Limite_Luminosite) // Si on est a une intersection.
         {
            Stop();
            EtatCourant = INTERSECTION;
         }
         else
         {if ( S_Sensor(BUMPER,GAUCHE) != 0 || S_Sensor(BUMPER,DROITE) != 0)  // Si il y a une collision sur les bumpers.
         {
            Stop();
			return 2;
         }
         else
         {if (Cliff_Signal_Droit <= Limite_Luminosite)          // Trop � gauche ( Signal droit = noir )
         {
            EtatCourant = TROP_A_GAUCHE;
            HDroite(Vitesse);
         }
         else
         {if (Cliff_Signal_Gauche <= Limite_Luminosite)         // Trop � droite ( Signal gauche = noir )
         {
            EtatCourant = TROP_A_DROITE;
            HGauche(Vitesse);
         }
         else
         {
            EtatCourant = CENTRE;
            Avant(Vitesse);
         }
         }}}


		 Sleep(200);
      }
   }
   else
   {
      Erreur(std::cout, "La vitesse entr�e en parametre n'est pas valide. (SuivreLigne.)", false);
      return 1;
   }

   return 0;
}

/////////////////////////////////////            SENSOR              //////////////////////////////////////////
//�������������������������������������������������������������������������������������������������������������

int IRobot::Sensor(CodeSensor sensor) const
{
   switch (sensor){
   case CodeSensor::WALL :
	  return Read(false, 128,132,142,8);
      break;
   case CodeSensor::WALL_SIGNAL :
	  return Read(false, 128,132,142,27);
      break;
   case CodeSensor::VIRTUAL_WALL :
	  return Read(false, 128,132,142,13);
      break;
   case CodeSensor::BATTERY_CHARGE :
	  return Read(false, 128,132,142,25);
      break;
   case CodeSensor::BATTERY_CAPACITY :
	  return Read(false, 128,132,142,26);
      break;
   case CodeSensor::DISTANCE :
	  return Read(false, 128,132,142,19);
      break;
   case CodeSensor::ANGLE :
      return Read(false, 128,132,142,20);
      break;
   }

   throw std::invalid_argument("Numero de sensor non-reconnu");
}
int IRobot::S_Sensor(CodeSensor sensor) const
{
   int Retour[3];
   int VRetour = 0;
   int Calcul = 0;

   int VMax = 0;
   int VMin = 0;

   // Boucle qui calcule le retour des sensor 5 fois, et le met dans un tableau.
   for (int i =0; i< 3; i++)
   {
	   Retour[i] = Sensor(sensor);
   }

   // Calcul des moyennes. vvv

   int t, t2, k;

   for (t=0; t < 3; t++)
   {
	   for(t2=0; t2 < 2; t++)
	   {
		   if(Retour[t] > Retour[t+1])
		   {
			   k = Retour[t] - Retour[t+1];
			   Retour[t] -=k;
			   Retour[t+1] += k;
		   }
	   }
   }

   return Retour[2];

}
int IRobot::Sensor(CodeSensor sensor, DirectionX precision) const
{
   int Retour = -1;

   switch (sensor){
   case CodeSensor::BUMPER:    // BUMPER
      Retour = Read(false, 128,132,142,7);
	  if (precision == GAUCHE)
      {
         Retour = (Retour & 2);
      }
      else
	  {
		  if (precision == DirectionX::DROITE)
      {
         Retour = (Retour & 1);
      }
      else
      {
         Erreur(std::cout, "La pr�cision pour le sensor BUMPER n'est pas valide. ( Sensor )", false);
      }}
      break;

   case CodeSensor::WHEEL:    // WHEEL
      Retour = Read(false, 128,132,142,7);
	  if (precision == DirectionX::GAUCHE)
      {
         Retour = (Retour & 8);
      }
      else
	  {
		  if (precision == DirectionX::DROITE)
      {
         Retour = (Retour & 4);
      }
      else
      {
         Erreur(std::cout, "La pr�cision pour le sensor WHEEL n'est pas valide. ( Sensor )", false);
      }}
      break;

   case CodeSensor::CLIFF:    // CLIFF
	   if (precision == DirectionX::GAUCHE)
      {
         Retour = Read(false, 128,132,142,9);
      }
      else
	  {
		  if (precision == DirectionX::AVANT_GAUCHE)
      {
         Retour = Read(false, 128,132,142,10);
      }
      else
	  {
		  if (precision == DirectionX::AVANT_DROITE)
      {
         Retour = Read(false, 128,132,142,11);
      }
      else
	  {
		  if (precision == DirectionX::DROITE)
      {
         Retour = Read(false, 128,132,142,12);
      }
      else
      {
         Erreur(std::cout, "La pr�cision pour le sensor CLIFF n'est pas valide. ( Sensor )", false);
      }}}}
      break;

	case CodeSensor::CLIFF_SIGNAL:    // CLIFF_SIGNAL
		if (precision == DirectionX::GAUCHE)
      {
		 do{
         Retour = Read(true,128,132,142,28);
	     }while(Retour < 0 || Retour > 4098);
      }
      else
	  {
		  if (precision == DirectionX::AVANT_GAUCHE)
      {
         do{
         Retour = Read(true, 128,132,142,29);
	     }while(Retour < 0 || Retour > 4098);
      }
      else
	  {
		  if (precision == DirectionX::AVANT_DROITE)
      {
         do{
         Retour = Read(true, 128,132,142,30);
	     }while(Retour < 0 || Retour > 4098);
      }
      else
	  {
		  if (precision == DirectionX::DROITE)
      {
         do{
         Retour = Read(true, 128,132,142,31);
	     }while(Retour < 0 || Retour > 4098);
      }
      else
      {
         Erreur(std::cout, "La pr�cision pour le sensor CLIFF_SIGNAL n'est pas valide. ( Sensor )", false);
      }}}}
      break;

	case CodeSensor::WALL:    // WALL
      Retour = Read(false, 128,132,142,8);
      break;

	case CodeSensor::WALL_SIGNAL:    // WALL_SIGNAL
      Retour = Read(false, 128,132,142,27);
      break;

	case CodeSensor::VIRTUAL_WALL:    // VIRTUAL_WALL
      Retour = Read(false, 128,132,142,13);
      break;

	case CodeSensor::BATTERY_CHARGE:    // BATTERY_CHARGE
      Retour = Read(false, 128,132,142,25);
      break;

	case CodeSensor::BATTERY_CAPACITY:    // BATTERY_CAPACITY
      Retour = Read(false, 128,132,142,26);
      break;

	case CodeSensor::DISTANCE:    // DISTANCE
      Retour = Read(false, 128,132,142,19);
      break;

	case CodeSensor::ANGLE:    // ANGLE
      Retour = Read(false, 128,132,142,20);
      break;
   }
   return Retour;
}
int IRobot::S_Sensor(CodeSensor sensor, DirectionX precision) const
{
   int Retour[3];
   int Moy_Retour = 0;
   int Calcul = 0;

   for (int i =0; i< 3; i++)
   {
	   Retour[i] = Sensor(sensor, precision);
   }

   // Calcul des moyennes.
   int t, t2, k;

   for (t=0; t < 3; t++)
   {
	   for(t2=0; t2 < 2; t2++)
	   {
		   if(Retour[t] > Retour[t2+1])
		   {
			   k = Retour[t] - Retour[t2+1];
			   Retour[t] -=k;
			   Retour[t2+1] += k;
		   }
	   }
   }
   return Retour[2];
}


/////////////////////////////////////            MUSIQUE             //////////////////////////////////////////
//�������������������������������������������������������������������������������������������������������������
void IRobot::Music(int Numero) const
{
	Send(132,141,Numero);
	Sleep(2000);
}



//________________________________________________________________________________________________________________________________________________________________
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                               // -- FONCTIONS PRIV�ES -- //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//����������������������������������������������������������������������������������������������������������������������������������������������������������������



/////////////////////////////////////        INITIALISATION          //////////////////////////////////////////
//�������������������������������������������������������������������������������������������������������������
void IRobot::SetConnection()
{
   // Mise a jour du membre "PortSerie"

   PortSerie = CreateFileA( "COM3", GENERIC_READ | GENERIC_WRITE, 0, 0,OPEN_EXISTING, 0, 0 );
   if( PortSerie == INVALID_HANDLE_VALUE )
   {Erreur(std::cout, "Erreur dans la tentative de connection ( Robot ferme ? ). Error #" + std::to_string(GetLastError()) ,true);}

   ComSetup(PortSerie, 57600, 8, NOPARITY, ONESTOPBIT);
}
void IRobot::ComSetup(HANDLE PortSerie, int BaudRate, short ByteSize, short Parity, short StopBits) const
{
   DCB Dcb;

   if( ! GetCommState( PortSerie, &Dcb ) )
   {
      Erreur(std::cout, "ComSetup - GetCommState. Error #" + std::to_string(GetLastError()) , true);
   }
   
   // Modification des valeurs.
   Dcb.BaudRate = BaudRate;
   Dcb.ByteSize = ByteSize;
   Dcb.Parity   = Parity;
   Dcb.StopBits = StopBits;
   
   if( ! SetCommState( PortSerie, &Dcb ) )
   {
	   Erreur(std::cout, "ComSetup - SetCommState. Error #"+ std::to_string(GetLastError()) , true);
   }
}
void IRobot::ComTimeoutSetup( int IT, int RTTM, int RTTC, int WTTM, int WTTC) const
{
   COMMTIMEOUTS delais;

   delais.ReadIntervalTimeout         = IT;
   delais.ReadTotalTimeoutMultiplier  = RTTM;
   delais.ReadTotalTimeoutConstant    = RTTC;
   delais.WriteTotalTimeoutMultiplier = WTTM;
   delais.WriteTotalTimeoutConstant   = WTTC;

   if( !SetCommTimeouts( PortSerie, &delais ) )
   {
      Erreur(std::cout, "Erreur dans le setting du timeout de la communication.", true);
   }
}
void IRobot::Bonjour() const
{
   // Musique de salutation.
}
void IRobot::SetMusique() const
{
	// Charge.
	Send(140,1,6,60,8,65,8);
    Send(69,8,72,16,69,8,72);
    Send(16);

	// Erreur.
	Send(140,2,2,65,8,60,8);

	// Mario.
	Send(140,3,7,88,8,88,16);
	Send(88,16,84,8,88,16,91);
	Send(32,79,16);
}
void IRobot::Flush(int Quantit�) const
{
   DWORD NbEcrits = 0;
   char *Tampon = new char[Quantit�];

   ComTimeoutSetup(MAXDWORD,MAXDWORD,15*Quantit�,MAXDWORD,15*Quantit�);

   if( !ReadFile(PortSerie, Tampon, strlen(Tampon), &NbEcrits, 0) )
   { Erreur(std::cout, " Erreur dans la reception d'un parametre (Flush).", false);}

   ComTimeoutSetup(0,0,m_Temps_Lecture, 0,m_Temps_Ecriture);

   delete [] Tampon;
}



///////////////////////////////////////           SEND            /////////////////////////////////////////////
//�������������������������������������������������������������������������������������������������������������
// Permet d'envoyer un ou plusieurs chars au robot.
void IRobot::Send(char arg1, ...) const
{
	DWORD NbEcrits = 0;

	va_list ap;

	va_start(ap, arg1);

	try
	{
		for (char i = arg1; ; i = va_arg(ap, char))
		{
			if (!WriteFile(PortSerie, &i, 1, &NbEcrits, 0))
			{
				Erreur(std::cout, " Erreur dans l'envoi d'un parametre.", true);
			}
		}
	}
	catch (std::runtime_error)
	{
	}

	va_end(ap);
}

///////////////////////////////////////           READ            /////////////////////////////////////////////
//�������������������������������������������������������������������������������������������������������������
// Permet d'envoyer une ou plusieurs valeurs au robot et de recevoir le message de retour.
int IRobot::Read(bool HighByte, char arg1, ...) const
{
   int Retour = 0;
   DWORD NbEcrits = 0;

   va_list ap;

   va_start(ap, arg1);

	try
	{
	   for (char i = arg1; ; i = va_arg(ap, char))
	   {
		   if (!WriteFile(PortSerie, &i, 1, &NbEcrits, 0))
		   {
			   Erreur(std::cout, " Erreur dans l'envoi d'un parametre.", false);
		   }
	   }
	}
	catch (std::runtime_error)
	{
	}

	va_end(ap);

	try
	{
		if (!ReadFile(PortSerie, &Retour, 1, &NbEcrits, 0))
		{
			Erreur(std::cout, " Erreur dans la reception d'un parametre (Read-1).", false);
		}
	}
	catch (std::runtime_error)
	{
	}

   if (HighByte)
   {
	   Retour = Retour >> 4;
   }

   return Retour;

}

//////////////////////////////////////           ERREUR            ////////////////////////////////////////////
//�������������������������������������������������������������������������������������������������������������
// Permet d'envoyer un message d'erreur � l'utilisateur ainsi qu'un numero.
void IRobot::Erreur(std::ostream& stream, std::string message, bool SendException) const
{
   if (SendException)
   {
	   throw std::runtime_error("IRobot: " + message);
   }
   else
   {
	   stream << message << std::endl;
   }
}



//////////////////////////////////           TRANSFORMATION            ////////////////////////////////////////
//�������������������������������������������������������������������������������������������������������������
// Transforme un short en un char, en sp�cifiant si on veut le quartet HAUT ou BAS.
char IRobot::ShortToChar(short Valeur, int PositionQuartet) const
{
   char ValeurRetour = 0;

   if( PositionQuartet == HAUT)
   {
      ValeurRetour = Valeur >> 8;
   }
   else
   {if( PositionQuartet == BAS)
   {
      ValeurRetour = ((Valeur << 8) >> 8);
   }}

   return ValeurRetour;
}


bool IRobot::Initialize()
{
	try
	{
		SetConnection();			// Met a jour le HANDLE "PortSerie", set les param�tres de communication.

		Flush(1000);				// Vide le port s�rie des messages re�us � l'initialisation.

		SetMusique();				// Met des musiques dans le robot.

		Stop();
		Bonjour();					// Fait jouer une musique de salutation au d�but du programme - Sers � v�rifier que la communication est �tablie.
	}
	catch (std::runtime_error e)
	{
		std::cout << e.what();
		return false;
	}
	return true;
}
void IRobot::Deconnecter() const
{
	try
	{
		CloseHandle(PortSerie);
	}
	catch (...)
	{
	}
}

//////////////////////////////////    CONSTRUCTEUR --- DESTRUCTEUR     ////////////////////////////////////////
//�������������������������������������������������������������������������������������������������������������
IRobot::IRobot()
	: m_Temps_Lecture{ 100 }, m_Temps_Ecriture{ 100 }, PortSerie{ nullptr }
{
}

IRobot::~IRobot()
{
	Stop();
	Deconnecter();
}

}