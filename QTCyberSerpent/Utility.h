#pragma once

#include <ctime>
#include <cstdlib>
#include <string>

class Utility
{

public:
   static void Initialize()
   {
      srand(static_cast <unsigned int> (time(0)));
   }


   static int RandMinMax(int min, int max)
   {
      return rand() % (max - min + 1) + min;
   }

   static int Min(int a, int b)
   {
      return (((a) < (b)) ? (a) : (b));
   }

   static int MinDistance(Point2D point1, Point2D point2)
   {
      return Min(abs(abs(point1.x) - abs(point2.x)), abs(abs(point1.y) - abs(point2.y)));
   }

   static void Error(std::string Message)
   {
      throw 42;
   }
};