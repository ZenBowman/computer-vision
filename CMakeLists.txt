cmake_minimum_required(VERSION 2.8)

project( DisplayImage )
find_package( OpenCV REQUIRED )
add_executable( DisplayImage src/DisplayImage.cpp )
target_link_libraries( DisplayImage ${OpenCV_LIBS} )

project( Sharpen )
find_package( OpenCV REQUIRED )
add_executable( Sharpen src/Sharpen.cpp )
target_link_libraries( Sharpen ${OpenCV_LIBS} )

project( Blend )
find_package( OpenCV REQUIRED )
add_executable( Blend src/Blend.cpp )
target_link_libraries( Blend ${OpenCV_LIBS} )

project( Blur )
find_package( OpenCV REQUIRED )
add_executable( Blur src/Blur.cpp src/Blurrer.cpp )
target_link_libraries( Blur ${OpenCV_LIBS} )

project( Operator )
find_package( OpenCV REQUIRED )
add_executable( Operator src/Operator.cpp )
target_link_libraries( Operator ${OpenCV_LIBS} )

project( Interactive )
find_package( OpenCV REQUIRED )

add_executable( Interactive 
  src/Interactive.cpp
  src/LoadImage.cpp
  src/ErodeImage.cpp
  src/SubtractImage.cpp
  src/AddImage.cpp
  src/DefGet.cpp
  src/EnhanceContrast.cpp
)

include_directories(/home/zenbowman/dev/externaltools/sexpr_1.2.1/src)

target_link_libraries(Interactive 
  /home/zenbowman/dev/externaltools/sexpr_1.2.1/src/libsexp.a
  ${OpenCV_LIBS} 
)



