// histogram.cpp
#include "histogram.hpp"

namespace scv
{

namespace histogram
{

// CONSTRUCTORS
Histogram::Histogram( int buckets, int space )
{
  d_buckets = buckets;
  d_space = space;
  d_histograms = std::vector<std::vector<int>>( space, std::vector<int>( buckets, 0 ) );
}

// DESTRUCTORS
Histogram::~Histogram()
{

}

// ACCESSORS
std::vector<std::vector<int>> Histogram::getHistograms()
{
  return d_histograms;
}

int Histogram::getPixelCount()
{
  int count = 0;
  for( int i=0; i<d_space; i++ )
  {
    for( int j=0; j<d_buckets; j++ )
    {
      count += d_histograms[i][j];
    }
  }

  return count;
}

// MUTATORS
void Histogram::insertPixel( cv::Vec3b pixel )
{
  for( int i=0; i<d_space; i++ )
  {
    d_histograms[i][(d_buckets-1)*(pixel[i]/255)] += 1;
  }
}

// FREE OPERATORS
float Histogram::getDistance( Histogram hist )
{
  float distance = 0.0;
  auto histograms = hist.getHistograms();

  for( int i=0; i<d_space; i++ )
  {
    for( int j=0; j<d_buckets; j++ )
    {
      distance += sqrt( pow( histograms[i][j] - d_histograms[i][j], 2 ) );
    }
  }

  return distance;
}

} // end namespace histogram.

} // end namespace scv.
