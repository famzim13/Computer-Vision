// HW4.cpp
#include "centroid.hpp"
#include "histogram_knn.hpp"
#include "kmeans.hpp"

#include <fstream>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>

int main( int argc, char** argv )
{
  if( argc != 8 )
  {
    std::cout << "Not enough arguments\n";
    return -1;
  }

  int buckets = atoi( argv[1] );
  int knn = atoi( argv[2] );
  std::string knn_training = argv[3];
  std::string knn_test = argv[4];
  int kmeans = atoi( argv[5] );
  std::string classify_train = argv[6];
  std::string classify_test = argv[7];

  // Create the KNN histogram classifier.
  auto KNN = scv::histogram_knn::HistogramKNN( buckets, knn );

  // Read in the filename and group for the training images.
  std::ifstream knn_training_file( knn_training );
  std::string filename, group;
  while( knn_training_file >> filename >> group )
  {
    KNN.addImage( std::pair<std::string, std::string>( filename, group ) );
  }

  // Train the classifier,
  KNN.train();

  // Classify test images.
  std::ifstream knn_testing_file( knn_test );
  std::string classified;
  while( knn_testing_file >> filename >> group )
  {
    classified = KNN.classifyImage( filename );
    std::cout << "Image " << filename << " was classified as " << classified << ", it is " << group << '\n';
  }

  return 0;
}
