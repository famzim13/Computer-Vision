// histogram_group.hpp
#ifndef INCLUDED_HISTOGRAM_GROUP
#define INCLUDED_HISTOGRAM_GROUP

#include "histogram.hpp"

#include <map>
#include <string>
#include <vector>

namespace scv
{

namespace histogram_group
{

class HistogramGroup
{
  private:
    std::string d_group;
      // Class of the histogram group.

    std::vector<histogram::Histogram> d_histograms;
      // Group of histograms for the image class.

  public:
    // CONSTRUCTORS
    HistogramGroup( std::string group );
      // Constructor with histogram group name.

    // DESTRUCTORS
    ~HistogramGroup();
      // Default destructor.

    // MUTATORS
    void addHistogram( histogram::Histogram hist );
      // Adds a histogram to the histogram group.

    // FREE OPERATORS
    std::map<float, std::string> getDistances( histogram::Histogram hist );
      // Get the distance from the input against all histograms in the group.

};

} // end namepsace histogram_group.

} // end namespace scv.

#endif
