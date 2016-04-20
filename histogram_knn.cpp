// histogram_knn.cpp

namespace scv
{

namespace histogram_knn
{

// CONSTRUCTOR
HistogramKNN::HistogramKNN()
{
  d_knn = 1;
  d_num_buckets = 8;
  d_training_images = std::vector<std::string>();
}

HistogramKNN::HistogramKNN( int knn )
{
  d_knn = knn;
  d_num_buckets = 8;
  d_training_images = std::vector<std::string>();
}

HistogramKNN::HistogramKNN( int num_buckets )
{
  d_knn = 1;
  d_num_buckets = num_buckets;
  d_training_images = std::vector<std::string>();
}

HistogramKNN::HistogramKNN( int num_buckets, int knn )
{
  d_knn = knn;
  d_num_buckets = num_buckets;
  d_training_images = std::vector<std::string>();
}

// DESTRUCTOR
HistogramKNN::~HistogramKNN();

// MUTATORS
HistogramKNN::addImage( std::string training )
{
  d_training_images.append( training );
}

HistogramKNN::addImages( std::vector<std::string> training )
{
  d_training_images.insert( d_training_images.end(), training.begin(), training.end() );
}

// MEMBER FUNCTIONS
HistogramKNN::classifyImage( std::string classify )
{

}

HistogramKNN::classifyImages( std::vector<std::string> classify )
{

}

HistogramKNN::train()
{
  
}

} // end namepsace histogram_knn.

} // end namespace scv.
