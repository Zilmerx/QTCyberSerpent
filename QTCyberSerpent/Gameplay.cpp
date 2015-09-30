#include "Gameplay.h"
#include "Utility.h"


// PUBLIC

#pragma region Constructeur / Destructeur
Gameplay::Gameplay()
{
}

Gameplay::~Gameplay()
{
}
#pragma endregion




// PRIVATE

void Gameplay::fillWithRandPoints(std::vector<Point2D>& tab, int amount)
{
   tab.clear();
   for (int i = 0; i < amount; ++i)
   {
      tab.push_back(Point2D(Utility::RandMinMax(0, Gameplay::MAPSIZE_X), Utility::RandMinMax(0, Gameplay::MAPSIZE_Y)));
   }
}
