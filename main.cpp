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
#include <time.h>

int main( int argc, char** argv )
{
  if( argc != 5 )
  {
    std::cout << "Not enough arguments\n";
    return -1;
  }

  int num_clusters = atoi( argv[1] );
  cv::Mat kmeans_image = cv::imread( argv[2] );
  if( kmeans_image.empty() )
  {
    std::cout << "Input image for kmeans does not exist\n";
    return -1;
  }

  int pixel_size = atoi( argv[3] );
  cv::Mat slic_image = cv::imread( argv[4] );
  if( slic_image.empty() )
  {
    std::cout << "Input image for SLIC does not exist\n";
    return -1;
  }

  scv::kmeans::KMeans clustered = scv::kmeans::KMeans( kmeans_image, num_clusters );
  std::string filename = std::to_string( num_clusters ).append( "_kmeans_" ).append( argv[2] );

  clock_t start = clock();
  clock_t end = clock();
  double speed = ( end - start ) / (double)CLOCKS_PER_SEC;

  scv::slic::SLIC super_pixels = scv::slic::SLIC( slic_image, pixel_size );
  filename = std::to_string( pixel_size ).append( "_slic_" ).append( argv[4] );
  start = clock();
  cv::imwrite( filename, super_pixels.perform() );
  end = clock();
  speed = ( end - start ) / (double)CLOCKS_PER_SEC;
  std::cout << "SLIC took " << speed << "s to complete\n";

  return 0;
}
