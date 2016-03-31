// kmeans.cpp
#include "kmeans.hpp"

namespace scv
{

namespace kmeans
{

// CONSTRUCTORS
/*
 * BUILDS: Builds a kmeans object with a default number of clusters.
 */
KMeans::KMeans( cv::Mat image )
{
  d_image = image;
  d_clustered = cv::Mat( image.rows, image.cols, CV_8U );
  d_num_clusters = 10;
  d_coords = std::vector<std::map<int, cv::Vec<int, 2>>>( d_num_clusters );
  d_rgb = std::vector<std::map<int, cv::Vec3b>>( d_num_clusters );
}

/*
 * BUILDS: Builds a kmeans object with a specified number of clusters.
 */
KMeans::KMeans( cv::Mat image, int num_clusters )
{
  d_image = image;
  d_clustered = cv::Mat( image.rows, image.cols, CV_8U );
  d_num_clusters = num_clusters;
  d_coords = std::vector<std::map<int, cv::Vec<int, 2>>>( d_num_clusters );
  d_rgb = std::vector<std::map<int, cv::Vec3b>>( d_num_clusters );
}

// DESTRUCTORS
/*
 * DESTROYS: Destroys the kmeans object.
 */
KMeans::~KMeans()
{

}

// MUTATORS
/*
 * INPUT: Image.
 * RESULT: Changes the kmeans image.
 */
void KMeans::setImage( cv::Mat image )
{
  d_image = image;
}

/*
 * INPUT: Number of clusters.
 * RESULT: Changes the number of clusters.
 */
void KMeans::setNumClusters( int num_clusters )
{
  d_num_clusters = num_clusters;
}

// FREE OPERATORS
/*
 * OPERATION: Perform kmeans on the image.
 * RESULT: Converged image of kmeans.
 */
cv::Mat KMeans::perform()
{
  bool converged;
  int nearest, old_nearest, key;
  setCentroids();
  setMaps();

  do
  {
    converged = true;

    for( int x=0; x<d_image.rows; x++ )
    {
      for( int y=0; y<d_image.cols; y++ )
      {
        nearest = nearestCentroid( d_image.at<cv::Vec3b>( x, y ) );
        old_nearest = d_clustered.at<uchar>( x, y );
        if( nearest != old_nearest )
        {
          converged = false;
          d_clustered.at<uchar>( x, y ) = nearest;
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

  } while( !converged );

  return kmeansImage();
}

// MEMBER FUNCTIONS
cv::Mat KMeans::kmeansImage()
{
  cv::Mat image = cv::Mat( d_image.rows, d_image.cols, d_image.type() );

  for( int i=0; i<d_num_clusters; i++ )
  {
    cv::Vec3b rgb = d_centroids[i].getRGB();
    std::map<int, cv::Vec<int, 2>>::const_iterator coord_it = d_coords[i].cbegin();
    for( ; coord_it != d_coords[i].cend(); coord_it++ )
    {
      image.at<cv::Vec3b>( (*coord_it).second(0), (*coord_it).second(1) ) = rgb;
    }
  }

  return image;
}

int KMeans::mapCoordinates( int x, int y )
{
  return x >= y?x * x + x + y:x + y * y;
}

int KMeans::nearestCentroid( cv::Vec3b pixel )
{
  int nearest_centroid = -1;
  float nearest_distance = INFINITY;
  for( int i=0; i<d_num_clusters; i++ )
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
      d_centroids.push_back( centroid::Centroid( cv::Vec<int, 2>( x, y ), pixel ) );
      selected++;
    }

    add = true;
  }
}

void KMeans::setMaps()
{
  for( int x=0; x<d_image.rows; x++ )
  {
    for( int y=0; y<d_image.cols; y++ )
    {
      int nearest = nearestCentroid( d_image.at<cv::Vec3b>( x, y ) );
      int key = mapCoordinates( x, y );
      cv::Vec<int, 2> coord = cv::Vec<int, 2>( x, y );
      cv::Vec3b pixel = d_image.at<cv::Vec3b>( x, y );
      d_coords[nearest].insert( std::make_pair( key, coord ) );
      d_rgb[nearest].insert( std::make_pair( key, pixel ) );
    }
  }
}

void KMeans::updateCentroids()
{
  for( int i=0; i<d_num_clusters; i++ )
  {
    d_centroids[i].update( d_rgb[i] );
  }
}

} // end namespace kmeans.

} // end namespace scv.
