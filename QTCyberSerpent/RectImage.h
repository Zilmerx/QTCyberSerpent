#pragma once

#include "opencv2\core.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"


class RectImage : public cv::Rect
{
public:
   const cv::Mat& m_Image;

   RectImage(const cv::Mat& image)
      : m_Image{ image }
   {
      x = 0;
      y = 0;
      width = m_Image.cols;
      height = m_Image.rows;
   }

   RectImage(const RectImage& copyfrom)
      : RectImage(copyfrom.m_Image)
   {
      x = copyfrom.x;
      y = copyfrom.y;
   }
};