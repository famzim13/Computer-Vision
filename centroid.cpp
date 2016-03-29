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

void Centroid::update( std::vector<cv::Vec2b> locations, std::vector<cv::Vec3b> pixels )
{
  int r_value, g_value, b_value, x_value, y_value = 0;

  for( int i=0; i<pixels.size(); i++ )
  {
    r_value += pixels[i](0);
    g_value += pixels[i](1);
    b_value += pixels[i](2);
    x_value += locations[i](0);
    y_value += locations[i](1);
  }

  d_rgb(0) = r_value / pixels.size();
  d_rgb(1) = g_value / pixels.size();
  d_rgb(2) = b_value / pixels.size();
  d_coordinates(0) = x_value / locations.size();
  d_coordinates(1) = y_value / locations.size();
}

} // end namespace centroid.

} // end namespace scv.
