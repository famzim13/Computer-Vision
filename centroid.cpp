// centroid.cpp
#include "centroid.hpp"

namespace scv
{

namespace centroid
{

// CONSTRUCTORS
Centroid::Centroid( cv::Vec2b coordinates, cv::Vec3b rgb )
{
  d_coordinates = coordinates;
  d_rgb = rgb;
}

// DESTRUCTORS
Centroid::~Centroid()
{

}

// ACCESSORS
cv::Vec3b Centroid::getRGB()
{
  return d_rgb;
}

// FREE OPERATORS
float Centroid::distance( cv::Vec3b rgb )
{
  return sqrt( pow( d_rgb(0) - rgb(0), 2 )
             + pow( d_rgb(1) - rgb(1), 2 )
             + pow( d_rgb(2) - rgb(2), 2 ) );
}

float Centroid::distance( cv::Vec2b coordinates, cv::Vec3b rgb )
{
  return sqrt( pow( d_rgb(0) - rgb(0), 2 )
                + pow( d_rgb(1) - rgb(1), 2 )
                + pow( d_rgb(2) - rgb(2), 2 )
                + pow( ( d_coordinates(0) - coordinates(0) )/2, 2 )
                + pow( ( d_coordinates(1) - coordinates(1) )/2, 2 ));
}

void Centroid::update( std::vector<cv::Vec3b> pixels )
{
  cv::Vec<int, 3> rgb;
  int size = pixels.size();

  for( int i=0; i<size; i++ )
  {
    rgb(0) += pixels[i](0);
    rgb(1) += pixels[i](1);
    rgb(2) += pixels[i](2);
  }

  d_rgb = rgb / size;
}

void Centroid::update( std::vector<cv::Vec2b> locations, std::vector<cv::Vec3b> pixels )
{
  cv::Vec<int, 2> coordinates;
  cv::Vec<int, 3> rgb;
  int size = pixels.size();

  for( int i=0; i<size; i++ )
  {
    rgb(0) += pixels[i](0);
    rgb(1) += pixels[i](1);
    rgb(2) += pixels[i](2);
    coordinates(0) += locations[i](0);
    coordinates(1) += locations[i](1);
  }

  d_rgb = rgb / size;
  d_coordinates = coordinates / size;
}

} // end namespace centroid.

} // end namespace scv.
