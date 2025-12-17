cmake_minimum_required(VERSION 3.23)

project(resound)

add_executable(resound WIN32)

target_compile_definitions(resound PRIVATE UNICODE _UNICODE)

target_sources(resound
  PRIVATE

  main.cpp
  widgets/button.cpp
  widgets/linear.cpp
  widgets/text.cpp
  widgets/checkbox.cpp
  widgets/radio.cpp
)
