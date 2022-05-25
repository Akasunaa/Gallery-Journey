#
# For googletest
#
# Contents coming from https://github.com/google/googletest/tree/main/googletest#incorporating-into-an-existing-cmake-project

cmake_minimum_required(VERSION 2.8.2...3.15)

project(googletest-download NONE)

include(ExternalProject)
ExternalProject_Add(googletest
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           main
  SOURCE_DIR        "C:/Users/prome/OneDrive/Bureau/Gallery Journey/SampleGoogleTestPugixml/out/build/x64-Debug/googletest-src"
  BINARY_DIR        "C:/Users/prome/OneDrive/Bureau/Gallery Journey/SampleGoogleTestPugixml/out/build/x64-Debug/googletest-build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)
