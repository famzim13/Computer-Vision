// centroid.hpp
#ifndef INCLUDED_CENTROID
#define INCLUDED_CENTROID

#include <cmath>
#include <iostream>
#include <map>
#include <opencv/cv.h>
#include <opencv/highgui.h>

namespace scv
{

namespace centroid
{

class Centroid
{
  private:
    cv::Vec2i d_coordinates;
      // Centroid coordinates.

    cv::Vec3b d_rgb;
      // Centroid color.

    std::map<int, cv::Vec2i> d_pixel_coordinates;
      // Coordinates of pixels owned by the centroid.

    std::map<int, cv::Vec3b> d_pixel_rgb;
      // RGBs of pixels owned by the centroid.

  public:
    //CONSTRUCTORS
    Centroid( cv::Vec2i coordinates, cv::Vec3b rgb );
      // Consturctor with coordinates of the centroid and color.

    // DESTRUCTORS
    ~Centroid();
      // Default destructor.

    // ACCESSORS
    cv::Vec2i getCoordinates();
      // Returns the x,y coordinate of the centroid.

    cv::Vec3b getRGB();
      // Returns the rgb value of the centroid.

    // MUTATORS
    void addCoordinate( int key, cv::Vec2i coordinate );
      // Adds coordinate to coordinates map.

    void addRGB( int key, cv::Vec3b rgb );
      // Adds RGB to RGB map.

    void removeCoordinate( int key );
      // Remove coordinate from coordinate map.

    void removeRGB( int key );
      // Remove RGB from RGB map.

    // FREE OPERATORS
    float distance( cv::Vec2i coordinates );
      // Calculates cartesian distance between pixel and centroid.

    float distance( cv::Vec3b rgb );
      // Calculates the color similarity between centroid and pixel.

    float distance( cv::Vec2i coordinates, cv::Vec3b rgb, float range );
      // Calculates the magnitude of color and distance between centroid and pixel.

    void update();
      // Updates the centroids rgb value.

    void update( std::map<int, cv::Vec2i> coordinates, std::map<int, cv::Vec3b> rgb );
      // Updates the centroids rgb and coordinate values.

};

} // end namespace centroid.

} // end namespace scv.

#endif
