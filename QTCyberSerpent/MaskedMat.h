#pragma once
#include "opencv2\core.hpp"
#include "Settings.h"

class MaskedMat
{

public:
   cv::Mat m_Image;
   cv::Mat m_Mask;

   MaskedMat()
   {
   }

   MaskedMat(cv::Mat image)
      : m_Image{ image },
      m_Mask{ makeMask(image) }
   {
   }

   MaskedMat& operator=(MaskedMat& other)
   {
      std::swap(m_Image, other.m_Image);
      std::swap(m_Mask, other.m_Mask);

      return *this;
   }

   void Set(cv::Mat mat)
   {
      m_Image = mat;
      m_Mask = makeMask(mat);
   }

private:

   cv::Mat makeMask(cv::Mat image)
   {
      cv::Mat inrange_output = cv::Mat::zeros(image.size(), image.type());

      cv::inRange(image, COULEUR_NONPRINT_MIN, COULEUR_NONPRINT_MAX, inrange_output);

      return inrange_output;
   }
};