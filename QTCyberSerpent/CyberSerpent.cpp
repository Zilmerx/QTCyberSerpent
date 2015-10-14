
#include "CyberSerpent.h"
#include <qtimer.h>


CyberSerpent::CyberSerpent(int argc, char *argv[], const std::string camImagePath)
	: m_Gameplay{},
	m_IRobotDriver{},
	m_QTApplication{ argc, argv },
	m_QTCyberSerpent{},
	m_VideoAnalyzer{ camImagePath },
   m_State{ CyberSerpentState::Uninitialized }
{
   m_QTCyberSerpent.show();

   m_QTCyberSerpent.SetFunc(Qt::Key_Left, std::bind(&CyberSerpent::OnLeftArrowKeyPress, this));
   m_QTCyberSerpent.SetFunc(Qt::Key_Right, std::bind(&CyberSerpent::OnRightArrowKeyPress, this));
   m_QTCyberSerpent.SetFunc(Qt::Key_Up, std::bind(&CyberSerpent::OnUpArrowKeyPress, this));
   m_QTCyberSerpent.SetFunc(Qt::Key_Down, std::bind(&CyberSerpent::OnDownArrowKeyPress, this));
}

CyberSerpent::~CyberSerpent()
{
   if (m_State >= CyberSerpentState::Started)
   {
      m_VideoAnalyzer.Stop();
      m_Gameplay.Stop();
      m_QTCyberSerpent.Stop();

      //m_IRobotDriver.Deconnecter(); // Le destructeur fait la job.
   }
}


bool CyberSerpent::Initialize()
{
   Utility::Initialize();

   m_QTCyberSerpent.PutMessageInList("CONNECTION IROBOT..");
   if (!m_IRobotDriver.Initialize("COM1"))
   {
      m_QTCyberSerpent.PutMessageInList("NON REUSSIE");
      //return false;
   }

   m_QTCyberSerpent.PutMessageInList("REUSSIE");

	m_VideoAnalyzer.Initialize(this);
   m_Gameplay.Initialize();
   m_QTCyberSerpent.Initialize(this);

   m_State = CyberSerpentState::Initialized;
	return true;
}

void CyberSerpent::Start()
{
   if (m_State < CyberSerpentState::Initialized)
   {
      m_QTCyberSerpent.PutMessageInList("NON INITIALISE");
		return;
   }

	m_VideoAnalyzer.Start();
   m_Gameplay.Start();

   m_State = CyberSerpentState::Started;
	m_QTApplication.exec();
}

void CyberSerpent::OnLeftArrowKeyPress()
{
   m_IRobotDriver.Gauche(100, 50);
   m_QTCyberSerpent.PutMessageInList("GAUCHE ENREGISTRE");
}

void CyberSerpent::OnRightArrowKeyPress()
{
	m_IRobotDriver.Droite(100, 50);
   m_QTCyberSerpent.PutMessageInList("DROITE ENREGISTRE");
}

void CyberSerpent::OnUpArrowKeyPress()
{
   m_QTCyberSerpent.PutMessageInList("HAUT ENREGISTRE");
}

void CyberSerpent::OnDownArrowKeyPress()
{
   m_QTCyberSerpent.PutMessageInList("BAS ENREGISTRE");
}
