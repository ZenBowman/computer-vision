#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

void sharpen(Mat &input, Mat &output) {
  Mat mask = (Mat_<char>(3,3) << 
	      -1, -1,  -1,
	      -1,  9, -1,
	      -1, -1,  -1);
  filter2D(input, output, input.depth(), mask);
}

int main( int argc, char** argv )
{
  Mat image;
  image = imread( argv[1], 1 );

  if( argc != 2 || !image.data )
    {
      printf( "No image data \n" );
      return -1;
    }

  Mat outputImage;
  sharpen(image, outputImage);
  // do sharpening here
  imshow("Display Image", image);
  
  imshow("Sharpened", outputImage);
  waitKey(0);
 
  return 0;
}
