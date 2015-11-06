#pragma once

#include "opencv2\core.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"


class RectImage : public cv::Rect
{
public:
   cv::Mat m_Image;

   RectImage()
   {
      x = 0;
      y = 0;
      width = 0;
      height = 0;
   }

   RectImage(cv::Mat image)
      : m_Image{ image }
   {
      x = 0;
      y = 0;
      width = image.cols;
      height = image.rows;
   }

   RectImage(const RectImage& copyfrom)
      : RectImage(copyfrom.m_Image)
   {
      x = copyfrom.x;
      y = copyfrom.y;
   }

   bool operator==(const RectImage& img1)
   {
      return (m_Image.data == img1.m_Image.data);
   }

   RectImage& operator=(RectImage other)
   {
      m_Image = other.m_Image;
      x = other.x;
      y = other.y;
      width = other.width;
      height = other.height;
      return *this;
   }
};