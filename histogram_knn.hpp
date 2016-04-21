// histogram_knn.hpp
#ifndef INCLUDED_HISTOGRAM_KNN
#define INCLUDED_HISTOGRAM_KNN

#include "histogram.hpp"
#include "histogram_group.hpp"

#include <map>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <vector>

namespace scv
{

namespace histogram_knn
{

class HistogramKNN
{
  private:
    std::map<std::string, HistogramGroup> d_classes;
      // A map of class name and its histogram group.

    int d_knn;
      // Number of nearest neighbors to classify with.

    int d_num_buckets;
      // Number of bucket in the histogram for each image.

    std::vector<std::string> d_training_images;
      // Vector of file locations for the training images.

  public:
    // CONSTRUCTOR
    HistogramKNN();
      // Default constructor.

    HistogramKNN( int num_buckets );
      // KNN histogram with a set number of buckets.

    HistogramKNN( int knn );
      // KNN histogram with the number of neighbors to check.

    HistogramKNN( int num_buckets, int knn );
      // KNN histogram with a number of buckets and how many neighbors to check.

    // DESTRUCTOR
    ~HistogramKNN();
      // Default destructor.

    // MUTATORS
    void addImage( std::string training );
      // Adds a training image to the classifier.

    void addImages( std::vector<std::string> training );
      // Adds training images to the classifier.

    // FREE OPERATORS
    std::string classifyImage( std::string classify );
      // Classifies a single image.

    std::vector<std::stirng> classifyImages( std::vector<std::string> classify );
      // Classifies a set of images to their nearest neighbors.

    void train(); // TODO MAKE INPUT A MAP FROM EXCEL
      // Trains the classifier.

};

} // end namespace histogram_knn.

} // end namespace scv.

#endif
