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
)

include_directories(/home/zenbowman/dev/externaltools/sexpr_1.2.1/src)

target_link_libraries(Interactive 
  /home/zenbowman/dev/externaltools/sexpr_1.2.1/src/libsexp.a
  ${OpenCV_LIBS} 
)



