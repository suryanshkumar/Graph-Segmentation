
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




#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "segment.h"
#include "segment-graph.h"
#include "pedro.h"

using namespace std;

pedro::pedro(cv::Mat img, int k, int size)
{	
 scale=img;
 
 K=k;
 
 min_size=size;
 
 double sigma=0.5;
 
 cv::Mat r=split(scale,3);
 
 cv::Mat g=split(scale,2);
 
 cv::Mat b=split(scale,1);
	
 cv::Mat r_f(scale.rows,scale.cols,CV_32FC1);
 
 cv::Mat g_f(scale.rows,scale.cols,CV_32FC1);
 
 cv::Mat b_f(scale.rows,scale.cols,CV_32FC1);
 
 r.convertTo(r_f,CV_32FC1);
 
 g.convertTo(g_f,CV_32FC1);
 
 b.convertTo(b_f,CV_32FC1);

 r_s=smooth(r_f,sigma);
 
 g_s=smooth(g_f,sigma);
 
 b_s=smooth(b_f,sigma);

 height=scale.rows;
 
 width=scale.cols;
 
 labels_seg=new int*[height];
 
 for (int i=0;i<height;i++)
  labels_seg[i]=new int [width];
  
 color_r=new int [height*width];
 color_g=new int [height*width];
 color_b=new int [height*width];
 cv::Mat o(height,width,CV_8UC3);
 output_seg=o;
}

void pedro::Evaluate()
{
		
  edge *edges = new edge[width*height*4];
  int num = 0;
  for (int y = 0; y < height; y++) 
  {
    for (int x = 0; x < width; x++) 
    {
      if (x < width-1) 
      {
	edges[num].a = y * width + x;
	edges[num].b = y * width + (x+1);
	edges[num].w = diff(r_s, g_s, b_s, x, y, x+1, y);
	num++;
      }

      if (y < height-1) 
      {
	edges[num].a = y * width + x;
	edges[num].b = (y+1) * width + x;
	edges[num].w = diff(r_s, g_s, b_s, x, y, x, y+1);
	num++;
      }

      if ((x < width-1) && (y < height-1)) 
      {
        edges[num].a = y * width + x;
	edges[num].b = (y+1) * width + (x+1);
	edges[num].w = diff(r_s, g_s, b_s, x, y, x+1, y+1);
	num++;
      }

      if ((x < width-1) && (y > 0)) 
      {
	edges[num].a = y * width + x;
	edges[num].b = (y-1) * width + (x+1);
	edges[num].w = diff(r_s, g_s, b_s, x, y, x+1, y-1);
	num++;
      }
    }
  }
  
  universe *u = segment_graph(width*height, num, edges,K);//defined in segment_graph.h
  for (int i = 0; i < num; i++) 
  {
    int a = u->find(edges[i].a);
    int b = u->find(edges[i].b);

    if ((a != b) && ((u->size(a) < min_size) || (u->size(b) < min_size)))
      u->join(a, b);
  }
  num_ccs = u->num_sets();
  delete [] edges;
    
  int *color_r=(int *)malloc(sizeof(int)*(width*height));
  int *color_g=(int *)malloc(sizeof(int)*(width*height));
  int *color_b=(int *)malloc(sizeof(int)*(width*height)); 
 
  for (int i = 0; i < width*height; i++)
    random_rgb(&color_r[i],&color_g[i],&color_b[i]);

  int *list=(int*)malloc((num_ccs+1)*sizeof(int));
  int counter_seg=0;
  for (int y = 0; y < height; y++)
  {
    for (int x = 0; x < width; x++)
    {
     int comp = u->find(y * width + x);
     int flag=-1;
     for (int k=0; k<= counter_seg; k++)
      if(comp==list[k])
        flag=k;	 
      if(flag==-1)
      {
        labels_seg[y][x]=counter_seg;
        list[counter_seg++]=comp;
      }
      else
        labels_seg[y][x]=flag;

      output_seg.at<cv::Vec3b>(y,x)[0]=color_r[comp];
      output_seg.at<cv::Vec3b>(y,x)[1]=color_g[comp];
      output_seg.at<cv::Vec3b>(y,x)[2]=color_b[comp];
    }
  }
}
