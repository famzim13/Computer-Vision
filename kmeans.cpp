// kmeans.cpp
#include "kmeans.hpp"

namespace scv
{

namespace kmeans
{

// CONSTRUCTORS
KMeans::KMeans( cv::Mat image )
{
  d_image = image;
  d_clustered = cv::Mat( image.rows, image.cols, CV_8U );
  d_num_clusters = 10;
}

KMeans::KMeans( cv::Mat image, int num_clusters )
{
  d_image = image;
  d_clustered = cv::Mat( image.rows, image.cols, CV_8U );
  d_num_clusters = num_clusters;
}

// DESTRUCTORS
KMeans::~KMeans()
{

}

// MUTATORS
void KMeans::setImage( cv::Mat image )
{
  d_image = image;
}

void KMeans::setNumClusters( int num_clusters )
{
  d_num_clusters = num_clusters;
}

// FREE OPERATORS
cv::Mat KMeans::perform()
{
  setCentroids();

  do
  {
    d_old_clustered = d_clustered;
    updateCentroids();

    for( int x=0; x<d_image.rows; x++ )
    {
      for( int y=0; y<d_image.cols; y++ )
      {
        d_clustered.at<uchar>( x, y ) = nearestCentroid( d_image.at<cv::Vec3b>( x, y ) );
      }
    }
  }
  while( !converged( d_old_clustered ) );

  return kmeansImage();
}

// MEMBER FUNCTIONS
bool KMeans::converged( cv::Mat clustered )
{
  return std::equal( d_clustered.begin<uchar>(), d_clustered.end<uchar>(), clustered.begin<uchar>() );
}

cv::Mat KMeans::kmeansImage()
{
  cv::Mat image = cv::Mat( d_image.rows, d_image.cols, d_image.type() );

  for( int x=0; x<image.rows; x++ )
  {
    for( int y=0; y<image.cols; y++ )
    {
      image.at<cv::Vec3b>( x, y ) = d_centroids[d_clustered.at<uchar>( x, y )].getRGB();
    }
  }

  return image;
}

int KMeans::nearestCentroid( cv::Vec3b pixel )
{
  int nearest_centroid = -1;
  float nearest_distance = INFINITY;
  for( int i=0; i<d_centroids.size(); i++ )
  {
    float distance = d_centroids[i].distance( pixel );

    if( distance < nearest_distance )
    {
      nearest_distance = distance;
      nearest_centroid = i;
    }

  }

  return nearest_centroid;
}

void KMeans::setCentroids()
{
  int selected = 0;
  cv::Mat selectedMatrix = cv::Mat::zeros( d_image.rows, d_image.cols, CV_8U );

  srand( time( NULL ) );

  while( selected != d_num_clusters )
  {
    int x = rand() % d_image.rows;
    int y = rand() % d_image.cols;

    if( selectedMatrix.at<uchar>( x, y ) )
    {
      continue;
    }

    d_centroids.push_back( centroid::Centroid( cv::Vec2b( x, y ), d_image.at<cv::Vec3b>( x, y ) ) );
    selectedMatrix.at<uchar>( x, y ) = 1;
    selected++;
  }
}

void KMeans::updateCentroids()
{
  for( int i=0; i<d_num_clusters; i++ )
  {
    std::vector<cv::Vec3b> pixels;
    for( int x=0; x<d_image.rows; x++ )
    {
      for( int y=0; y<d_image.cols; y++ )
      {
        if( d_clustered.at<uchar>( x, y ) == i )
        {
          pixels.push_back( d_image.at<cv::Vec3b>( x, y ) );
        }
      }
    }
  }
}

} // end namespace kmeans.

} // end namespace scv.
