/**
 * This algorithm for graph-segmentation is orignally 
 * developed by Pedro F. Felzenszwalb. Its C++ implementation 
 * is freely avilable under the terms of the GNU General Public License.
 * 
 * However, I (Suryansh Kumar) with Ayush Dewan has modified his code
 * to make it compatible with OpenCV datastructure. The code that is available freely
 * has its own methods to read image file( namely .ppm, .pgm, .pbm etc). We have 
 * made it flexible enough to make this algorithm work for .jpg and other compressed image file format. 
 *
 * Author: Suryansh Kumar 
 * 
 * */


#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include "../src/pedro.cpp" 
using namespace std;
using namespace cv;

//it takes the label number which you want as output

Mat labelled_image(int label,int *arr_label[],Mat image)
{
 Mat temp(image.size(),CV_8UC1,Scalar(0));
 for(int i=0;i<image.rows;i++)
 {
   for(int j=0;j<image.cols;j++)
   {
     if(label==arr_label[i][j])
     {
      temp.at<uchar>(i,j)=255;
     }
   }
 }
 return(temp);
}

int main( int argc, char *argv[])
{
  /*Read Image*/  
  cv::Mat img = cv::imread(argv[1], 1);

  /*Result of graph-segmentation*/	
  cv::Mat output(img.size(),img.type());
	
  /*labelled image i.e each segment is assigned a particular label*/	  
  cv::Mat label_image(img.size(),img.type(),Scalar(0));
	
  /*Parameters for graph-segmentation*/
  int k = 500;
  int min_size = 500; 
  
  pedro p = pedro(img, k, min_size);
	
  cv::imshow("input image",img);
  
  p.Evaluate();
  
  cout<<"number of segments = "<<p.num_ccs<<endl;
  
  p.output_seg.copyTo(output); 
  
  cv::imshow(" segmented output ",output);
  
  /**Suppose you want to check a segment number then uncomment the code below and provide
   * the label number**/
  
  /*
  int label_no = 1;
  label_image = labelled_image(label_no, p.labels_seg, img); //Suppose you want label 1
  
  cv::namedWindow("labelimage");
  
  cv::imshow("labelimage",label_image);*/
  
  cv::waitKey(0);
  
  return (0);
}



