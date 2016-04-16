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
  d_pixel_coordinates = std::map<int, cv::Vec2i>();
  d_pixel_rgb = std::map<int, cv::Vec3b>();
}

// DESTRUCTORS
Centroid::~Centroid()
{

}

// ACCESSORS
cv::Vec2i Centroid::getCoordinates()
{
  return d_coordinates;
}

cv::Vec3b Centroid::getRGB()
{
  return d_rgb;
}

// MUTATORS
void Centroid::addCoordinate( int key, cv::Vec2i coordinate )
{
  d_pixel_coordinates.insert( std::pair<int, cv::Vec2i>( key, coordinate ) );
}

void Centroid::addRGB( int key, cv::Vec3b rgb )
{
  d_pixel_rgb.insert( std::pair<int, cv::Vec3b>( key, rgb ) );
}

void Centroid::removeCoordinate( int key )
{
  d_pixel_coordinates.erase( key );
}

void Centroid::removeRGB( int key )
{
  d_pixel_rgb.erase( key );
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

float Centroid::distance( cv::Vec<int, 2> coordinates, cv::Vec3b rgb, float range )
{
  float rgb_dist = distance( rgb );
  float coord_dist = distance( coordinates );
  return sqrt( pow( rgb_dist, 2 )
             + pow( coord_dist, 2 ) * pow( range, 2 ) );
}

void Centroid::update()
{
  bool d_same = true;
  cv::Vec3i rgb( 0, 0, 0 );

  for( auto rgb_it = d_pixel_rgb.cbegin(); rgb_it != d_pixel_rgb.cend(); rgb_it++ )
  {
    rgb(0) += (*rgb_it).second(0);
    rgb(1) += (*rgb_it).second(1);
    rgb(2) += (*rgb_it).second(2);
  }

  d_rgb = rgb / (int)d_pixel_rgb.size();
}

void Centroid::update( std::map<int, cv::Vec<int, 2>> coordinates, std::map<int, cv::Vec3b> rgb )
{
  bool d_same = true;
  cv::Vec2i _coordinates;
  cv::Vec3i _rgb;
  std::map<int, cv::Vec2i>::const_iterator coord_it = coordinates.cbegin();

  for( auto rgb_it = rgb.cbegin(), d_rgb_it = d_pixel_rgb.cbegin();
            rgb_it != rgb.cend(), d_rgb_it != d_pixel_rgb.cend(); rgb_it++, d_rgb_it++ )
  {
    _rgb(0) += (*rgb_it).second(0);
    _rgb(1) += (*rgb_it).second(1);
    _rgb(2) += (*rgb_it).second(2);
  }

  for( auto coodr_it = coordinates.begin(); coord_it != coordinates.cend(); coord_it++ )
  {
    _coordinates(0) += (*coord_it).second(0);
    _coordinates(1) += (*coord_it).second(1);
  }

  d_rgb = _rgb / (int)rgb.size();
  d_coordinates = _coordinates / (int)coordinates.size();
}

} // end namespace centroid.

} // end namespace scv.
