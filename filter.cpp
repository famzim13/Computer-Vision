// filter.cpp
#include "filter.hpp"

namespace scv
{

namespace filter
{

// CONSTRUCTORS
Filter::Filter()
{
  Filter( 1.0 );
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
cv::Mat Filter::gaussian( cv::Mat image, int space )
{
  cv::Mat blur = directionFilter( image, d_kernel, 0 );
  return setSpace( directionFilter( blur, d_kernel, 1 ), space );
}

cv::Mat Filter::filter( cv::Mat image, std::vector<float> kernel, int direction, int space )
{
  return setSpace( directionFilter( image, kernel, direction ), space );
}

// MEMBER FUNCTIONS
int Filter::boundCheck( int bound, int position )
{
  return position < 0?0:position > bound?bound:position;
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
  cv::Mat filtered = cv::Mat( image.rows, image.cols, CV_8UC3 );
  int kernel_half = floor( filter.size() / 2 );
  int x1, y1 = 0;

  for( int x = 0; x < image.rows; x++ )
  {
    for( int y = 0; y < image.cols; y++ )
    {
      float r_value, b_value, g_value = 0.0;
      for( int i = -kernel_half; i <= kernel_half; i++ )
      {
        if( direction == 0 )
        {
          x1 = boundCheck( image.rows, i+x );
          y1 = y;
        } else
        {
          x1 = x;
          y1 = boundCheck( image.cols, i+y );
        }
        cv::Vec3b pixel = image.at<cv::Vec3b>( x1, y1 );
        r_value += pixel(0) * filter[i+kernel_half];
        g_value += pixel(1) * filter[i+kernel_half];
        b_value += pixel(2) * filter[i+kernel_half];
      }
      filtered.at<cv::Vec3b>( x, y ) = cv::Vec3b( r_value, g_value, b_value );
    }
  }

  return filtered;
}

cv::Mat Filter::setSpace( cv::Mat image, int space )
{
  if( space )
  {
    return image;
  }

  cv::Mat spaced = cv::Mat( image.rows, image.cols, CV_8U );

  for( int x=0; x<image.rows; x++ )
  {
    for( int y=0; y<image.cols; y++ )
    {
      spaced.at<uchar>( x, y ) = image.at<cv::Vec3b>( x, y )(0);
    }
  }

  return spaced;
}

} // end namespace filter.

} // end namespace scv.
