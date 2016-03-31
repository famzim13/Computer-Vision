// centroid.hpp
#ifndef INCLUDED_CENTROID
#define INCLUDED_CENTROID

#include <cmath>
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
    cv::Vec<int, 2> d_coordinates;
      // Centroid coordinates.

    cv::Vec<int, 3> d_rgb;
      // Centroid color.

  public:
    //CONSTRUCTORS
    Centroid( cv::Vec<int, 2> coordinates, cv::Vec3b rgb );
      // Consturctor with coordinates of the centroid and color.

    // DESTRUCTORS
    ~Centroid();
      // Default destructor.

    // ACCESSORS
    cv::Vec<int, 2> getCoordinates();
      // Returns the x,y coordinate of the centroid.

    cv::Vec3b getRGB();
      // Returns the rgb value of the centroid.

    // FREE OPERATORS
    float distance( cv::Vec<int, 2> coordinates );
      // Calculates cartesian distance between pixel and centroid.

    float distance( cv::Vec3b rgb );
      // Calculates the color similarity between centroid and pixel.

    float distance( cv::Vec<int, 2> coordinates, cv::Vec3b rgb );
      // Calculates the magnitude of color and distance between centroid and pixel.

    void update( std::map<int, cv::Vec3b> rgb );
      // Updates the centroids rgb value.

    void update( std::map<int, cv::Vec<int, 2>> coordinates, std::map<int, cv::Vec3b> rgb );
      // Updates the centroids rgb and coordinate values.

};

} // end namespace centroid.

} // end namespace scv.

#endif
