#include <iostream>
#include <string>
#include <stdio.h>
#include <map>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace cv;

const double GAMMA = 2.2;
const double THRESHOLD = 90;

void exercise_3_1(char* imageName, float balanceR, float balanceG, float balanceB, bool inverseGamma) {
  Mat image = cv::imread(imageName, 1);
  int numRows = image.rows;
  int numCols = image.cols;
  for (int i=0; i<numRows; i++) {
    uchar* rowPointer = image.ptr<uchar>(i);
    for (int j=0; j<numCols; j++) {
      int r = 3*j;
      int g = r+1;
      int b = g+1;

      if (inverseGamma) {
	rowPointer[r] = pow(rowPointer[r], 1/GAMMA);
	rowPointer[g] = pow(rowPointer[g], 1/GAMMA);
	rowPointer[b] = pow(rowPointer[b], 1/GAMMA);
      }      

      rowPointer[r] = rowPointer[r]*balanceR;
      rowPointer[g] = rowPointer[g]*balanceG;
      rowPointer[b] = rowPointer[b]*balanceB;


      if (inverseGamma) {
	rowPointer[r] = pow(rowPointer[r], GAMMA);
	rowPointer[g] = pow(rowPointer[g], GAMMA);
	rowPointer[b] = pow(rowPointer[b], GAMMA);
      }            
    }
  }

  imshow("Exercise 3.1", image);
  waitKey(0);
}

void exercise_3_3(char* greenScreenImageName, char* mainImageName) {
  Mat greenScreenImage = cv::imread(greenScreenImageName, 1);
  Mat mainImage = cv::imread(mainImageName, 1);
  Mat resizedGreenScreenImage;
  resize(greenScreenImage, resizedGreenScreenImage, mainImage.size(), 0, 0, INTER_NEAREST);
  
  int numRows = mainImage.rows;
  int numCols = mainImage.cols;

  for (int i=0; i<numRows; i++) {
    uchar* rowPointer = mainImage.ptr<uchar>(i);
    uchar* gPointer = resizedGreenScreenImage.ptr<uchar>(i);

    for (int j=0; j<numCols; j++) {
      int r = 3*j;
      int g = r+1;
      int b = g+1;

      int alldiff = abs(rowPointer[g] - gPointer[g]) + abs(rowPointer[r] - gPointer[r]) + abs(rowPointer[b] - gPointer[b]);
      
      /*if (alldiff > THRESHOLD) {
	rowPointer[r] = rowPointer[g] = rowPointer[b] = 255;
      } else {
	rowPointer[r] = rowPointer[g] = rowPointer[b] = 0;
	}*/
      
      rowPointer[r] = rowPointer[r]-gPointer[r];
      int gval = (int) rowPointer[g] - (int) gPointer[g];
      if ((abs(gval) < 20) && (alldiff < THRESHOLD)) gval = 0;
      rowPointer[g] = gval;
      rowPointer[b] = rowPointer[b]-gPointer[b]; 
      
    }
  }

  imshow("Exercise 3.3", mainImage);
  waitKey(0);
}

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << "Not enough arguments to run the program. The first argument should be the exercise number";
    return 1;
  }
  if (strcmp(argv[1], "3.1") == 0) {
    if (argc < 7) {
      std::cout << "Insufficient arguments to run exercise 3.1";
      return 1;
    }
    exercise_3_1(argv[2], atof(argv[5]), atof(argv[4]), atof(argv[3]), (atoi(argv[6]) > 0));
    return 0;
  }
  else if (strcmp(argv[1], "3.3") == 0) {
    if (argc != 4) {
      std::cout << "Insufficient arguments to run exercise 3.3";
      return 1;
    }
    exercise_3_3(argv[2], argv[3]);
  }
}
