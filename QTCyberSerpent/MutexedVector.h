#pragma once
#include <mutex>
#include <memory>
#pragma once
#include <mutex>
#include <memory>

template<class T>
class MutexedVector
{
public:
   std::vector<T> m_Vector;
   std::mutex m_Mutex;

   MutexedVector()
   {
   }
};