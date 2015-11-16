#include <thread>
#include <functional>

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

   void Stop()
   {
      m_Run = false;
      m_Thread.join();
   }
};