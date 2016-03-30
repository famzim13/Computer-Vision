// main.cpp

#include "centroid.hpp"
#include "filter.hpp"
#include "kmeans.hpp"
#include "slic.hpp"

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <stdlib.h>

int main( int argc, char** argv )
{
  if( argc != 6 )
  {
    std::cout << "Not enough arguments\n";
    return -1;
  }

  int num_clusters = atoi( argv[1] );
  cv::Mat kmeans_image = cv::imread( argv[2] );
  int pixel_size = atoi( argv[3] );
  cv::Mat slic_image = cv::imread( argv[4] );
  float sigma = atof( argv[5] );

  scv::kmeans::KMeans clustered = scv::kmeans::KMeans( kmeans_image, num_clusters );
  std::string filename = std::to_string( num_clusters ).append( "_kmeans_" ).append( argv[2] );
  cv::imwrite( filename, clustered.perform() );

  scv::slic::SLIC super_pixels = scv::slic::SLIC( slic_image, pixel_size, sigma );
  filename = std::to_string( pixel_size ).append( "_slic_" ).append( argv[4] );
  cv::imwrite( filename, super_pixels.perform() );

  return 0;
}
