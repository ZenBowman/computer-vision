cmake_minimum_required(VERSION 2.8)

project( Interactive )
find_package( OpenCV REQUIRED )

add_executable( Interactive 
  src/Interactive.cpp
  src/LoadImage.cpp
  src/ErodeImage.cpp
  src/DilateImage.cpp
  src/SubtractImage.cpp
  src/AddImage.cpp
  src/DefGet.cpp
  src/EnhanceContrast.cpp
  src/Sharpen.cpp
  src/Blur.cpp
  src/Filter3.cpp
  src/ToGrayScale.cpp
  src/Derivative.cpp
  src/Canny.cpp
  src/Multiply.cpp
)

include_directories(/home/zenbowman/dev/externaltools/sexpr_1.2.1/src)

target_link_libraries(Interactive 
  /home/zenbowman/dev/externaltools/sexpr_1.2.1/src/libsexp.a
  ${OpenCV_LIBS} 
)

project(FaceDetect)
find_package(OpenCV REQUIRED)
add_executable(FaceDetect src/FaceDetection.cpp)
target_link_libraries(FaceDetect ${OpenCV_LIBS})

project(Chapter3)
find_package(OpenCV REQUIRED)
add_executable(Chapter3 src/Chapter3Exercises.cpp)
target_link_libraries(Chapter3 ${OpenCV_LIBS})

project( InteractiveVideo )
find_package( OpenCV REQUIRED )

add_executable( InteractiveVideo 
  src/InteractiveVideo.cpp
  src/LoadImage.cpp
  src/ErodeImage.cpp
  src/DilateImage.cpp
  src/SubtractImage.cpp
  src/AddImage.cpp
  src/DefGet.cpp
  src/EnhanceContrast.cpp
  src/Sharpen.cpp
  src/Blur.cpp
  src/Filter3.cpp
  src/ToGrayScale.cpp
  src/Derivative.cpp
  src/Canny.cpp
  src/Multiply.cpp
)

include_directories(/home/zenbowman/dev/externaltools/sexpr_1.2.1/src)

target_link_libraries(InteractiveVideo 
  /home/zenbowman/dev/externaltools/sexpr_1.2.1/src/libsexp.a
  ${OpenCV_LIBS} 
)

project(holecount)
find_package(OpenCV REQUIRED)
add_executable(holecount src/HoleCounting.cpp)
target_link_libraries(holecount ${OpenCV_LIBS})

project(jpegstudy)
find_package(OpenCV REQUIRED)
add_executable(jpegstudy src/JpegStudy.cpp)
target_link_libraries(jpegstudy ${OpenCV_LIBS})