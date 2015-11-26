#include "Collision.h"
#include "Settings.h"
#include <math.h>

Collision::Collision()
{
   pos.x = 0;
   pos.y = 0;
}

Collision::Collision(cv::Mat image)
   : m_Image{ image }
{
   pos.x = 0;
   pos.y = 0;
}

bool Collision::operator==(const Collision& img1) const
{
   return (m_Image.data == img1.m_Image.data);
}

cv::Mat Collision::DrawVec(const std::vector<RectCollision>& vec, cv::Mat&& DrawOn)
{
   for (int i = 0; i < vec.size(); ++i)
   {
      DrawOn = vec[i].Draw(std::move(DrawOn));
   }
   return std::move(DrawOn);
}

cv::Mat Collision::DrawVec(const std::vector<CircleCollision>& vec, cv::Mat&& DrawOn)
{
   for (int i = 0; i < vec.size(); ++i)
   {
      DrawOn = vec[i].Draw(std::move(DrawOn));
   }
   return std::move(DrawOn);
}

cv::Mat Collision::Draw(cv::Mat&& DrawOn) const
{
   for (int iy = 0; iy < m_Image.rows; ++iy)
   {
      for (int ix = 0; ix < m_Image.cols; ++ix)
      {
         cv::Vec3b val;

         val = m_Image.at<cv::Vec3b>(iy, ix);

         if (val != COULEUR_NONPRINT)
         {
            DrawOn.at<cv::Vec3b>(pos.y + iy, pos.x + ix) = val;
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

RectCollision::RectCollision(cv::Rect rect)
{
   pos = rect.tl();
   width = rect.width;
   height = rect.height;
}

bool RectCollision::Touches(const cv::Rect& rect) const
{
   return (pos.x < rect.x + rect.width
      && pos.x + width > rect.x
      && pos.y < rect.y + rect.width
      && pos.y + width > rect.y);
}

bool RectCollision::Touches(const CircleCollision& circ) const
{
   cv::Point2d circleDistance;
   circleDistance.x = abs(circ.pos.x - (circ.rayon / 2) - pos.x);
   circleDistance.y = abs(circ.pos.y - (circ.rayon / 2) - pos.y);

   if (circleDistance.x > (width / 2 + circ.rayon)) { return false; }
   if (circleDistance.y > (height / 2 + circ.rayon)) { return false; }

   if (circleDistance.x <= (width / 2)) { return true; }
   if (circleDistance.y <= (height / 2)) { return true; }

   int cornerDistance_sq = pow((circleDistance.x - width / 2), 2) +
      pow((circleDistance.y - height / 2), 2);

   return (cornerDistance_sq <= pow(circ.rayon, 2));
}

RectCollision& RectCollision::operator=(RectCollision& other)
{
   std::swap(pos, other.pos);
   std::swap(m_Image, other.m_Image);
   std::swap(width, other.width);
   std::swap(height, other.height);

   return *this;
}

RectCollision::operator cv::Rect() const
{
   return cv::Rect(pos.x, pos.y, width, height);
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
   rectcol.pos.x = rect.x;
   rectcol.pos.y = rect.y;
   rectcol.height = rect.height;
   rectcol.width = rect.width;

   return rectcol.Touches(*this);
}

bool CircleCollision::Touches(const CircleCollision& circ) const
{
   return true;
}

CircleCollision& CircleCollision::operator=(CircleCollision& other)
{
   std::swap(pos, other.pos);
   std::swap(m_Image, other.m_Image);
   std::swap(rayon, other.rayon);

   return *this;
}