// kmeans.hpp
#ifndef INCLUDED_KMEANS
#define INCLUDED_KMEANS

#include "centroid.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdlib.h>
#include <time.h>
#include <vector>

namespace scv
{

namespace kmeans
{

  class KMeans
  {
    private:
      cv::Mat d_image;
        // Input image.

      cv::Mat d_clustered;
        // Image with pixels placed in a cluster.

      cv::Mat d_old_clustered;
        // Old image with pixels placed in a cluster.

      int d_num_clusters;
        // Number of clusters to be chosen.

      std::vector<centroid::Centroid> d_centroids;
        // List of centroids.

      // MEMBER FUNCTIONS
      bool converged( cv::Mat clustered );
        // Check if kmeans has converged.

      cv::Mat kmeansImage();
        // Returns image with clusters color by their centroid.

      int nearestCentroid( cv::Vec3b pixel );
        // Find the centroid the pixel belongs to.

      void setCentroids();
        // Builds the list of centroids.

      void updateCentroids();
        // Update the centroids for each iteration of the loop.

    public:
      // CONSTRUCTORS
      KMeans( cv::Mat image );
        // Constructor taking in input image, default clusters of 3.

      KMeans( cv::Mat image, int num_clusters );
       // Constructor taking in input image and number of clusters.

       // DESTRUCTORS
      ~KMeans();
        // Default destructor.

      // MUTATORS
      void setImage( cv::Mat image );
        // Set input image.

      void setNumClusters( int num_clusters );
        // Set number of clusters.

      // FREE OPERATORS
      cv::Mat perform();
        // Perform kmeans algorithm upon image.

  };

} // end namespace kmeans.

} // end namespace scv.

#endif
