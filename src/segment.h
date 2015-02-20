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

using namespace cv;

cv::Mat conv(cv::Mat a)
{
 cv::Mat q;
 q.create(a.rows,a.cols,CV_32FC1);
 for(int j=0;j<a.rows;j++)
 {
   uchar* data=a.ptr<uchar>(j);
   float * data2=q.ptr<float>(j);
   for(int i=0;i<a.cols;i++)
   {
    data2[i]=(float(data[i]));
   }
  }
 return q;
}

cv::Mat split(cv::Mat a,int n)
{
 cv::Mat test(a.rows,a.cols,CV_8UC1);
 for (int i=0;i<a.rows;i++)
 {
   uchar *data=test.ptr<uchar>(i);
   for(int j=0;j<a.cols;j++)
   {
    if(n==1)
     data[j]=a.at<cv::Vec3b>(i,j)[0];
    else if(n==2)
     data[j]=a.at<cv::Vec3b>(i,j)[1];
    else
     data[j]=a.at<cv::Vec3b>(i,j)[2];
    }
 }
return test;
}

static void normalize(std::vector<float> &mask) 
{
  int len = mask.size();
  float sum = 0;
  for (int i = 1; i < len; i++) 
  {
    sum += fabs(mask[i]);
  }
  sum = 2*sum + fabs(mask[0]);
  for (int i = 0; i < len; i++) 
  {
    mask[i] /= sum;
  }
}

float square(float a)
{
  return a*a;
}

/* make filters */                             
std::vector<float> make_fgauss (float sigma) 
{
  int width=4.0;			      
  int len = (int)ceil(sigma * width) + 1;                     
  std::vector<float> mask(len);    
  
  for (int i = 0; i < len; i++) 
  {                             
    mask[i] = exp(-0.5*square(i/sigma));                            
  }                                                           
  return mask;                                                
}

void convolve_even(cv::Mat src, cv::Mat dst, 
			  std::vector<float> &mask) {

  int len = mask.size();

  for (int y = 0; y < src.rows; y++) 
  {
    float *data=src.ptr<float>(y);
    float *data1=dst.ptr<float>(y);
    for (int x = 0; x <src.cols; x++)
    {
      float sum = mask[0] * data[x];
      for (int i = 1; i < len; i++) 
	  {
	   sum += mask[i] *(data[max(x-i ,0)] +data[min(x+i,src.cols-1)]);
	  }
      data1[x]=sum;
    }
  }
}

/* convolve image with gaussian filter */
cv::Mat smooth(cv::Mat a , float sigma) 
{
 std::vector<float> mask = make_fgauss(sigma);
 
 normalize(mask);
 
 cv::Mat tmp(a.rows,a.cols,CV_32FC1);
 
 cv::Mat dst(a.rows,a.cols,CV_32FC1);
 
 convolve_even(a, tmp, mask);
 
 convolve_even(tmp, dst, mask);
 
 return dst;
}

float diff(cv::Mat r, cv::Mat g, cv::Mat  b,
           int x1, int y1, int x2, int y2) {
 float *data  = r.ptr<float>(y1);
 float *data1 = r.ptr<float>(y2);
 float *data2 = g.ptr<float>(y1);
 float *data3 = g.ptr<float>(y2);
 float *data4 = b.ptr<float>(y1);
 float *data5 = b.ptr<float>(y2);
		
 return sqrt(square(data[x1]-data1[x2]) +
	      square(data2[x1]-data3[x2]) +
	      square(data4[x1]-data5[x2]));
}
 
void random_rgb(int *r,int *g,int *b)
{ 
  *r=(uchar)rand();
  *g=(uchar)rand();
  *b=(uchar)rand();  
}
