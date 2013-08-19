#include <fstream>
#include "InteractiveCommon.cpp"

char processCommand[256];
char filename[256];

void refreshProcessCommand() {
  std::ifstream myfile(filename);
  std::string line;
  if (myfile.is_open())
  {
    getline(myfile, line);
  }
  strcpy(processCommand, line.c_str()); 
}

void saveFrame(std::string frame_name, Mat frame) {
  std::vector<EvalResult> saveCurrentFrame;
  EvalResult cFrameName;
  cFrameName.resultString = frame_name;
  cFrameName.resultType = RESULT_STRING;
  saveCurrentFrame.push_back(cFrameName);
  
  EvalResult cFrameData;
  cFrameData.resultMat = frame;
  cFrameData.resultType = RESULT_MATRIX;
  saveCurrentFrame.push_back(cFrameData);
  
  defImage.execute(saveCurrentFrame);
}

int main( int argc, char** argv )
{
  bool initializedFrameSet = false;

  init();
  cv::destroyWindow("win");
  char _command[256];
  sexp_t* command;
  EvalResult commandResult;
  std::string foo;

  strcpy(filename, argv[1]);
  std::cout << "Reading input from " << filename << "\n\n";

  CvCapture* capture;

  Mat frameSet[1000];
  Mat currentFrame;
  
  namedWindow("Result", CV_WINDOW_AUTOSIZE);

  capture = cvCaptureFromCAM(-1);
  refreshProcessCommand();

  if (capture) {
    while(true) {

      currentFrame = cvQueryFrame(capture);

      if (!initializedFrameSet) {
	for (int i=0; i<100; i++) {
	  frameSet[i] = currentFrame.clone();
	}
	initializedFrameSet = true;
      }
      else {
	for (int i=99; i>=1; i--) {
	  frameSet[i] = frameSet[i-1];
	}
	frameSet[0] = currentFrame.clone();
      }


      if (!currentFrame.empty()) {
	saveFrame("frame-75", frameSet[75]);
	saveFrame("frame-50", frameSet[50]);
	saveFrame("frame-20", frameSet[20]);
	saveFrame("frame-10", frameSet[10]);
	saveFrame("previous-frame", frameSet[1]);
	saveFrame("current-frame", frameSet[0]);
	command = parse_sexp(processCommand, strlen(processCommand));
	commandResult = eval(command);
	imshow("Result", commandResult.resultMat);

	int c = waitKey(10);	
	if (((char) c) == 'c') {
	  break;
	} else if (((char) c) == 'r') {
	  refreshProcessCommand();
	}

	destroy_sexp(command);
      }
    }
  }

  return 1;
}
