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

class ErodeImage: public ExecutableCommand {
public:
  cv::Mat execute(std::vector<EvalResult> arguments);
};

class SubtractImage: public ExecutableCommand {
 public:
  cv::Mat execute(std::vector<EvalResult> arguments);
};

class AddImage: public ExecutableCommand {
 public:
  cv::Mat execute(std::vector<EvalResult> arguments);
};

class DefImage: public ExecutableCommand {
 public:
  cv::Mat execute(std::vector<EvalResult> arguments);
};

class GetImage: public ExecutableCommand {
 public:
  cv::Mat execute(std::vector<EvalResult> arguments);
};

class EnhanceContrast: public ExecutableCommand {
 public:
  cv::Mat execute(std::vector<EvalResult> arguments);
};


#endif
