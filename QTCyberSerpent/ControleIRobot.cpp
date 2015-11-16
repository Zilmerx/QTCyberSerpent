#include "Settings.h"
#include "ControleIRobot.h"

ControleIRobot::ControleIRobot(short vitesse)
	: m_IRobotDriver{},
	VITESSE{ vitesse },
	DegreeTournure{ 0 }
{
}

bool ControleIRobot::Start(const char* port)
{
   if (m_IRobotDriver.Connecter(port))
   {
      DegreeTournure = 0;
      ComputeNewSpeed();
      return true;
   }
   return false;
}

void ControleIRobot::Stop()
{
   m_IRobotDriver.Stop();
	m_IRobotDriver.Deconnecter();
}


void ControleIRobot::OnUpArrowKeyPress()
{
   PRECISION_TEMPLATEMATCHING += 0.05;
}

void ControleIRobot::OnDownArrowKeyPress()
{
   PRECISION_TEMPLATEMATCHING -= 0.05;
}

void ControleIRobot::OnLeftArrowKeyPress()
{
	if ((std::chrono::steady_clock::now() - lastIRobotCommand) >= INTERVAL_IROBOT)
	{
		lastIRobotCommand = std::chrono::steady_clock::now();

      if (DegreeTournure - IROBOT_DEGREE_INCREMENTATION >= -IROBOT_DEGREE_TOURNURE)
		{
         DegreeTournure -= IROBOT_DEGREE_INCREMENTATION;
		}

		ComputeNewSpeed();
	}
}

void ControleIRobot::OnRightArrowKeyPress()
{
	if ((std::chrono::steady_clock::now() - lastIRobotCommand) >= INTERVAL_IROBOT)
	{
		lastIRobotCommand = std::chrono::steady_clock::now();

      if (DegreeTournure + IROBOT_DEGREE_INCREMENTATION <= IROBOT_DEGREE_TOURNURE)
		{
         DegreeTournure += IROBOT_DEGREE_INCREMENTATION;
		}

		ComputeNewSpeed();
	}
}


void ControleIRobot::ComputeNewSpeed() const
{
	if (DegreeTournure >= 0)
	{
      m_IRobotDriver.Droite(VITESSE, 100-abs(DegreeTournure));
	}
	else
	{
      m_IRobotDriver.Gauche(VITESSE, 100-abs(DegreeTournure));
	}
}