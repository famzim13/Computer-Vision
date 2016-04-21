// histogram_group.cpp
#include "histogram_group.hpp"

namespace scv
{

namespace histogram_group
{

// CONSTRUCTORS
HistogramGroup::HistogramGroup( std::string group )
{
  d_group = group;
  d_histograms = std::vector<histogram::Histogram>();
}

// DESTRUCTORS
HistogramGroup::~HistogramGroup();

// MUTATORS
void HistogramGroup::addHistogram( histogram::Histogram histogram )
{
  d_histograms.push_back( histogram );
}

// FREE OPERATORS
std::map<float, std::string> HistogramGroup::getDistances( histogram::Histogram histogram )
{
  std::map<float, std::string> distances;
  for( int i=0; i<d_histograms.length(); i++ )
  {
    distances[d_histograms.getDistance( Histogram )] = d_group;
  }

  return distances;
}

} // end namespace histogram_group.

} // end namespace scv.
