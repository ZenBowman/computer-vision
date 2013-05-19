#ifndef EXECUTABLE_COMMAND_H
#define EXECUTABLE_COMMAND_H

#include <opencv2/opencv.hpp>

enum ResultType {
  RESULT_MATRIX,
  RESULT_STRING
};

struct EvalResult {
  cv::Mat resultMat;
  std::string resultString;
  ResultType resultType;
};

class ExecutableCommand {
 public:
  virtual cv::Mat execute(std::vector<EvalResult> arguments) = 0;
};

class LoadImage: public ExecutableCommand {
 public:
  cv::Mat execute(std::vector<EvalResult> arguments);
};

#endif
