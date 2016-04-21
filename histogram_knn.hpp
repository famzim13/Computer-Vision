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
    int d_buckets;
      // Number of bucket in the histogram for each image.

    std::map<std::string, histogram_group::HistogramGroup> d_groups;
      // A map of class name and its histogram group.

    int d_knn;
      // Number of nearest neighbors to classify with.

    int d_space;
      // Color space of the KNN classifier.

    std::vector<std::string> d_training_images;
      // Vector of file locations for the training images.

    // MEMBER FUNCTIONS
    histogram::Histogram buildHistogram( cv::Mat image );
      // Builds histograms from the training images.

    std::string getGroup( std::string filename );
      // Gets the classification group from the filename.

    std::vector<cv::Mat> loadImages();
      // Loads the image files.

  public:
    // CONSTRUCTOR
    HistogramKNN();
      // Default constructor.

    HistogramKNN( int buckets, int knn );
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

    std::vector<std::string> classifyImages( std::vector<std::string> classify );
      // Classifies a set of images to their nearest neighbors.

    void train(); // TODO MAKE INPUT A MAP FROM EXCEL
      // Trains the classifier.

};

} // end namespace histogram_knn.

} // end namespace scv.

#endif
