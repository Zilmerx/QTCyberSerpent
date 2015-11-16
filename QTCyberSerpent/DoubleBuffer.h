#pragma once

#include <memory>
#include <mutex>
#include <condition_variable>
#include "NullException.h"

template <class T>
class DoubleBuffer_Ptr
{
private:

	T* PointeurGet;
	T* PointeurSet;

public:

	DoubleBuffer_Ptr()
	{
		PointeurGet = nullptr;
		PointeurSet = nullptr;
	}
	~DoubleBuffer_Ptr()
	{

	}

	void Switch()
	{
		std::swap(PointeurGet, PointeurSet);
	}

   void Clear()
   {
      PointeurSet = nullptr;
      PointeurGet = nullptr;
   }

	T* Get()
	{
		if (PointeurGet == nullptr)
		{
         throw NullException();
		}
		else
		{
			return PointeurGet;
		}
	}

	void Set(T* value)
	{
		PointeurSet = value;

		Switch();
	}
};

template <class T>
class DoubleBuffer_Copie
{
private:

   bool HasValue;
	T ValueGet;
	T ValueSet;

   std::mutex mutex;
   std::condition_variable cond_var;

public:

   DoubleBuffer_Copie()
      : HasValue{ false }
   {
   }
   ~DoubleBuffer_Copie()
   {
   }

   void Switch()
   {
      std::swap(std::move(ValueGet), std::move(ValueSet));
   }

   void Clear()
   {
      ValueSet = T();
      ValueGet = T();
   }

   T Get()
   {
      return ValueGet;
   }

   T WaitGet()
   {
      std::unique_lock<std::mutex> lock(mutex);
      while (!HasValue) cond_var.wait(lock);

      return ValueGet;
   }

	void Set(const T& value)
	{
      std::unique_lock<std::mutex> lock(mutex);

      ValueSet = value;
      HasValue = true;

      cond_var.notify_all();

		Switch();
	}

	void Set(T&& value)
	{
      std::unique_lock<std::mutex> lock(mutex);

      ValueSet = std::move(value);
      HasValue = true;

      cond_var.notify_all();

		Switch();
	}
};