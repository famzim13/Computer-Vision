// filter.cpp
#include "filter.hpp"

namespace scv
{

namespace filter
{

// CONSTRUCTORS
Filter::Filter()
{
  d_sigma = 1.0;
  buildKernel( d_sigma );
}

Filter::Filter( float sigma )
{
  d_sigma = sigma;
  buildKernel( d_sigma );
}

// DESTRUCTORS
Filter::~Filter()
{

}

// MUTATORS
void Filter::setSigma( float sigma )
{
  d_sigma = sigma;
}

// FREE OPERATORS
cv::Mat Filter::gaussian( cv::Mat image )
{
  cv::Mat blur = directionFilter( image, d_kernel, 0 );
  return directionFilter( blur, d_kernel, 1 );
}

cv::Mat Filter::filter( cv::Mat image, std::vector<float> kernel, int direction )
{
  return directionFilter( image, kernel, direction );
}

// MEMBER FUNCTIONS
int Filter::boundCheck( int bound, int position )
{
  return position < 0?0:position >= bound?bound-1:position;
}

void Filter::buildKernel( float sigma )
{
  float divisor = 2 * sigma * M_PI;
  int features = floor( 6 * sigma );
  features % 2 == 0 ? features++ : features += 0;
  std::vector<float> kernel( features );
  int kernel_half = floor( features / 2 );
  float kernel_normal = 0.0;

  for( int i = -kernel_half; i <= kernel_half; i++ )
  {
    float power = pow( i, 2 ) / ( 2 * pow( sigma, 2 ) );
    float value = exp( -power ) / sqrt( divisor );
    kernel[i+kernel_half] = value;
    kernel_normal += value;
  }

  for( int i = 0; i < features; i++ )
  {
    kernel[i] = kernel[i] / kernel_normal;
  }

  d_kernel = kernel;
}

cv::Mat Filter::directionFilter( cv::Mat image, std::vector<float> filter, int direction )
{
  cv::Mat filtered = cv::Mat( image.rows, image.cols, CV_32FC3 );
  int kernel_half = floor( filter.size() / 2 );
  int x1, y1;

  for( int x = 0; x < image.rows; x++ )
  {
    for( int y = 0; y < image.cols; y++ )
    {
      cv::Vec<float, 3> rgb( 0, 0, 0 );
      for( int i = -kernel_half; i <= kernel_half; i++ )
      {
        if( direction == 0 )
        {
          x1 = boundCheck( image.rows, x+i );
          y1 = y;
        } else
        {
          x1 = x;
          y1 = boundCheck( image.rows, y+i );
        }

        cv::Vec3b pixel = image.at<cv::Vec3b>( x1, y1 );
        rgb += pixel * filter[i+kernel_half];
      }

      filtered.at<cv::Vec<float, 3>>( x, y ) = rgb;
    }
  }

  return filtered;
}

} // end namespace filter.

} // end namespace scv.
