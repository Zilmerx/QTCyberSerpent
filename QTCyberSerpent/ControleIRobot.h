#pragma once
#include "IRobotDriver.h"
#include <chrono>


class ControleIRobot
{

	IRobot::IRobot m_IRobotDriver;

	const short VITESSE;
	int DegreeTournure;

	std::chrono::steady_clock::time_point lastIRobotCommand;
public:

	ControleIRobot(short vitesse);

	bool Start(const char* port);
	void Stop();

	void OnLeftArrowKeyPress();
	void OnRightArrowKeyPress();

private:

	void ComputeNewSpeed() const;
};