#pragma once

#include "opencv2\core.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"


class RectImage : public cv::Rect
{
public:
   cv::Mat& m_Image;

   RectImage(cv::Mat& image)
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
};