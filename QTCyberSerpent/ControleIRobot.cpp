#include "ControleIRobot.h"

ControleIRobot::ControleIRobot(short vitesse)
	: m_IRobotDriver{},
	VITESSE{ vitesse },
	DegreeTournure{ 0 }
{
}

bool ControleIRobot::Start(const char* port)
{
	return m_IRobotDriver.Connecter(port);
}

void ControleIRobot::Stop()
{
	m_IRobotDriver.Deconnecter();
}




void ControleIRobot::OnLeftArrowKeyPress()
{
	if ((std::chrono::steady_clock::now() - lastIRobotCommand) >= INTERVAL_IROBOT)
	{
		lastIRobotCommand = std::chrono::steady_clock::now();

		if (DegreeTournure - 15 >= -45)
		{
			DegreeTournure -= 15;
		}

		ComputeNewSpeed();
	}
}

void ControleIRobot::OnRightArrowKeyPress()
{
	if ((std::chrono::steady_clock::now() - lastIRobotCommand) >= INTERVAL_IROBOT)
	{
		lastIRobotCommand = std::chrono::steady_clock::now();

		if (DegreeTournure + 15 <= 45)
		{
			DegreeTournure += 15;
		}

		ComputeNewSpeed();
	}
}


void ControleIRobot::ComputeNewSpeed()
{
	if (DegreeTournure >= 0)
	{
		m_IRobotDriver.Droite(VITESSE, DegreeTournure);
	}
	else
	{
		m_IRobotDriver.Gauche(VITESSE, DegreeTournure);
	}
}