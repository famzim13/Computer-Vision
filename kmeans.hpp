// kmeans.hpp
#ifndef INCLUDED_KMEANS
#define INCLUDED_KMEANS

#include "centroid.hpp"

#include <map>
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

      int d_num_clusters;
        // Number of clusters to be chosen.

      std::vector<centroid::Centroid> d_centroids;
        // List of centroids.

      std::vector<std::map<int, cv::Vec2i>> d_coords;
        // Map of centroid pixel coordinates.

      std::vector<std::map<int, cv::Vec3b>> d_rgb;
        // Map of centroid pixel rgbs.

      // MEMBER FUNCTIONS
      cv::Mat kmeansImage();
        // Returns image with clusters color by their centroid.

      int mapCoordinates( int x, int y );
        // Converts coordinates into a unique integer.

      int nearestCentroid( cv::Vec3b pixel );
        // Find the centroid the pixel belongs to.

      void setCentroids();
        // Builds the list of centroids.

      void setMaps();
        // Builds initial maps.

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

      cv::Mat performMap();

  };

} // end namespace kmeans.

} // end namespace scv.

#endif
