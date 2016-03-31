// filter.hpp
#ifndef INCLUDED_FILTER
#define INCLUDED_FILTER

#include <cmath>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

namespace scv
{

namespace filter
{

  class Filter
  {
    private:
      std::vector<float> d_kernel;
        // Gaussian kernel.

      float d_sigma;
        // Gaussian sigma.

      // MEMBER FUNCTIONS
      int boundCheck( int bound, int position );
        // Checks the bounds of the pixel.

      void buildKernel( float sigma );
        // Creates Gaussian kernel.

      cv::Mat directionFilter( cv::Mat image, std::vector<float> filter, int direction );
        // Filters the image with a one dimension filter in either x or y direction.

    public:
      // CONSTRUCTORS
      Filter();
        // Default constructor.

      Filter( float sigma );
        // Constructor with sigma input.

      // DESTRUCTORS
      ~Filter();

      // MUTATORS
      void setSigma( float sigma );
        // Set the sigma value for the filter.

      // FREE OPERATORS
      cv::Mat gaussian( cv::Mat image );
        // Performs a Gaussian filter on the input image.

      cv::Mat filter( cv::Mat image, std::vector<float> kernel, int direction );
        // Performs a filtering of the image with the given kernel.

  };

} // end namespace filter.

} // end namspeace scv.

#endif
