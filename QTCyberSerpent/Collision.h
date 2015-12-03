#pragma once
#include "opencv2\core.hpp"

class RectCollision;
class CircleCollision;

class Collision
{
public:
   cv::Point pos;
   const cv::Mat* m_Image;

   Collision();

   Collision(const cv::Mat& image);

   bool operator==(const Collision& img1) const;

   virtual bool Touches(const cv::Rect& rect) const = 0;

   virtual bool Touches(const CircleCollision& circ) const = 0;

   static cv::Mat DrawVec(const std::vector<RectCollision>& vec, cv::Mat&& DrawOn);

   static cv::Mat DrawVec(const std::vector<CircleCollision>& vec, cv::Mat&& DrawOn);

   cv::Mat Draw(cv::Mat&& DrawOn) const;
};

class RectCollision : public Collision
{
public:
   int width, height;

   RectCollision();

   RectCollision(cv::Rect rect);

   RectCollision(const cv::Mat& image);

   bool Touches(const cv::Rect& rect) const override;

   bool Touches(const CircleCollision& circ) const override;

   operator cv::Rect() const;

   RectCollision& operator=(RectCollision& other);
};

class CircleCollision : public Collision
{
public:
   double rayon;

   CircleCollision();

   CircleCollision(const cv::Mat& image);

   cv::Point2d Center() const;

   bool Touches(const cv::Rect& rect) const override;

   bool Touches(const CircleCollision& circ) const override;

   operator cv::Rect() const;

   CircleCollision& operator=(CircleCollision& other);
};