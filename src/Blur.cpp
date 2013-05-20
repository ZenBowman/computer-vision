#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "Blurrer.h"

using namespace cv;


int main( int argc, char** argv )
{
  Mat image1;

  image1 = imread( argv[1], 1 );

  imshow("Original", image1);
  waitKey(0);

  Blurrer::showWithGaussianBlur(image1);
 
  return 0;
}
