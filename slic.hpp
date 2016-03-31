// slic.hpp
#ifndef INCLUDED_SLIC
#define INCLUDED_SLIC

#include "centroid.hpp"
#include "filter.hpp"

#include <cmath>
#include <iostream>
#include <map>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

namespace scv
{

namespace slic
{

class SLIC
{
  private:
    cv::Mat d_image;
      // Image to perform SLIC on.

    cv::Mat d_result;
      // Result of the last SLIC performance.

    cv::Mat d_pixels;
      // Image of super pixel assignments.

    int d_size;
      // Dimensional size of super pixel.

    int d_num_clusters;
      // Number of super pixels.

    std::vector<centroid::Centroid> d_centroids;
      // List of centroids for the super pixels.

    std::vector<std::map<int, cv::Vec<int, 2>>> d_coords;
      // Map of centroid pixel coordinates.

    std::vector<std::map<int, cv::Vec3b>> d_rgb;
      // Map of centroid pixel rgbs.

    filter::Filter d_filter;
      // Filter object for the SLIC.

    // MEMBER FUNCTIONS
    void assignPixels();
      // Assigns the super pixels.

    int boundsCheck( int bounds, int position );
      // Bounds the pixel coordinates.

    bool boundary( int x, int y );
      // Returns whether or not a pixel is a boundary.

    void getSmallestMagnitude( int x_start, int x_end, int y_start, int y_end );
      // Get the smallest 3x3 area in the superpixel.

    int mapCoordinates( int x, int y );
      // Converts pixel coordinates into a single integer.

    int nearestCentroid( cv::Vec<int, 2> coordinates, cv::Vec3b pixel );
      // Calculates nearest centroid for the pixel.

    void setCentroids();
      // Build the array of centroids.

    void setMap();
      // Builds the initial maps.

    cv::Mat slicImage();
      // Returns image that SLIC has computed.

    void updatePixels();
      // Updates super pixels for each iteration.

  public:
    // CONSTRUCTORS
    SLIC( cv::Mat image );
      // Constructor with image input.

    SLIC( cv::Mat image, float sigma );
      // Constructor with image and sigma input.

    SLIC( cv::Mat image, int size );
      // Constructor with image and super pixel size input.

    SLIC( cv::Mat image, int size, float sigma );
      // Constructor with image, super pixel size, and sigma.

    // DESTRUCTORS
    ~SLIC();
      // Default destructor.

    // MUTATORS
    void setImage( cv::Mat image );
      // Changes the image.

    void setSize( int size );
      // Changes the size of the super pixel.

    void setSigma( float sigma );
      // Set the sigma value of the filter.

    // FREE OPERATORS
    cv::Mat perform();
      // Run SLIC.
};

} // end namespace slic.

} // end namespace scv.
#endif
