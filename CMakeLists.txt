cmake_minimum_required(VERSION 3.10)

# set the project name
project(Tutorial VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

list(APPEND LIBS modou pthread)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

add_library(modou
    "${PROJECT_SOURCE_DIR}/src/EventLoop.cc"
    "${PROJECT_SOURCE_DIR}/src/Channel.cc"
    "${PROJECT_SOURCE_DIR}/src/Poller.cc"
    )
target_include_directories(modou PUBLIC
                           "${PROJECT_SOURCE_DIR}/include"
                           )
set_target_properties(modou PROPERTIES
                         POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS}
                         )

add_executable(Test00 test/test00.cc)
target_link_libraries(Test00 PUBLIC "${LIBS}")
target_include_directories(Test00 PUBLIC
                           "${PROJECT_SOURCE_DIR}/include"
                           )

add_executable(Test01 test/test01.cc)
target_link_libraries(Test01 PUBLIC "${LIBS}")
target_include_directories(Test01 PUBLIC
                           "${PROJECT_SOURCE_DIR}/include"
                           )
add_executable(Test02 test/test02.cc)
target_link_libraries(Test02 PUBLIC "${LIBS}")
target_include_directories(Test02 PUBLIC
                           "${PROJECT_SOURCE_DIR}/include"
                           )

add_executable(Test10 test/test10.cc)
target_link_libraries(Test10 PUBLIC "${LIBS}")
target_include_directories(Test10 PUBLIC
                           "${PROJECT_SOURCE_DIR}/include"
                           )
