# CMake generated Testfile for 
# Source directory: C:/Users/prome/OneDrive/Bureau/Gallery Journey/SampleGoogleTestPugixml
# Build directory: C:/Users/prome/OneDrive/Bureau/Gallery Journey/SampleGoogleTestPugixml/out/build/x64-Debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(that-test-I-made "C:/Users/prome/OneDrive/Bureau/Gallery Journey/SampleGoogleTestPugixml/out/build/x64-Debug/unitTests.exe")
set_tests_properties(that-test-I-made PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/prome/OneDrive/Bureau/Gallery Journey/SampleGoogleTestPugixml/CMakeLists.txt;89;add_test;C:/Users/prome/OneDrive/Bureau/Gallery Journey/SampleGoogleTestPugixml/CMakeLists.txt;0;")
subdirs("_deps/sfml-build")
subdirs("_deps/pugixml-build")
subdirs("mainLauncher")
subdirs("src")
subdirs("googletest-build")
