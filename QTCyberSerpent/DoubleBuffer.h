#pragma once

//#include <mutex>
#include <memory>
#include <stdexcept>
#include <mutex>
#include <chrono>
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
			throw std::runtime_error("NULL_VALUE");
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

   std::mutex MutexGet;

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
      HasValue = false;
   }

   T WaitGet(std::chrono::milliseconds DurationCheck)
   {
      while (!HasValue)
      {
         std::this_thread::sleep_for(DurationCheck);
      }

      return Get();
   }

   T Get()
   {
      std::unique_lock<std::mutex> lock(MutexGet);

      if (!HasValue)
      {
         throw NullException();
      }
      else
      {
         HasValue = false;
         return ValueGet;
      }
   }

	void Set(const T& value)
	{
      ValueSet = value;

		Switch();
      HasValue = true;
	}

	void Set(T&& value)
	{
      ValueSet = std::move(value);

		Switch();
      HasValue = true;
	}
};