// histogram.hpp
#ifndef INCLUDED_HISTOGRAM
#define INCLUDED_HISTOGRAM

#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

namespace scv
{

namespace histogram
{

class Histogram
{
  private:
    int d_buckets;
      // Number of histogram buckets.

    std::vector<std::vector<int>> d_histograms;
      // Histograms in a color space.

    int d_space;
      // Color space of the image.

    // MEMBER FUNCTIONS
    void placePixel( int histogram, int pixel );
      // Determines which bucket a pixel goes into.

  public:
    // CONSTRUCTORS
    Histogram( int buckets, int space );
      // Constructor with number of buckets input and color space.

    // DESTRUCTORS
    ~Histogram();
      // Default destructor.

    // ACCESSORS
    int getPixelCount();
      // Gets the count of the number of pixels in the histogram.

    std::vector<std::vector<int>> getHistograms();
      // Gets the histograms of the image.

    // MUTATORS
    void insertPixel( cv::Vec3i pixel );
      // Inserts a pixel into the histogram arrays.

    // FREE OPERATORS
    float getDistance( Histogram histogram );
      // Gets the distance between two histgrams.

};

} // end namespace histogram.

} // end namepsace scv.

#endif
