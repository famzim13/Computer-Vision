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

  d_histograms = std::vector<std::vector<int>>( space );
  for( int i=0; i<space; i++ )
  {
    d_histograms[i] = std::vector<int>( buckets, 0 );
  }
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
void Histogram::insertPixel( cv::Vec3i pixel )
{
  for( int i=0; i<d_space; i++ )
  {
    placePixel( i, pixel[i] );
  }
}

// FREE OPERATORS
float Histogram::getDistance( Histogram histogram )
{
  float distance = 0.0;
  for( int i=0; i<d_space; i++ )
  {
    for( int j=0; j<d_histograms[i].length(); j++ )
    {
      float += sqrt( pow( histogram[i][j] - d_histograms[i][j], 2 ) );
    }
  }

  return distance;
}

// MEMBER FUNCTIONS
void Histogram::placePixel( int histogram, int pixel )
{
  int bucket = (d_buckets-1)*(pixel/255);
  d_histograms[i][bucket] += 1;
}

} // end namespace histogram.

} // end namespace scv.
