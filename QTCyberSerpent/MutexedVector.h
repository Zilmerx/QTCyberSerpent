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

template<class T>
class MutexedObj
{
public:
   T m_Obj;
   std::mutex m_Mutex;

   MutexedObj()
   {
   }
};