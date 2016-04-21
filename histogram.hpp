// histogram.hpp
#ifndef INCLUDED_HISTOGRAM
#define INCLUDED_HISTOGRAM

namespace scv
{

namespace histogram
{

class Histogram
{
  private:
    std::vector<int> d_histogram_r;
      // Histogram for the red pixel.

    std::vector<int> d_histogram_g;
      // Histogram for the green pixel.

    std::vector<int> d_histogram_b;
      // Histogram for the blue pixel.

  public:
    // CONSTRUCTORS
    Histogram( int buckets );
      // Constructor with number of buckets input.

    // DESTRUCTORS
    ~Histogram();
      // Default destructor.

    // MUTATORS
    void insertPixel( cv::Vec3i pixel );

};

} // end namespace histogram.

} // end namepsace scv.

#endif
