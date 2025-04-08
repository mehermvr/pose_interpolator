cmake_minimum_required(VERSION 3.28)
project(
  pose_interpolator
  VERSION 0.0.1
  LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(SKBUILD)
  set(PYBIND11_NEWPYTHON ON)
  find_package(pybind11 CONFIG REQUIRED)
  find_package(Sophus REQUIRED)
  pybind11_add_module(pose_interpolator_pybind MODULE
                      pose_interpolator/pose_interpolator_pybind.cpp)
  target_link_libraries(pose_interpolator_pybind PRIVATE Sophus::Sophus)
  install(TARGETS pose_interpolator_pybind DESTINATION pose_interpolator)
endif()
