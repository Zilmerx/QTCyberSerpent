#include "Point2D.h"

#pragma once

class Zone2D
{
public:
   // Debut == Haut Gauche,
   // Fin ==== Bas Droite.
   Point2D debut, fin;

   Zone2D(Point2D debut, Point2D fin)
      : debut{ debut }, fin{ fin }
   {
   }

   // Just the tip.
   bool ZonesAreTouching(Zone2D& zone)
   {
      // Haut gauche
      if (debut.x <= zone.fin.x && debut.y <= zone.fin.y)
      {
         return true;
      }
      // Haut droite
      else if (fin.x >= zone.debut.x && debut.y <= zone.fin.y)
      {
         return true;
      }
      // Bas gauche
      else if (debut.x <= zone.fin.x && fin.y >= zone.debut.y)
      {
         return true;
      }
      // Bas droite
      else if (fin.x >= zone.debut.x && fin.y >= zone.debut.y)
      {
         return true;
      }

      return false;
   }

   bool IsInside(Zone2D& zone)
   {
      return (IsInside(zone.debut) && IsInside(zone.fin));
   }

   bool IsInside(Point2D& point)
   {
      return (debut.x <= point.x && debut.y <= point.y && fin.x >= point.x && fin.y >= point.y);
   }
};