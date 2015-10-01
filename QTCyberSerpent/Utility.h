#pragma once

#include <ctime>
#include <cstdlib>
#include <string>
#include <qpixmap.h>

#include "opencv2\imgproc.hpp"

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

   static QImage Mat2QImage(const cv::Mat &mat)
   {
      switch (mat.type())
      {
         // 8-bit, 4 channel
      case CV_8UC4:
      {
         QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB32);

         return image;
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

   static QPixmap Mat2QPixmap(const cv::Mat& mat)
   {
      return QPixmap::fromImage(Mat2QImage(mat));
   }

};