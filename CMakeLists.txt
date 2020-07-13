cmake_minimum_required(VERSION 3.1)

project(imager)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify compilers
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc++)

set (SOURCES
 src/code.cpp
 src/mainwindow.cpp
 src/colors.cpp
 src/image.cpp
)

set (MOC_HEADERS
 include/mainwindow.h
)

set (FORMS
 include/mainwindow.ui
)


# Tell cmake to look for qt .ui files at compilation
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS include)

# Adding qt and kde libraries to include?
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(KF5WidgetsAddons)
find_package(KF5KIO)

# Specify include directories
include_directories(include build/imager_autogen/include)
set(CMAKE_INCLUDE_CURRENT_DIR ON) # Not sure if this is needed

# Set debugging flag?
set(CMAKE_CXX_FLAGS "-g3")

add_executable(${PROJECT_NAME} ${SOURCES} ${MOC_HEADERS})

target_link_libraries(imager PRIVATE KF5::WidgetsAddons Qt5::Widgets KF5::KIOCore KF5::KIOFileWidgets KF5::KIOWidgets KF5::KIONTLM)
