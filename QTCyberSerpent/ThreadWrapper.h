#include <thread>
#include <functional>
#include "Utility.h"

class ThreadWrapper
{
   bool m_Run;
   std::thread m_Thread;
   std::function<void()> m_Func;

   void Do()
   {
      while (m_Run)
      {
         try
         {
            m_Func();
         }
         catch (cv::Exception e)
         {
            Utility::Clog(e.what());
         }
      }
   }

public:

   ThreadWrapper(std::function<void()> func)
      : m_Func{ func }
   {
   }

   void Start()
   {
      m_Run = true;
      m_Thread = std::thread(&ThreadWrapper::Do, this);
   }

   bool IsRunning()
   {
      return m_Run;
   }

   void Stop()
   {
      m_Run = false;
      m_Thread.join();
   }
};