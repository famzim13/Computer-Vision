// slic.cpp
#include "slic.hpp"

namespace scv
{

namespace slic
{

// CONSTRUCTORS
SLIC::SLIC( cv::Mat image )
{
  d_image = image;
  d_filter = filter::Filter();
  d_size = 50;
}

SLIC::SLIC( cv::Mat image, float sigma )
{
  d_image = image;
  d_filter = filter::Filter( sigma );
  d_size = 50;
}

SLIC::SLIC( cv::Mat image, int size )
{
  d_image = image;
  d_filter = filter::Filter();
  d_size = size;
}

SLIC::SLIC( cv::Mat image, int size, float sigma )
{
  d_image = image;
  d_filter = filter::Filter( sigma );
  d_size = size;
}

// DESTRUCTORS
SLIC::~SLIC()
{

}

// MUTATORS
void SLIC::setImage( cv::Mat image )
{
  d_image = image;
}

void SLIC::setSize( int size )
{
  d_size = size;
}

void SLIC::setSigma( float sigma )
{
  d_filter.setSigma( sigma );
}

// FREE OPERATORS
cv::Mat SLIC::perform()
{

}

// MEMBER FUNCTIONS
void SLIC::assignSuperPixels()
{
  cv::Mat super_pixels( d_image.rows, d_image.cols, CV_8U );
  int per_row = d_image.rows / d_size;

  for( int x=0; x<d_image.rows; x++ )
  {
    for( int y=0; y<d_image.cols; y++ )
    {
      super_pixels.at<uchar>( x, y ) = ( x / d_size ) + ( per_row * ( y / d_size ) );
    }
  }

  d_super_pixels = super_pixels;
}

int SLIC::boundsCheck( int bounds, int position )
{
  return position < 0?0:position > bounds?bounds:position;
}

bool SLIC::converged( cv::Mat super_pixels )
{
  return std::equal( d_super_pixels.begin<uchar>(),
                     d_super_pixels.end<uchar>(),
                     super_pixels.begin<uchar>() );
}

void SLIC::getSmallestMagnitude( int x_start, int x_end, int y_start, int y_end )
{

}

int SLIC::nearestCentroid( cv::Vec2b coordinates, cv::Vec3b pixel )
{
  int nearest_centroid = -1;
  float nearest_distance = INFINITY;
  for( int i=0; i<d_centroids.size(); i++ )
  {
    float distance = d_centroids[i].distance( coordinates, pixel );

    if( distance < nearest_distance )
    {
      nearest_distance = distance;
      nearest_centroid = i;
    }

  }

  return nearest_centroid;
}

cv::Mat SLIC::slicImage()
{

}

void SLIC::updateSuperPixels()
{

}

} // end namespace slic.

} // end namespace scv.
