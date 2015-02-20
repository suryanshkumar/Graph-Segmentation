/**
 * This algorithm for graph-segmentation is orignally 
 * developed by Pedro F. Felzenszwalb. Its C++ implementation 
 * is freely avilable under the terms of the GNU General Public License.
 * 
 * 
 * However, I (Suryansh Kumar) with Ayush Dewan has modified his code
 * to make it compatible with OpenCV datastructure.
 * 
 * Author: Suryansh Kumar
 * */



class pedro
{
  public :
	
    pedro(cv::Mat img,int k,int size);
    
	cv::Mat output_seg;

	int **labels_seg;
    
    int num_ccs;
	
    void Evaluate();


private:
   
   cv::Mat r_s;
   
   int K;
   
   int min_size;

   cv::Mat g_s;
   
   cv::Mat b_s;
   
   cv::Mat scale;
   
   int height;
   
   int width;
   
   int *color_r; 
   
   int *color_g;
   
   int *color_b;
};
