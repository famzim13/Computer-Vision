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
  d_num_clusters = ceil( image.rows / d_size ) * ceil( image.cols / d_size );
}

SLIC::SLIC( cv::Mat image, float sigma )
{
  d_image = image;
  d_filter = filter::Filter( sigma );
  d_size = 50;
  d_num_clusters = ceil( image.rows / d_size ) * ceil( image.cols / d_size );
}

SLIC::SLIC( cv::Mat image, int size )
{
  d_image = image;
  d_filter = filter::Filter();
  d_size = size;
  d_num_clusters = ceil( image.rows / d_size ) * ceil( image.cols / d_size );
}

SLIC::SLIC( cv::Mat image, int size, float sigma )
{
  d_image = image;
  d_filter = filter::Filter( sigma );
  d_size = size;
  d_num_clusters = ceil( image.rows / d_size ) * ceil( image.cols / d_size );
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
  assignSuperPixels();
  setCentroids();
  int count = 0;

  do
  {
    std::cout << count << '\n';
    count++;

    cv::Vec3b rgb;
    int nearest;
    d_old_super_pixels = d_super_pixels.clone();

    for( int x=0; x<d_image.rows; x++ )
    {
      for( int y=0; y<d_image.cols; y++ )
      {
        rgb = d_image.at<cv::Vec3b>( x, y );
        nearest = nearestCentroid( cv::Vec<int, 2>( x, y ), rgb );
        d_super_pixels.at<uchar>( x, y ) = nearest;
      }
    }
    cv::imwrite( std::to_string(count)+"_slic.png", slicImage() );
    updateSuperPixels();
  } while( !converged() );

  return slicImage();
}

// MEMBER FUNCTIONS
void SLIC::assignSuperPixels()
{
  d_super_pixels = cv::Mat( d_image.rows, d_image.cols, CV_8U );
  int per_row = d_image.rows / d_size;

  for( int x=0; x<d_image.rows; x++ )
  {
    for( int y=0; y<d_image.cols; y++ )
    {
      d_super_pixels.at<uchar>( x, y ) = ( y / d_size ) + ( per_row * ( x / d_size ) );
    }
  }
}

int SLIC::boundsCheck( int bounds, int position )
{
  return position < 0?0:position > bounds?bounds:position;
}

bool SLIC::boundary( int x, int y )
{
  int surrounding = ( d_super_pixels.at<uchar>( boundsCheck( d_image.rows, x+1 ), y )
    + d_super_pixels.at<uchar>( boundsCheck( d_image.rows, x-1 ), y )
    + d_super_pixels.at<uchar>( x, boundsCheck( d_image.cols, y-1 ) )
    + d_super_pixels.at<uchar>( x, boundsCheck( d_image.cols, y+1 ) ) ) / 4;

  return surrounding != d_super_pixels.at<uchar>( x, y )?true:false;
}

bool SLIC::converged()
{
  return std::equal( d_super_pixels.begin<uchar>(),
                     d_super_pixels.end<uchar>(),
                     d_old_super_pixels.begin<uchar>() );
}

void SLIC::getSmallestMagnitude( int x_start, int x_end, int y_start, int y_end )
{

}

int SLIC::nearestCentroid( cv::Vec<int, 2> coordinates, cv::Vec3b pixel )
{
  int nearest_centroid = -1;
  float nearest_distance = INFINITY;
  for( int i=0; i<d_centroids.size(); i++ )
  {
    if( d_centroids[i].distance( coordinates ) >= 2*d_size )
    {
      continue;
    }

    float distance = d_centroids[i].distance( coordinates, pixel );

    if( distance < nearest_distance )
    {
      nearest_distance = distance;
      nearest_centroid = i;
    }

  }

  return nearest_centroid;
}

void SLIC::setCentroids()
{
  for( int x=0; x<d_image.rows; x += d_size )
  {
    for( int y=0; y<d_image.cols; y += d_size )
    {
      int i = x + ( boundsCheck( d_image.rows, x+d_size ) - x ) / 2;
      int j = y + ( boundsCheck( d_image.cols, y+d_size ) - y ) / 2;
      cv::Vec3b rgb = d_image.at<cv::Vec3b>( i, j );

      d_centroids.push_back( centroid::Centroid( cv::Vec<int, 2>( i, j ), rgb ) );
    }
  }
}

cv::Mat SLIC::slicImage()
{
  cv::Mat image = cv::Mat( d_image.rows, d_image.cols, d_image.type() );

  for( int x=0; x<image.rows; x++ )
  {
    for( int y=0; y<image.cols; y++ )
    {
      image.at<cv::Vec3b>( x, y ) = boundary( x, y )?0:d_image.at<cv::Vec3b>( x, y );
    }
  }

  for( int i=0; i<d_num_clusters; i++ )
  {
    cv::Vec<int, 2> coordinate = d_centroids[i].getCoordinates();
    image.at<cv::Vec3b>( coordinate(0), coordinate(1) ) = 255-i;
  }

  return image;
}

void SLIC::updateSuperPixels()
{
  std::vector<cv::Vec<int, 2>> coordinates;
  std::vector<cv::Vec3b> rgb;

  for( int i=0; i<d_num_clusters; i++ )
  {
    for( int x=0; x<d_image.rows; x++ )
    {
      for( int y=0; y<d_image.cols; y++ )
      {
        if( i == d_super_pixels.at<uchar>( x, y ) )
        {
          coordinates.push_back( cv::Vec<int, 2>( x, y ) );
          rgb.push_back( d_image.at<cv::Vec3b>( x, y ) );
        }
      }
    }

    d_centroids[i].update( coordinates, rgb );
    coordinates.clear();
    rgb.clear();
  }
}

} // end namespace slic.

} // end namespace scv.
