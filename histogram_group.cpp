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
  d_histograms = std::vector<std::vector<int>>();
}

// DESTRUCTORS
HistogramGroup::~HistogramGroup();

// MUTATORS
void HistogramGroup::addHistogram( std::vector<int> histogram )
{
  d_histograms.push_back( histogram );
}

// FREE OPERATORS
std::vector<int> HistogramGroup::getDistances( std::vector<int> histogram )
{
  std::vector<int> distances = std::vector<int>( d_histograms.length() );
  for( int i=0; i<d_histograms.length(); i++ )
  {
    for( int j=0; j<d_histograms[i].length(); j++ )
    {
      distance[i] += sqrt( pow( d_histograms[i][j] - histogram[j], 2 ) );
    }
  }
  
  return distances;
}

} // end namespace histogram_group.

} // end namespace scv.
