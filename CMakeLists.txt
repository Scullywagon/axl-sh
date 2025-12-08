cmake_minimum_required(VERSION 3.20)

project(axl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(include)

file(GLOB SRC_FILES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(${PROJECT_NAME} ${SRC_FILES})

find_library(READLINE_LIB readline)

target_link_libraries(${PROJECT_NAME} PRIVATE ${READLINE_LIB})

