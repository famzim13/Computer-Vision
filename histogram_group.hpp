// histogram_group.hpp
#ifndef INCLUDED_HISTOGRAM_GROUP
#define INCLUDED_HISTOGRAM_GROUP

#include <string>
#include <vector>

namespace scv
{

namespace histogram_group
{

class HistogramGroup
{
  private:
    std::string d_class;
      // Class of the histogram group.
      
    std::vector<std::vector<int>> d_histograms;
      // Group of histograms for the image class.

  public:

};

}

}

#endif
