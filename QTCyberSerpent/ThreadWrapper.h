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
         m_Func();
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
      try
      {
         m_Run = false;
         m_Thread.join();
      }
      catch (std::system_error e)
      {
         Utility::Clog(e.what());
      }
   }
};