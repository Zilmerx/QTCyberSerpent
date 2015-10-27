#pragma once

//#include <mutex>
#include <memory>
#include <stdexcept>

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

	T* PointeurGet;
	T* PointeurSet;

	T Value1;
	T Value2;

public:

<<<<<<< HEAD
   DoubleBuffer()
   {
      PointeurGet = nullptr;
      PointeurSet = nullptr;

      //MutexGet;
      //MutexSet;
   }
   ~DoubleBuffer()
   {

   }

   void Switch()
   {
      //std::lock_guard<std::mutex> lockGet(MutexGet);
      //std::lock_guard<std::mutex> lockSet(MutexSet);

      std::swap(PointeurGet, PointeurSet);
   }

   T& Get()
   {
      //std::lock_guard<std::mutex> lockGet(MutexGet);

      if (PointeurGet == nullptr)
      {
         throw std::runtime_error("NULL_VALUE");
      }
      else
      {
         return *PointeurGet;
      }
   }

   void Set(T& value)
   {
      //std::lock_guard<std::mutex> lockSet(MutexSet);
      PointeurSet = &value;

	  std::swap(PointeurGet, PointeurSet);
   }

   void Clear()
   {
      PointeurSet = nullptr;
      PointeurGet = nullptr;
   }
=======
	DoubleBuffer_Copie()
	{
		PointeurGet = &Value1;
		PointeurSet = &Value2;
	}
	~DoubleBuffer_Copie()
	{

	}

	void Switch()
	{
		std::swap(PointeurGet, PointeurSet);
	}

	T Get()
	{
		if (PointeurGet == nullptr)
		{
			throw std::runtime_error("NULL_VALUE");
		}
		else
		{
			return *PointeurGet;
		}
	}

	void Set(const T& value)
	{
		*PointeurSet = value;

		Switch();
	}

	void Set(T&& value)
	{
		*PointeurSet = std::move(value);

		Switch();
	}
>>>>>>> origin/master
};