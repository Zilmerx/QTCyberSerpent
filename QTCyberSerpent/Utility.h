#pragma once

#include <ctime>
#include <cstdlib>
#include <string>
#include <qpixmap.h>
#include <iostream>

#include "Collision.h"
#include "Settings.h"

#include "opencv2\imgproc.hpp"

class Utility
{
private:
   Utility(){}

public:
   static void Initialize()
   {
      srand(static_cast <unsigned int> (time(0)));
   }

   static int RandMinMax(const int min, const int max)
   {
      return rand() % (max - min + 1) + min;
   }

   static int Min(const int a, const  int b)
   {
      return (((a) < (b)) ? (a) : (b));
   }

   static int MinDistance(const cv::Point point1, const cv::Point point2)
   {
      return Min(abs(abs(point1.x) - abs(point2.x)), abs(abs(point1.y) - abs(point2.y)));
   }

   static QImage Mat2QImage(const cv::Mat&& mat)
   {
      switch (mat.type())
      {
         // 8-bit, 4 channel
      case CV_8UC4:
      {
         return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB32);
      }

         // 8-bit, 3 channel
      case CV_8UC3:
      {
         QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);

         return image.rgbSwapped();
      }

         // 8-bit, 1 channel
      case CV_8UC1:
      {
         static QVector<QRgb>  sColorTable;

         // only create our color table once
         if (sColorTable.isEmpty())
         {
            for (int i = 0; i < 256; ++i)
               sColorTable.push_back(qRgb(i, i, i));
         }

         QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);

         image.setColorTable(sColorTable);

         return image;
      }

      default:
         break;
      }

      return QImage();
   }

   template<class T>
   static void PutRect1InCenterOfRect2(T& rect1, const cv::Rect& rect2)
   {
      rect1.pos.x = ((rect2.width - rect1.width) / 2) + rect2.x;
      rect1.pos.y = ((rect2.height - rect1.height) / 2) + rect2.y;
   }

   static bool MatIsNull(const cv::Mat& mat)
   {
      return (mat.empty() && !mat.data && mat.rows <= 0 && mat.cols <= 0);
   }

   static void Clog(const char* s)
   {
      std::clog << s << "\r\n";
   }
};