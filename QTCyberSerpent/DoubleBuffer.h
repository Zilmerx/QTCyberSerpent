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
      ValueSet = T;
      ValueGet = T;
   }

   T Get()
   {
      std::lock_guard<std::mutex> lock(MutexGet);

      return ValueGet;
   }

	void Set(const T& value)
	{
      ValueSet = value;

		Switch();
	}

	void Set(T&& value)
	{
      ValueSet = std::move(value);

		Switch();
	}
};