#include "Collision.h"
#include "Settings.h"
#include "Utility.h"
#include <math.h>

Collision::Collision()
{
   pos.x = 0;
   pos.y = 0;
}

Collision::Collision(const cv::Mat& image)
   : m_Image{ &image }
{
   pos.x = 0;
   pos.y = 0;
}

bool Collision::operator==(const Collision& img1) const
{
   return (m_Image->data == img1.m_Image->data);
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
   if (!Utility::MatIsNull(*m_Image))
   {
      cv::MatConstIterator_<cv::Vec3b> it, end;
      for (it = m_Image->begin<cv::Vec3b>(), end = m_Image->end<cv::Vec3b>(); it != end; ++it)
      {
         if (*it != COULEUR_NONPRINT)
         {
            DrawOn.at<cv::Vec3b>(it.pos() + pos) = *it;
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

RectCollision::RectCollision(const cv::Mat& image)
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
      && pos.y < rect.y + rect.height
      && pos.y + height > rect.y);
}

bool RectCollision::Touches(const CircleCollision& circ) const
{
   cv::Point2d circleDistance;
   circleDistance.x = abs(circ.Center().x - (width / 2) - pos.x);
   circleDistance.y = abs(circ.Center().y - (height / 2) - pos.y);

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

CircleCollision::CircleCollision(const cv::Mat& image)
   : Collision{ image }
{
   rayon = std::min(image.cols, image.rows) / 2;
}

cv::Point2d CircleCollision::Center() const
{
   return cv::Point2d(pos.x + rayon, pos.y + rayon);
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
   cv::Point2d circ1 = Center();
   cv::Point2d circ2 = circ.Center();

   auto deltax = std::abs(circ1.x - circ2.x);
   auto deltay = std::abs(circ1.y - circ2.y);
   float distSq = (deltax * 2) + (deltay * 2);

   return !(distSq > ((rayon + circ.rayon) * 2));
}

CircleCollision::operator cv::Rect() const
{
   int width = rayon * 2;
   return cv::Rect(pos.x, pos.y, width, width);
}

CircleCollision& CircleCollision::operator=(CircleCollision& other)
{
   std::swap(pos, other.pos);
   std::swap(m_Image, other.m_Image);
   std::swap(rayon, other.rayon);

   return *this;
}