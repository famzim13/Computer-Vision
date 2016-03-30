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
    d_old_clustered = d_clustered.clone();
    cv::MatIterator_<uchar> cluster_it = d_clustered.begin<uchar>();
    cv::MatConstIterator_<cv::Vec3b> image_it = d_image.begin<cv::Vec3b>();

    for( ; cluster_it != d_clustered.end<uchar>(); cluster_it++, image_it++ )
    {
      *cluster_it = nearestCentroid( *image_it );
    }

    updateCentroids();
  } while( !converged( d_old_clustered ) );

  return kmeansImage();
}

// MEMBER FUNCTIONS
bool KMeans::converged( cv::Mat clustered )
{
  return std::equal( d_clustered.begin<uchar>(),
                    d_clustered.end<uchar>(),
                    clustered.begin<uchar>() );
}

cv::Mat KMeans::kmeansImage()
{
  cv::Mat image = cv::Mat( d_image.rows, d_image.cols, d_image.type() );
  cv::MatIterator_<cv::Vec3b> image_it = image.begin<cv::Vec3b>();
  cv::MatConstIterator_<uchar> cluster_it = d_clustered.begin<uchar>();

  for( ; cluster_it != d_clustered.end<uchar>(); image_it++, cluster_it++ )
  {
    *image_it = d_centroids[*cluster_it].getRGB();
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
  bool add = true;
  int selected = 0;
  srand( time( NULL ) );

  while( selected != d_num_clusters )
  {
    int x = rand() % d_image.rows;
    int y = rand() % d_image.cols;
    cv::Vec3b pixel = d_image.at<cv::Vec3b>( x, y );

    for( int i=0; i<d_centroids.size(); i++ )
    {
      if( d_centroids[i].getRGB() == pixel )
      {
        add = false;
      }
    }

    if( add )
    {
      d_centroids.push_back( centroid::Centroid( cv::Vec2b( x, y ), pixel ) );
      selected++;
    }

    add = true;
  }
}

void KMeans::updateCentroids()
{
  std::vector<cv::Vec3b> pixels;
  std::vector<centroid::Centroid> centroids;

  for( int i=0; i<d_num_clusters; i++ )
  {
    cv::MatConstIterator_<uchar> cluster_it = d_clustered.begin<uchar>();
    cv::MatConstIterator_<cv::Vec3b> image_it = d_image.begin<cv::Vec3b>();
    for( ; cluster_it != d_clustered.end<uchar>(); cluster_it++, image_it++ )
    {
      if( *cluster_it == i )
      {
        pixels.push_back( *image_it );
      }
    }

    d_centroids[i].update( pixels );
    pixels.clear();
  }
}

} // end namespace kmeans.

} // end namespace scv.
