cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)

PROJECT(opencv_cpp_basics)

find_package( OpenCV REQUIRED ) #find_package( OpenCV 4 REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS})

MACRO(add_example name)
  ADD_EXECUTABLE(${name} src/${name}.cpp)
  TARGET_LINK_LIBRARIES(${name} ${OpenCV_LIBS})
ENDMACRO()

add_example(hello_cv)
#add_example(basic_functions)
#add_example(array_types)
#add_example(split_channels)
#add_example(drawing_functions)
#add_example(simple_webcam)
#add_example(record_vid_cam)
#add_example(record_video)
#add_example(bitwise_ops)
#add_example(trackbar_wsum)
#add_example(mouse_events)
#add_example(mouse_userdata_buttons)
#add_example(inrange_hsv)
