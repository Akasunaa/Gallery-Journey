cmake_minimum_required(VERSION 3.15)
cmake_policy(VERSION 3.15)

include(FetchContent)
project(Tmxlite_SampleSFML VERSION 1.0.0 LANGUAGES CXX)

if(WIN32)
  # SonarLint support for CMake requires the following flag to be set on.
  #(see https://community.sonarsource.com/t/sonarlint-for-visual-studio-v4-38-support-cmake-projects/50127)
  set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

set (BUILD_SHARED_LIBS FALSE)

FetchContent_Declare(
    pugixml
    GIT_REPOSITORY https://github.com/zeux/pugixml.git
    GIT_TAG v1.10
)

FetchContent_MakeAvailable(pugixml)

if(APPLE)
  find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
  include_directories(${SFML_INCLUDE_DIRS})
else()
  # Linux or Windows
  FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.5.1
  )

  FetchContent_MakeAvailable(sfml)
endif()

set(CMAKE_CXX_STANDARD 20)

#
# Tmxlite : A simple FetchContent does not work We generate its library
# in the same manner as GoogleTest
#

# Download and unpack tmxlite at configure time
set (TMXLITE_STATIC_LIB TRUE)
configure_file(CMakeLists_tmxlite.txt.in tmxlite-download/tmxlite/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/tmxlite-download/tmxlite )
if(result)
  message(FATAL_ERROR "CMake step for tmxlite failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/tmxlite-download/tmxlite )
if(result)
  message(FATAL_ERROR "Build step for tmxlite failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add tmxlite directly to our build. This defines tmxlite target
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/tmxlite-src/tmxlite
                 ${CMAKE_CURRENT_BINARY_DIR}/tmxlite-build/tmxlite
                 EXCLUDE_FROM_ALL)
include_directories("${CMAKE_CURRENT_BINARY_DIR}/tmxlite-src/tmxlite/include")

#
# Now, we can include subdirectoiries containing sources of our project
#
add_subdirectory(mainLauncher)
add_subdirectory(src)

###################################################################################################
#
# The following lines concern googletest.
# They *must* be at top-level CMakeLists.txt, not in a sub-directory (so no "add_subdirectory(unitTests)") !
# Otherwise, Visual STudio Test Explorer does not see the tests.
#
###################################################################################################

#
# Lines coming from https://github.com/google/googletest/tree/master/googletest#incorporating-into-an-existing-cmake-project
#

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

# Now simply link against gtest or gtest_main as needed. Eg
enable_testing()
add_executable(unitTests unitTests.cpp)
target_link_libraries(unitTests gtest_main)
target_link_libraries(unitTests src pugixml sfml-graphics tmxlite)
add_test(NAME that-test-I-made COMMAND unitTests)
