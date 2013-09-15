#include <iostream>
#include <string>
#include <stdio.h>
#include <map>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace cv;

const int THRESHOLD = 80;

int holecount(Mat image) {
  int rows = image.rows;
  int cols = image.cols;


  imshow("Image", image);
  waitKey(0);

  for (int i=0; i<rows; i++) {
    uchar* rowPointer = image.ptr<uchar>(i);
    for (int j=0; j<cols; j++) {
      if (((int) rowPointer[j]) > THRESHOLD) {
	rowPointer[j] = 1;
      } else {
	rowPointer[j] = 0;
      }
      std::cout << (int)rowPointer[j] << " ";
    }
    std::cout << std::endl;
  }

  int externalCorners = 0;
  int internalCorners = 0;
  for (int i=0; i<(rows-1); i++) {
    uchar* r0 = image.ptr<uchar>(i);
    uchar* r1 = image.ptr<uchar>(i+1);
    for (int j=0; j<(cols-1); j++) {
      int num1s = 0;
      
      if (r0[j] == 1) num1s++;
      if (r1[j] == 1) num1s++;
      if (r0[j+1] == 1) num1s++;
      if (r1[j+1] == 1) num1s++;

      if (num1s == 3) {
	internalCorners++;
      } else if (num1s == 1) {
	externalCorners++;
      }
    }
  }

  imshow("Image", image);
  waitKey(0);

  std::cout << "Number of holes = " 
	    << (externalCorners-internalCorners)/4
	    << std::endl;
  return 0;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("Please supply an image name - usage: holecount <imagename>\n");
    return -1;
  }
  Mat grayImage;
  std::cout << argv[1];
  Mat image = cv::imread(argv[1]);
  cvtColor(image, grayImage, CV_RGB2GRAY);
  return holecount(grayImage);
}
