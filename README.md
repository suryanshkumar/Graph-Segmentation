# GraphSegmentation

This algorithm for graph-segmentation is orignally 
developed by Pedro F. Felzenszwalb. Its C++ implementation 
is freely available by him under the terms of the GNU General Public License.

Kindly, refer to his research work[1] for more details:

[1]. Efficient Graph-Based Image Segmentation 

     Pedro F. Felzenszwalb and Daniel P. Huttenlocher,
     International Journal of Computer Vision, Volume 59, Number 2, September 2004
     
     link: http://cs.brown.edu/~pff/segment/


Modified by: Suryansh Kumar, Ayush Dewan.

The motivation behind writing this code is to make this algorithm compatible with different image formats. 
Moreover, OpenCV is one of the most widely used computer vision library, which makes this algorithm more 
flexible to use. 

In addition to this, Robot vision platform rarely uses raw image formats(.ppm, .pgm etc), most of the 
time compressed image formats (say .jpg) are used. Hence, this algorithm can be easily integrated with ROS(OpenCV). 

To run this version of Software you must have few dependencies installed 

a. OpenCV

b. cmake

Compilation Instructions:

a. cd GraphSegmentation (folder_ containing_GraphSegmentation_source)

b. mkdir build

c. cmake ..

d. make

Your binary will be in build/apps.
Example image has been provided with this code in img folder to test quickly.

Execution command
a) ./graph_segmentation ../../img/339.jpg 

   ./(name_of_binary) (path_to_image)

