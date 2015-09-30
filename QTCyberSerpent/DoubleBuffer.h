#include <mutex>
#include <memory>

template <class T>
class DoubleBuffer
{
private:

   T* PointeurGet;
   T* PointeurSet;

   std::mutex MutexGet;
   std::mutex MutexSet;

public:

   DoubleBuffer()
   {
      PointeurGet = nullptr;
      PointeurSet = nullptr;

      MutexGet;
      MutexSet;
   }
   ~DoubleBuffer()
   {

   }

   void Switch()
   {
      std::lock_guard<std::mutex> lockGet(MutexGet);
      std::lock_guard<std::mutex> lockSet(MutexSet);

      std::swap(PointeurGet, PointeurSet);
   }

   T Get()
   {
      std::lock_guard<std::mutex> lockGet(MutexGet);
      return *PointeurGet;
   }

   void Set(T &value)
   {
      std::lock_guard<std::mutex> lockSet(MutexSet);
      PointeurSet = &value;
   }
};