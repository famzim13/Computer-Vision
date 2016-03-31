// centroid.cpp
#include "centroid.hpp"

namespace scv
{

namespace centroid
{

// CONSTRUCTORS
Centroid::Centroid( cv::Vec<int, 2> coordinates, cv::Vec3b rgb )
{
  d_coordinates = coordinates;
  d_rgb = rgb;
}

// DESTRUCTORS
Centroid::~Centroid()
{

}

// ACCESSORS
cv::Vec<int, 2> Centroid::getCoordinates()
{
  return d_coordinates;
}

cv::Vec3b Centroid::getRGB()
{
  return d_rgb;
}

// FREE OPERATORS
float Centroid::distance( cv::Vec<int, 2> coordinates )
{
  return sqrt( pow( d_coordinates(0) - coordinates(0), 2 )
             + pow( d_coordinates(1) - coordinates(1), 2 ) );
}

float Centroid::distance( cv::Vec3b rgb )
{
  return sqrt( pow( d_rgb(0) - rgb(0), 2 )
             + pow( d_rgb(1) - rgb(1), 2 )
             + pow( d_rgb(2) - rgb(2), 2 ) );
}

float Centroid::distance( cv::Vec<int, 2> coordinates, cv::Vec3b rgb )
{
  return sqrt( pow( d_rgb(0) - rgb(0), 2 )
                + pow( d_rgb(1) - rgb(1), 2 )
                + pow( d_rgb(2) - rgb(2), 2 )
                + pow( ( d_coordinates(0) - coordinates(0) )/2, 2 )
                + pow( ( d_coordinates(1) - coordinates(1) )/2, 2 ));
}

void Centroid::update( std::map<int, cv::Vec3b> rgb )
{
  cv::Vec<int, 3> _rgb;
  std::map<int, cv::Vec3b>::const_iterator rgb_it = rgb.cbegin();

  for( ; rgb_it != rgb.cend(); rgb_it++ )
  {
    _rgb(0) += (*rgb_it).second(0);
    _rgb(1) += (*rgb_it).second(1);
    _rgb(2) += (*rgb_it).second(2);
  }

  d_rgb = _rgb / (int)rgb.size();
}

void Centroid::update( std::map<int, cv::Vec<int, 2>> coordinates, std::map<int, cv::Vec3b> rgb )
{
  cv::Vec<int, 2> _coordinates;
  cv::Vec<int, 3> _rgb;
  std::map<int, cv::Vec<int, 2>>::const_iterator coord_it = coordinates.cbegin();
  std::map<int, cv::Vec3b>::const_iterator rgb_it = rgb.cbegin();

  for( ; rgb_it != rgb.cend(); rgb_it++, coord_it++ )
  {
    _rgb(0) += (*rgb_it).second(0);
    _rgb(1) += (*rgb_it).second(1);
    _rgb(2) += (*rgb_it).second(2);
    _coordinates(0) += (*coord_it).second(0);
    _coordinates(1) += (*coord_it).second(1);
  }

  d_rgb = _rgb / (int)rgb.size();
  d_coordinates = _coordinates / (int)coordinates.size();
}

} // end namespace centroid.

} // end namespace scv.
