// histogram_knn.cpp
#include "histogram_knn.hpp"

namespace scv
{

namespace histogram_knn
{

// CONSTRUCTOR
HistogramKNN::HistogramKNN()
{
  d_buckets = 8;
  d_groups = std::map<std::string, histogram_group::HistogramGroup>();
  d_knn = 1;
  d_space = 3;
  d_training_images = std::vector<std::string>();
}

HistogramKNN::HistogramKNN( int buckets, int knn )
{
  d_buckets = buckets;
  d_groups = std::map<std::string, histogram_group::HistogramGroup>();
  d_knn = knn;
  d_space = 3;
  d_training_images = std::vector<std::string>();
}

// DESTRUCTOR
HistogramKNN::~HistogramKNN()
{

}

// MUTATORS
void HistogramKNN::addImage( std::string training )
{
  d_training_images.push_back( training );
}

void HistogramKNN::addImages( std::vector<std::string> training )
{
  d_training_images.insert( d_training_images.end(), training.begin(), training.end() );
}

// FREE OPERATORS
std::string HistogramKNN::classifyImage( std::string classify )
{
  std::map<float, std::string> all_distances = std::map<float, std::string>();
  std::map<float, std::string> distances = std::map<float, std::string>();
  cv::Mat image = cv::imread( classify );
  histogram::Histogram hist = buildHistogram( image );

  for( auto it = d_groups.begin(); it != d_groups.end(); it++ )
  {
    distances = (it->second).getDistances( hist );
    all_distances.insert( distances.begin(), distances.end() );
  }

  return all_distances.begin()->second;
}

std::vector<std::string> HistogramKNN::classifyImages( std::vector<std::string> classify )
{

}

void HistogramKNN::train()
{
  std::string group;
  std::vector<cv::Mat> images = loadImages();

  for( int i=0; i<images.size(); i++ )
  {
    group = getGroup( d_training_images[i] );
    if( ( auto it = d_groups.find( group ) ) != d_groups.end() )
    {
      d_groups[group].addHistogram( buildHistogram( cv::Mat ) );
    } else
    {
      d_groups[group] = histogram_group::HistogramGroup( group );
      d_groups[group].addHistogram( buildHistogram( cv::Mat ) );
    }
  }

}

// MEMBER FUNCTIONS
histogram::Histogram HistogramKNN::buildHistogram( cv::Mat image )
{
  histogram::Histogram hist = histogram::Histogram( d_buckets, d_space );

  for( int x=0; x<image.rows; x++ )
  {
    for( int y=0; y<image.cols; y++ )
    {
      newHist.insertPixel( image.at<cv::Vec3b>( x, y ) );
    }
  }

  return hist;
}

std::string HistogramKNN::getGroup( std::string filename )
{

}

std::vector<cv::Mat> HistogramKNN::loadImages()
{
  std::vector<cv::Mat> images = std::vector<cv::Mat>();

  for( int i=0; i<d_training_images.size(); i++ )
  {
    images.push_back( cv::imread( d_training_images[i] ) );
  }

  return images;
}

} // end namepsace histogram_knn.

} // end namespace scv.
