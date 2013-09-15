#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

struct YCbCr {
  int y;
  int cb;
  int cr;
};

struct RGB {
  int r; 
  int g;
  int b;
};

double mult(double r, double g, double b, double fr, double fg, double fb) {
  return r * fr + g * fg + b * fb;
}

YCbCr rgb_to_ycbcr(int r, int g, int b) {
  YCbCr result;
  result.y = mult(r, g, b, 0.2999, 0.587, 0.114);
  result.cb = 128 + mult(r, g, b, -0.168736, -0.331264, 0.5); 
  result.cr = 128 + mult(r, g, b, 0.5, -.4186888, -0.081312);
  return result;
}

RGB ycbcr_to_rgb(int y, int cb, int cr) {
  RGB result;
  result.r = y + 1.402 * (cr - 128);
  result.g = y - 0.34414 * (cb - 128) - 0.71414 * (cr - 128);
  result.b = y + 1.772 * (cb - 128);
  return result;
}

cv::Mat perform_dct(cv::Mat original) {
  cv::Mat dctMat = original.clone();
  int rows = image.rows;
  int cols = image.cols;

  for (int i=0; i<rows; i++) {
    uchar *rowPointer = image.ptr<uchar>(i);
    for (int j=0; j<cols; j++) {
    }
  }
}

cv::Mat load_image(char *image_name) {
  cv::Mat image = cv::imread(image_name);
  return image;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: jpegstudy [commandname]\n");
    return -1;
  } else {
    if (strcmp(argv[1], "rgb2ycbcr") == 0) {
      if (argc < 5) {
	printf("Usage: jpegstudy rgb2ycbcr [r] [g] [b]\n");
	return -1;
      }
      YCbCr result = rgb_to_ycbcr(atoi(argv[2]), atoi(argv[3]), 
				  atoi(argv[4]));
      printf("Result: %d, %d, %d \n", result.y, result.cb, result.cr);
    }
    else if (strcmp(argv[1], "ycbcr2rgb") == 0) {
      if (argc < 5) {
	printf("Usage: jpegstudy ycbcr2rgb [y] [cb] [cr]\n");
	return -1;
      }
      RGB result = ycbcr_to_rgb(atoi(argv[2]), atoi(argv[3]),
				atoi(argv[4]));
      printf("Result: %d, %d, %d\n", result.r, result.g, result.b);
    }
    else if (strcmp(argv[1], "performdct") == 0){
      if (argc < 3) {
	printf("Usage: jpegstudy performdct [img_name]\n");
	return -1;
      }
      cv::Mat img = load_image(argv[2]);
      cv::imshow("Original image", img);
      cv::waitKey(0);
    }
  }
}
