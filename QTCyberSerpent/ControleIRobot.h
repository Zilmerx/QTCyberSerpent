#pragma once
#include "IRobotDriver.h"



class ControleIRobot
{

	IRobot::IRobot m_IRobotDriver;

	const short VITESSE;
	int DegreeTournure; // Peut être entre -45 et 45. 
						// +45 == DROITE, -45 == GAUCHE.

public:

	ControleIRobot(short vitesse);

	bool Start(const char* port);
	void Stop();

	void OnLeftArrowKeyPress();
	void OnRightArrowKeyPress();

private:

	void ComputeNewSpeed();
};