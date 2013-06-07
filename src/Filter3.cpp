#include "ExecutableCommand.h"
#include <opencv2/opencv.hpp>

using namespace cv;


Mat Filter3::execute(std::vector<EvalResult> arguments) {
  Mat output_image;

  Mat input_image = arguments[0].resultMat;
  int filterElements[9];

  for (int i=0; i<9; i++) {
    filterElements[i] = atoi(arguments[i+1].resultString.c_str());
  }

  Mat mask = (Mat_<char>(3,3) <<
	      filterElements[0], filterElements[1], filterElements[2],
	      filterElements[3], filterElements[4], filterElements[5],
	      filterElements[7], filterElements[8], filterElements[9]);
  
  filter2D(input_image, output_image, input_image.depth(), mask);

  return output_image;
}

