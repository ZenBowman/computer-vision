#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

using namespace cv;

const int THRESHOLD = 80;
const int NEGATED = 254;
int gLabel = 0;

Mat binarize_image(Mat image) {
  Mat result; 
  cvtColor(image, result, CV_RGB2GRAY);

  int rows = image.rows;
  int cols = image.cols;

  for (int i=0; i<rows; i++) {
    uchar* rowPointer = result.ptr<uchar>(i);
    for (int j=0; j<cols; j++) {
      if (((int) rowPointer[j]) > THRESHOLD) {
	rowPointer[j] = NEGATED;
      } else {
	rowPointer[j] = 0;
      }
    }
  }
  
  return result;
}


struct xy {
  int x;
  int y;
  xy(int _x, int _y): x(_x), y(_y) {}
};

std::vector<xy> get_neighbors(int rows, int cols, int i, int j) {
  std::vector<xy> neighbors;

  if ((i-1) >= 0) {
    neighbors.push_back(xy(i-1, j));
  }  
  if (((i-1) >= 0) && ((j-1) >= 0)) {
    neighbors.push_back(xy(i-1, j-1));
  }
  if ((j-1) >= 0) {
    neighbors.push_back(xy(i, j-1));
  }
  if (((i+1) <= rows) && ((j-1) >= 0)) {
    neighbors.push_back(xy(i+1, j-1));
  }
  if ((i+1) <= rows) {
    neighbors.push_back(xy(i+1, j));
  }
  if (((i+1) <= rows) && ((j+1) <= cols)) {
    neighbors.push_back(xy(i+1, j+1));
  }
  if ((j+1) <= cols) {
    neighbors.push_back(xy(i, j+1));
  }
  if (((i-1) >= 0) && ((j+1) <= cols)) {
    neighbors.push_back(xy(i-1, j+1));
  }

  return neighbors;
}

void label_components(Mat image, int label, int i, int j) {
  int rows = image.rows;
  int cols = image.cols;
  
  uchar* rowPointer = image.ptr<uchar>(i);
  if (((int)rowPointer[j]) == NEGATED) {
    rowPointer[j] = label * 1;

    std::vector<xy> neighbors = get_neighbors(rows, cols, i, j);
    for (int index=0; index<neighbors.size(); index++) {
      label_components(image, label, neighbors[index].x, neighbors[index].y);
    }
  }
}

Mat recolor_connected_components(Mat image) {
  Mat recolored;
  cvtColor(image, recolored, CV_GRAY2RGB);
   
  int rows = image.rows;
  int cols = image.cols;
  
  for (int i=0; i<rows; i++) {
    uchar *rowPointer = image.ptr<uchar>(i);
    uchar *newPointer = recolored.ptr<uchar>(i);
    
    for (int j=0; j<cols; j++) {
      int oldvalue = ((int) rowPointer[j]);
      if (oldvalue > 0){
	int value = oldvalue % 5;
	int r = j*3;
	int g = r + 1;
	int b = r + 2;
	if (value == 0) {
	  newPointer[r] = 255;
	  newPointer[g] = 0;
	  newPointer[b] = 0;
	}
	else if (value == 1) {
	  newPointer[r] = 0;
	  newPointer[g] = 255;
	  newPointer[b] = 0;
	}
	else if (value == 2) {
	  newPointer[r] = 0;
	  newPointer[g] = 0;
	  newPointer[b] = 255;
	}
	else if (value == 3) {
	  newPointer[r] = 125;
	  newPointer[g] = 0;
	  newPointer[b] = 125;
	}
	else if (value == 4) {
	  newPointer[r] = 0;
	  newPointer[g] = 125;
	  newPointer[b] = 125;
	}
      }
    }
  }

  return recolored;
}


void find_components(Mat image) {
  int rows = image.rows;
  int cols = image.cols;

  for (int i=0; i<rows; i++) {
    uchar* rowPointer = image.ptr<uchar>(i);
    for (int j=0; j<cols; j++) {
      if (((int)rowPointer[j]) == NEGATED) {
	gLabel += 1;
	label_components(image, gLabel, i, j);
      }
    }
  }
}



// Expected usage: findconnected [image_filename]
// Output: Displays an image of connected components
int main(int argc, char *argv[]) {
  Mat image = imread(argv[1]);
  Mat binarized = binarize_image(image);
  find_components(binarized);
  Mat connectedColoring = recolor_connected_components(binarized);
  imshow("Original image", image);    
  waitKey(0);
  imshow("Connected components", connectedColoring);
  waitKey(0);
}
