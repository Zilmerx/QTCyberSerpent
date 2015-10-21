#pragma once

#include <ctime>
#include <cstdlib>
#include <string>
#include <qpixmap.h>

#include "RectImage.h"

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

   static QImage Mat2QImage(const cv::Mat& mat)
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

   static bool CvRect1TouchesRect2(const cv::Rect R1, const cv::Rect R2)
   {
      return (R1.contains(cv::Point(R2.x, R2.y)) ||
         R1.contains(cv::Point(R2.x + R2.width, R2.y)) ||
         R1.contains(cv::Point(R2.x, R2.y + R2.height)) ||
         R1.contains(cv::Point(R2.x + R2.width, R2.y + R2.height)));
   }

   static bool CvRect1ContainsRect2(const cv::Rect R1, const cv::Rect R2)
   {
      return ((R2.x + R2.width) < (R1.x + R1.width)
         && (R2.x) > (R1.x)
         && (R2.y) > (R1.y)
         && (R2.y + R2.height) < (R1.y + R1.height));
   }

   static cv::Mat DrawRectImageOnMat(RectImage mat1, cv::Mat mat2)
   {
      cv::Mat matTemp(mat2);
      if (matTemp.data)
      {
         mat1.m_Image.copyTo(matTemp(cv::Rect(mat1.x, mat1.y, mat1.width, mat1.height)));
      }
      return matTemp;
   }
};