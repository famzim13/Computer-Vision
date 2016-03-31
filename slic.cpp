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
  d_coords = std::vector<std::map<int, cv::Vec<int, 2>>>( d_num_clusters );
  d_rgb = std::vector<std::map<int, cv::Vec3b>>( d_num_clusters );
}

SLIC::SLIC( cv::Mat image, float sigma )
{
  d_image = image;
  d_filter = filter::Filter( sigma );
  d_size = 50;
  d_num_clusters = ceil( image.rows / d_size ) * ceil( image.cols / d_size );
  d_coords = std::vector<std::map<int, cv::Vec<int, 2>>>( d_num_clusters );
  d_rgb = std::vector<std::map<int, cv::Vec3b>>( d_num_clusters );
}

SLIC::SLIC( cv::Mat image, int size )
{
  d_image = image;
  d_filter = filter::Filter();
  d_size = size;
  d_num_clusters = ceil( image.rows / d_size ) * ceil( image.cols / d_size );
  d_coords = std::vector<std::map<int, cv::Vec<int, 2>>>( d_num_clusters );
  d_rgb = std::vector<std::map<int, cv::Vec3b>>( d_num_clusters );
}

SLIC::SLIC( cv::Mat image, int size, float sigma )
{
  d_image = image;
  d_filter = filter::Filter( sigma );
  d_size = size;
  d_num_clusters = ceil( image.rows / d_size ) * ceil( image.cols / d_size );
  d_coords = std::vector<std::map<int, cv::Vec<int, 2>>>( d_num_clusters );
  d_rgb = std::vector<std::map<int, cv::Vec3b>>( d_num_clusters );
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
  bool converged;
  int nearest, old_nearest, key;
  assignPixels();
  setCentroids();
  setMap();

  do
  {
    converged = true;

    for( int x=0; x<d_image.rows; x++ )
    {
      for( int y=0; y<d_image.cols; y++ )
      {
        nearest = nearestCentroid( cv::Vec<int, 2>( x, y ), d_image.at<cv::Vec3b>( x, y ) );
        old_nearest = d_pixels.at<uchar>( x, y );
        if( nearest != old_nearest )
        {
          converged = false;
          d_pixels.at<uchar>( x, y ) = nearest;
          key = mapCoordinates( x, y );
          cv::Vec<int, 2> coord = cv::Vec<int, 2>( x, y );
          cv::Vec3b pixel = d_image.at<cv::Vec3b>( x, y );
          d_coords[old_nearest].erase( key );
          d_coords[nearest].insert( std::pair<int, cv::Vec<int, 2>>( key, coord ) );
          d_rgb[old_nearest].erase( key );
          d_rgb[nearest].insert( std::pair<int, cv::Vec3b>( key, pixel ) );
        }
      }
    }

    updatePixels();
  } while( !converged );

  return slicImage();
}

// MEMBER FUNCTIONS
void SLIC::assignPixels()
{
  d_pixels = cv::Mat( d_image.rows, d_image.cols, CV_8U );
  int per_row = d_image.rows / d_size;

  for( int x=0; x<d_image.rows; x++ )
  {
    for( int y=0; y<d_image.cols; y++ )
    {
      d_pixels.at<uchar>( x, y ) = ( y / d_size ) + ( per_row * ( x / d_size ) );
    }
  }
}

int SLIC::boundsCheck( int bounds, int position )
{
  return position < 0?0:position > bounds?bounds:position;
}

bool SLIC::boundary( int x, int y )
{
  int surrounding = ( d_pixels.at<uchar>( boundsCheck( d_image.rows, x+1 ), y )
    + d_pixels.at<uchar>( boundsCheck( d_image.rows, x-1 ), y )
    + d_pixels.at<uchar>( x, boundsCheck( d_image.cols, y-1 ) )
    + d_pixels.at<uchar>( x, boundsCheck( d_image.cols, y+1 ) ) ) / 4;

  return surrounding != d_pixels.at<uchar>( x, y );
}

void SLIC::getSmallestMagnitude( int x_start, int x_end, int y_start, int y_end )
{

}

int SLIC::mapCoordinates( int x, int y )
{
  return x >= y?x * x + x + y:x + y * y;
}

int SLIC::nearestCentroid( cv::Vec<int, 2> coordinates, cv::Vec3b pixel )
{
  int nearest_centroid = -1;
  float nearest_distance = INFINITY;
  for( int i=0; i<d_num_clusters; i++ )
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

void SLIC::setMap()
{
  for( int x=0; x<d_image.rows; x++ )
  {
    for( int y=0; y<d_image.cols; y++ )
    {
      int centroid = d_pixels.at<uchar>( x, y );
      int key = mapCoordinates( x, y );
      cv::Vec<int, 2> coord = cv::Vec<int, 2>( x, y );
      cv::Vec3b pixel = d_image.at<cv::Vec3b>( x, y );
      d_coords[centroid].insert( std::make_pair( key, coord ) );
      d_rgb[centroid].insert( std::make_pair( key, pixel ) );
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

  return image;
}

void SLIC::updatePixels()
{
  for( int i=0; i<d_num_clusters; i++ )
  {
    d_centroids[i].update( d_coords[i], d_rgb[i] );
  }
}

} // end namespace slic.

} // end namespace scv.
