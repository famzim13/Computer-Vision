// histogram_knn.hpp
#ifndef INCLUDED_HISTOGRAM_KNN
#define INCLUDED_HISTOGRAM_KNN

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
    HistogramKNN( int num_buckets, std::vector<std::string> training );
      // Constructor taking in histogram bucket count and training images.

    // DESTRUCTOR
    ~HistogramKNN();
      // Default destructor.

    // MUTATORS
    void addImage( std::string training );
      // Adds a training image to the classifier.

    void addImages( std::vector<std::string> training );
      // Adds training images to the classifier.

    // FREE OPERATORS
    std::String classifyImage( std::string classify );
      // Classifies a single image.

    std::vector<std::Stirng> classifyImages( std::vector<std::string> classify );
      // Classifies a set of images to their nearest neighbors.

    void train();
      // Trains the classifier.

};

} // end namespace histogram_knn.

} // end namespace scv.

#endif
