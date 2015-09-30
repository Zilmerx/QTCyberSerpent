#pragma once

#include <vector>
#include "Point2D.h"


class Gameplay
{
   std::vector<Point2D> m_Obstacles;

public:

   const static int MAPSIZE_X = 500;
   const static int MAPSIZE_Y = 500;


private:
   // Mets "amount" Point2D dans le tableau, qui ont un x,y entre "0" et "MAPSIZE_X"/"MAPSIZE_Y".
   void fillWithRandPoints(std::vector<Point2D>& tab, int amount);


public:
   Gameplay();
   ~Gameplay();

};