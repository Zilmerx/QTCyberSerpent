#include "Collision.h"
#include "Settings.h"
#include <math.h>

Collision::Collision()
{
   x = 0;
   y = 0;
}

Collision::Collision(cv::Mat image)
   : m_Image{ image }
{
   x = 0;
   y = 0;
}

bool Collision::operator==(const Collision& img1) const
{
   return (m_Image.data == img1.m_Image.data);
}

cv::Mat Collision::DrawVec(std::vector<RectCollision>& vec, cv::Mat&& DrawOn)
{
   for (int i = 0; i < vec.size(); ++i)
   {
      vec[i].Draw(std::move(DrawOn));
   }
   return std::move(DrawOn);
}

cv::Mat Collision::DrawVec(std::vector<CircleCollision>& vec, cv::Mat&& DrawOn)
{
   for (int i = 0; i < vec.size(); ++i)
   {
      vec[i].Draw(std::move(DrawOn));
   }
   return std::move(DrawOn);
}

cv::Mat Collision::Draw(cv::Mat&& DrawOn) const
{
   for (int iy = 0; iy < m_Image.rows; ++iy)
   {
      for (int ix= 0; ix < m_Image.cols; ++ix)
      {
         cv::Vec3b val;

         val = m_Image.at<cv::Vec3b>(iy, ix);

         if (val != COULEUR_NONPRINT)
         {
            DrawOn.at<cv::Vec3b>(this->y + iy, this->x + ix) = val;
         }
      }
   }
   return DrawOn;
}
 

RectCollision::RectCollision()
   : Collision()
{
   width = 0;
   height = 0;
}

RectCollision::RectCollision(cv::Mat image)
   : Collision{ image }
{
   width = image.cols;
   height = image.rows;
}

bool RectCollision::Touches(const cv::Rect& rect) const
{
   return (x < rect.x + rect.width
      && x + width > rect.x
      && y < rect.y + rect.width
      && y + width > rect.y);
}

bool RectCollision::Touches(const CircleCollision& circ) const
{
   cv::Point2d circleDistance;
   circleDistance.x = abs(circ.x - (circ.rayon/2) - x);
   circleDistance.y = abs(circ.y - (circ.rayon/2) - y);

   if (circleDistance.x > (width / 2 + circ.rayon)) { return false; }
   if (circleDistance.y > (height / 2 + circ.rayon)) { return false; }

   if (circleDistance.x <= (width / 2)) { return true; }
   if (circleDistance.y <= (height / 2)) { return true; }

   int cornerDistance_sq = pow((circleDistance.x - width / 2), 2) +
      pow((circleDistance.y - height / 2), 2);

   return (cornerDistance_sq <= pow(circ.rayon, 2));
}

RectCollision::operator cv::Rect() const
{
   return cv::Rect(x, y, width, height);
}


CircleCollision::CircleCollision()
   : Collision()
{
   rayon = 0;
}

CircleCollision::CircleCollision(cv::Mat image)
   : Collision{ image }
{
   rayon = std::min(image.cols, image.rows) / 2;
}

bool CircleCollision::Touches(const cv::Rect& rect) const
{
   RectCollision rectcol;
   rectcol.x = rect.x;
   rectcol.y = rect.y;
   rectcol.height = rect.height;
   rectcol.width = rect.width;

   return rectcol.Touches(*this);
}

bool CircleCollision::Touches(const CircleCollision& circ) const
{
   return true;
}