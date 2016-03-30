// slic.hpp
#ifndef INCLUDED_SLIC
#define INCLUDED_SLIC

#include "centroid.hpp"
#include "filter.hpp"

#include <cmath>
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

    cv::Mat d_super_pixels;
      // Image of super pixel assignments.

    cv::Mat d_old_super_pixels;
      // Image of previous super pixel assignments.

    int d_size;
      // Dimensional size of super pixel.

    std::vector<centroid::Centroid> d_centroids;
      // List of centroids for the super pixels.

    filter::Filter d_filter;
      // Filter object for the SLIC.

    // MEMBER FUNCTIONS
    void assignSuperPixels();
      // Assigns the super pixels.

    int boundsCheck( int bounds, int position );
      // Bounds the pixel coordinates.

    bool converged( cv::Mat super_pixels );
      // Checks if SLIC has converged.

    void getSmallestMagnitude( int x_start, int x_end, int y_start, int y_end );
      // Get the smallest 3x3 area in the superpixel.

    int nearestCentroid( cv::Vec2b coordinates, cv::Vec3b pixel );
      // Calculates nearest centroid for the pixel.

    cv::Mat slicImage();
      // Returns image that SLIC has computed.

    void updateSuperPixels();
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
