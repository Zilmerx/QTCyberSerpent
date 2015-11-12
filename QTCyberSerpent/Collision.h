#pragma once
#include "opencv2\core.hpp"

class RectCollision;
class CircleCollision;

class Collision
{
public:
   int x, y;
   cv::Mat m_Image;

   Collision();

   Collision(cv::Mat image);

   bool operator==(const Collision& img1) const;

   virtual bool Touches(const cv::Rect& rect) const = 0;

   virtual bool Touches(const CircleCollision& circ) const = 0;

   static cv::Mat DrawVec(std::vector<RectCollision>& vec, cv::Mat&& DrawOn);

   static cv::Mat DrawVec(std::vector<CircleCollision>& vec, cv::Mat&& DrawOn);

   cv::Mat Collision::Draw(cv::Mat&& DrawOn) const;
};

class RectCollision : public Collision
{
public:
   int width, height;

   RectCollision();

   RectCollision(cv::Mat image);

   bool Touches(const cv::Rect& rect) const override;

   bool Touches(const CircleCollision& circ) const override;

   operator cv::Rect() const;
};

class CircleCollision : public Collision
{
public:
   double rayon;

   CircleCollision();

   CircleCollision(cv::Mat image);

   bool Touches(const cv::Rect& rect) const override;

   bool Touches(const CircleCollision& circ) const override;
};