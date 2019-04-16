#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <fstream>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
  if(argc != 2)
  {
    cout << "Worng parameter" << endl;
    return -1;
  }
  String imageName = argv[1];

  Mat image;
  image = imread(imageName,CV_8UC3);
  
  int height = image.rows;
  int width = image.cols;
  cout << "Image height is: " << height << endl;
  cout << "Image width is: " << width << endl;

  // Finish loading image

  int new_height = height/3;
  Size smallSize(width,new_height);
  vector <Mat> smallImages;
  namedWindow("smallImages",CV_WINDOW_AUTOSIZE);

  Mat new_images[3];
  Mat bgr[3];
  Mat cvt;

  for (int i = 0; i < 3; i ++)
  {
    Rect rect = Rect(0,i*new_height,width,new_height);
    smallImages.push_back(Mat(image,rect));
    new_images[i] = Mat(image,rect);
    cvtColor(new_images[i],new_images[i],COLOR_GRAY2BGR);
  }

  Mat bgr_b(new_images[0].size(),CV_8UC3, Scalar(255,0,0));  
  Mat bgr_g(new_images[0].size(),CV_8UC3, Scalar(0,255,0));
  Mat bgr_r(new_images[0].size(),CV_8UC3, Scalar(0,0,255));
//  addWeighted(new_images[0],1,bgr_b,1,0.0,new_images[0]);
  bitwise_and(new_images[0],bgr_b,new_images[0]);
//  addWeighted(new_images[1],1,bgr_g,1,0.0,new_images[1]);
//  addWeighted(new_images[2],1,bgr_r,1,0.0,new_images[2]);
  bitwise_and(new_images[1],bgr_g,new_images[1]);
  bitwise_and(new_images[2],bgr_r,new_images[2]);


  imshow("smallImages",new_images[0]);
  waitKey(0);
  imshow("smallImages",new_images[1]);
  waitKey(0);
  imshow("smallImages",new_images[2]);
  waitKey(0);


  Mat dst;
  addWeighted(new_images[0],1,new_images[1],1,0.0,dst);
  addWeighted(dst,1,new_images[2],1,0.0,dst);
   
  imshow("smallImages",dst);
  waitKey(0);

  return 0;
}

