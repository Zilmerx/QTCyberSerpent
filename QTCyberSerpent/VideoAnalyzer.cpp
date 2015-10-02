#include "VideoAnalyzer.h"
#include "CyberSerpent.h"
#include "Utility.h"

VideoAnalyzer::VideoAnalyzer(const std::string camImagePath) 
	: m_CamImagePath{ camImagePath }, 
	RunLecture{ false }, 
	RunAnalyse{ false }, 
	RunAffichage{ false }
{
}

VideoAnalyzer::~VideoAnalyzer()
{
}

void VideoAnalyzer::Initialize(CyberSerpent* linked)
{
	m_Game = linked;
}

void VideoAnalyzer::Start()
{
	RunLecture = true;
	ThreadLecture = std::thread(&VideoAnalyzer::LireFichier, this);

	RunAnalyse = true;
	ThreadAnalyse = std::thread(&VideoAnalyzer::Analyser, this);

	RunAffichage = true;
	ThreadAffichage = std::thread(&VideoAnalyzer::Afficher, this);
}

void VideoAnalyzer::Stop()
{
	RunAffichage = false;
	ThreadAffichage.join();

	RunAnalyse = false;
	ThreadAnalyse.join();

	RunLecture = false;
	ThreadLecture.join();
}

//////////////////////////////////////////////////////////////////
// Threads
//////////////////////////////////////////////////////////////////

void VideoAnalyzer::LireFichier()
{
	cv::Mat mat;
	while (RunLecture)
	{
		cv::imread(m_CamImagePath, CV_LOAD_IMAGE_UNCHANGED).copyTo(mat);

		if (mat.data)
		{
			m_ImageLue.Set(mat);
			m_ImageLue.Switch();
		}
	}
}

void VideoAnalyzer::Analyser()
{
	cv::Mat* mat;

	while (RunAnalyse)
	{
		try
		{
			mat = &m_ImageLue.Get();

			// Analyse quelquonque.

			m_ImageAnalysee.Set(*mat);
			m_ImageAnalysee.Switch();
		}
		catch (...)
		{
		}
	}
}

void VideoAnalyzer::Afficher()
{
	while (RunAffichage)
	{
		try
		{
			m_Game->m_QTCyberSerpent.PutImage(Utility::Mat2QPixmap(m_ImageAnalysee.Get()));
		}
		catch (...)
		{
		}
	}
}