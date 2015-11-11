
#include "CyberSerpent.h"
#include <qtimer.h>


CyberSerpent::CyberSerpent(int argc, char *argv[])
	: m_Gameplay{},
	m_IRobot{ 200 },
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
   if (m_IRobot.Start(m_QTCyberSerpent.ui.lineEdit_PortConnexion->text().toStdString().c_str()))
   {
      m_QTCyberSerpent.UI_PutMessageInList("REUSSIE");
   }
   else
   {
      m_QTCyberSerpent.UI_PutMessageInList("NON REUSSIE");
   }

   //m_QTCyberSerpent.SetFunc(Qt::Key_Left, std::bind(&ControleIRobot::OnLeftArrowKeyPress, m_IRobot));
   //m_QTCyberSerpent.SetFunc(Qt::Key_Right, std::bind(&ControleIRobot::OnRightArrowKeyPress, m_IRobot));

   m_QTCyberSerpent.SetFunc(Qt::Key_Right, std::bind(&Gameplay::RIGHT, m_Gameplay));
   m_QTCyberSerpent.SetFunc(Qt::Key_Left, std::bind(&Gameplay::LEFT, m_Gameplay));
   m_QTCyberSerpent.SetFunc(Qt::Key_Up, std::bind(&Gameplay::UP, m_Gameplay));
   m_QTCyberSerpent.SetFunc(Qt::Key_Down, std::bind(&Gameplay::DOWN, m_Gameplay));


   m_VideoAnalyzer.Start(m_QTCyberSerpent.ui.lineEdit_CameraNum->text().toInt());
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
	  m_IRobot.Stop();
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