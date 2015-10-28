
#include "CyberSerpent.h"
#include <qtimer.h>


CyberSerpent::CyberSerpent(int argc, char *argv[])
	: m_Gameplay{},
	m_IRobotDriver{},
	m_QTApplication{ argc, argv },
	m_QTCyberSerpent{},
	m_VideoAnalyzer{},
   m_State{ CyberSerpentState::Uninitialized },
   m_IsExecuting{ false }
{
   Utility::Initialize();

   m_QTCyberSerpent.show();
}

CyberSerpent::~CyberSerpent()
{
   Delete();
}

bool CyberSerpent::Initialize()
{
	m_VideoAnalyzer.Initialize(this);
   m_Gameplay.Initialize(this);
   m_QTCyberSerpent.Initialize(this);

   m_State = CyberSerpentState::Initialized;
	return true;
}

void CyberSerpent::Start()
{
   if (m_State < CyberSerpentState::Initialized)
   {
      m_QTCyberSerpent.UI_PutMessageInList("NON INITIALISE");
      return;
   }

   m_QTCyberSerpent.UI_PutMessageInList("CONNECTION IROBOT..");
   if (m_IRobotDriver.Connecter(m_QTCyberSerpent.ui.lineEdit_PortConnexion->text().toStdString().c_str()))
   {
      m_QTCyberSerpent.UI_PutMessageInList("REUSSIE");
   }
   else
   {
      m_QTCyberSerpent.UI_PutMessageInList("NON REUSSIE");
   }

   m_QTCyberSerpent.SetFunc(Qt::Key_Left, std::bind(&CyberSerpent::OnLeftArrowKeyPress, this));
   m_QTCyberSerpent.SetFunc(Qt::Key_Right, std::bind(&CyberSerpent::OnRightArrowKeyPress, this));
   m_QTCyberSerpent.SetFunc(Qt::Key_Up, std::bind(&CyberSerpent::OnUpArrowKeyPress, this));
   m_QTCyberSerpent.SetFunc(Qt::Key_Down, std::bind(&CyberSerpent::OnDownArrowKeyPress, this));

	m_VideoAnalyzer.Start(m_QTCyberSerpent.ui.lineEdit_CameraPath->text().toStdString());
   m_Gameplay.Start(m_QTCyberSerpent.ui.lineEdit_MaxScore->text().toInt(), m_QTCyberSerpent.ui.lineEdit_NbObstacles->text().toInt());

   m_State = CyberSerpentState::Started;
}

void CyberSerpent::Afficher()
{
   if (m_State >= CyberSerpentState::Initialized)
   {
      if (!m_IsExecuting)
      {
         m_IsExecuting = true;
         m_QTApplication.exec();
      }
   }
}

void CyberSerpent::Stop()
{
   if (m_State == CyberSerpentState::Started)
   {
      m_VideoAnalyzer.Stop();
      m_Gameplay.Stop();

      m_QTCyberSerpent.ClearFunc();
      m_IRobotDriver.Deconnecter();
      m_State = CyberSerpentState::Stopped;
   }
}

void CyberSerpent::Delete()
{
   if (m_State >= CyberSerpentState::Initialized)
   {
      Stop();

      m_QTCyberSerpent.Delete();
      m_State = CyberSerpentState::Uninitialized;
   }
}

void CyberSerpent::OnLeftArrowKeyPress()
{
   m_IRobotDriver.Gauche(100, 50);
   m_QTCyberSerpent.UI_PutMessageInList("GAUCHE ENREGISTRE");
}

void CyberSerpent::OnRightArrowKeyPress()
{
	m_IRobotDriver.Droite(100, 50);
   m_QTCyberSerpent.UI_PutMessageInList("DROITE ENREGISTRE");
}

void CyberSerpent::OnUpArrowKeyPress()
{
   m_QTCyberSerpent.UI_PutMessageInList("HAUT ENREGISTRE");
}

void CyberSerpent::OnDownArrowKeyPress()
{
   m_QTCyberSerpent.UI_PutMessageInList("BAS ENREGISTRE");
}
