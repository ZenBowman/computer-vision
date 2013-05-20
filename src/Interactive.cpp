#include <iostream>
#include <string>
#include <stdio.h>
#include <map>
#include <vector>
#include <opencv2/opencv.hpp>
#include "sexp.h"
#include "ExecutableCommand.h"

using namespace cv;

const int erosion_type = MORPH_RECT;
LoadImage loadImage;
ErodeImage erodeImage;
SubtractImage subtractImage;
AddImage addImage;
DefImage defImage;
GetImage getImage;

std::map<std::string, ExecutableCommand*> commands;

void init() {
  commands["load"] = &loadImage;
  commands["erode"] = &erodeImage;
  commands["subtract"] = &subtractImage;
  commands["add"] = &addImage;
  commands["def"] = &defImage;
  commands["get"] = &getImage;
}

EvalResult eval(sexp_t* command) {
  elt* current;
  std::string operation;
  std::vector<EvalResult> arguments;
  EvalResult result;
  result.resultType = RESULT_MATRIX;

  if (command->ty == SEXP_LIST) {
    operation = command->list->val;
    std::cout << "Found command: " << command->list->val << std::endl;
    current = command->list->next;
    while (current != 0) {
      if (current->ty == SEXP_VALUE) {
	std::cout << "Found argument: " << current->val << std::endl;
	EvalResult er;
	er.resultString = current->val;
	std::cout << "Added argument " << er.resultString << std::endl;
	er.resultType = RESULT_STRING;
	arguments.push_back(er);
      } else {
	arguments.push_back(eval(current));
      }
      current = current->next;
    }
    
    std::cout << "Processing operation " << operation << " with args: "
	      << std::endl;

    for (size_t i=0; i<arguments.size(); i++) {
      EvalResult i_er = arguments[i];
      if (i_er.resultType == RESULT_STRING) {
	std::cout << "string = " << i_er.resultString << std::endl;
      } else {
	std::cout << "MATRIX" << std::endl;
      }
    }
    if (commands.find(operation) != commands.end()) {
      result.resultMat = commands[operation]->execute(arguments);
    }
  }
  return result;
}

int main( int argc, char** argv )
{
  init();
  cv::destroyWindow("win");
  char _command[256];
  sexp_t* command;
  EvalResult commandResult;
  std::string foo;
  
  namedWindow("Result", CV_WINDOW_AUTOSIZE);

  while(true) {
    std::cout << "Enter command:\t";
    std::cin.getline(_command, 256);
    std::cout << _command << std::endl;
    if (strcmp("(exit)", _command) == 0) {
      break;
    }
    else if (strcmp("(display)", _command) == 0) {
      waitKey(0);
    }
    else {
      command = parse_sexp(_command, strlen(_command));
      commandResult = eval(command);
      imshow("Result", commandResult.resultMat);
      destroy_sexp(command);
    }
  }

  return 0;
}
