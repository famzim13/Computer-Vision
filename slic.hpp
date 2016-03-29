// slic.hpp
#ifndef INCLUDED_SLIC
#define INCLUDED_SLIC

#include "centroid.hpp"
#include "filter.hpp"

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

    int d_super_x;
      // X dimensional size of super pixel.

    int d_super_y;
      // Y dimensional size of super pixel.

    std::vector<

    filter::Filter d_filter;
      // Filter object for the SLIC.

    // MEMBER FUNCTIONS
    void getSmallestMagnitude( int x_start, int x_end, int y_start, int y_end );
      // Get the smallest 3x3 area in the superpixel.

  public:
    // CONSTRUCTORS
    SLIC( cv::Mat image );
      // Constructor with image input.

    SLIC( cv::Mat image, float sigma );
      // Constructor with image and sigma input.

    SLIC( cv::Mat image, int super_x, int super_y );
      // Constructor with image and super pixel size input.

    SLIC( cv::Mat image, int super_x, int super_y, float sigma );
      // Constructor with image, super pixel size, and sigma.

    // DESTRUCTORS
    ~SLIC();
      // Default destructor.

    // MUTATORS
    void setImage( cv::Mat image );
      // Changes the image.

    void setSize( int super_x, int super_y );
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
