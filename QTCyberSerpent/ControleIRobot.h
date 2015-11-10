#pragma once
#include "IRobotDriver.h"
#include <chrono>


class ControleIRobot
{

	IRobot::IRobot m_IRobotDriver;

	const short VITESSE;
	int DegreeTournure; // Peut être entre -45 et 45. 
						// +45 == DROITE, -45 == GAUCHE.

	const std::chrono::milliseconds INTERVAL_IROBOT = std::chrono::milliseconds(1000);
	std::chrono::steady_clock::time_point lastIRobotCommand;
public:

	ControleIRobot(short vitesse);

	bool Start(const char* port);
	void Stop();

	void OnLeftArrowKeyPress();
	void OnRightArrowKeyPress();

private:

	void ComputeNewSpeed();
};