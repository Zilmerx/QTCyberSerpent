#include "CyberSerpent.h"
#include "Settings.h"
#include <chrono>
#include <thread>
#include <future>


CyberSerpent::CyberSerpent(int argc, char *argv[])
	: m_IRobot{ VITESSE_IROBOT },
	m_QTApplication{ argc, argv },
	m_QTCyberSerpent{},
	m_VideoAnalyzer{},
   m_IsExecuting{ false }
{
   Utility::Initialize();

   m_QTCyberSerpent.show();
}

CyberSerpent::~CyberSerpent()
{
   Stop();
   m_QTCyberSerpent.Delete();
}

bool CyberSerpent::Initialize()
{
   m_VideoAnalyzer.Initialize(this);
   m_QTCyberSerpent.Initialize(this);

	return true;
}

std::unique_ptr<CyberSerpent> CyberSerpent::Creer_CyberSerpent(int argc, char *argv[])
{
   std::unique_ptr<CyberSerpent> p{ new CyberSerpent{ argc, argv } };
   p->Initialize();
   return p;
}

void CyberSerpent::Start()
{
   std::async(std::launch::async, [this]()
   {
      m_QTCyberSerpent.UI_PutMessageInList("INITIALISATION");

      if (IS_DEBUG)
      {
         m_QTCyberSerpent.SetFunc(Qt::Key_Right, std::bind(&Gameplay::RIGHT, &m_VideoAnalyzer.m_Gameplay));
         m_QTCyberSerpent.SetFunc(Qt::Key_Left, std::bind(&Gameplay::LEFT, &m_VideoAnalyzer.m_Gameplay));
         m_QTCyberSerpent.SetFunc(Qt::Key_Up, std::bind(&Gameplay::UP, &m_VideoAnalyzer.m_Gameplay));
         m_QTCyberSerpent.SetFunc(Qt::Key_Down, std::bind(&Gameplay::DOWN, &m_VideoAnalyzer.m_Gameplay));
      }
      else
      {
         m_QTCyberSerpent.SetFunc(Qt::Key_Up, std::bind(&ControleIRobot::OnUpArrowKeyPress, &m_IRobot));
         m_QTCyberSerpent.SetFunc(Qt::Key_Down, std::bind(&ControleIRobot::OnDownArrowKeyPress, &m_IRobot));
         m_QTCyberSerpent.SetFunc(Qt::Key_Left, std::bind(&ControleIRobot::OnLeftArrowKeyPress, &m_IRobot));
         m_QTCyberSerpent.SetFunc(Qt::Key_Right, std::bind(&ControleIRobot::OnRightArrowKeyPress, &m_IRobot));
      }

      do
      {
         m_QTCyberSerpent.UI_PutMessageInList("CONNECTION CAMERA..");
      } while (!m_VideoAnalyzer.Start(m_QTCyberSerpent.ui.lineEdit_CameraNum->text().toInt()));
      m_QTCyberSerpent.UI_PutMessageInList("REUSSIE.");

      if (!IS_DEBUG)
      {
         do
         {
            m_QTCyberSerpent.UI_PutMessageInList("CONNECTION IROBOT..");

         } while (!m_IRobot.Start(m_QTCyberSerpent.ui.lineEdit_PortConnexion->text().toStdString().c_str()));
         m_QTCyberSerpent.UI_PutMessageInList("REUSSIE.");
      }

      m_QTCyberSerpent.UI_PutMessageInList("DEBUT DE LA PARTIE.");
   });
}

void CyberSerpent::Afficher()
{
   if (!m_IsExecuting)
   {
      m_IsExecuting = true;
      m_QTApplication.exec();
   }
}

void CyberSerpent::Stop()
{
   m_VideoAnalyzer.Stop();

   m_QTCyberSerpent.ClearFunc();
	m_IRobot.Stop();
}