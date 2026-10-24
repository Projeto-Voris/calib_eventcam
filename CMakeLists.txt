cmake_minimum_required(VERSION 3.5)
project(calib_cam VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# --- Dependencies -----------------------------------------------------------
# The calibration/cv components are part of the full Metavision SDK (not
# OpenEB).
find_package(MetavisionSDK COMPONENTS core driver ui cv calibration
             REQUIRED)
find_package(OpenCV REQUIRED COMPONENTS core imgproc imgcodecs highgui calib3d)
find_package(Boost REQUIRED COMPONENTS filesystem program_options)
find_package(yaml-cpp REQUIRED)
if(TARGET yaml-cpp::yaml-cpp)
  set(YAML_CPP_TARGET yaml-cpp::yaml-cpp)
else()
  set(YAML_CPP_TARGET yaml-cpp) # older yaml-cpp releases
endif()

# --- Library: everything except main() --------------------------------------
add_library(calib_core STATIC
  src/app_config.cpp
  src/bias_settings.cpp
  src/camera_bias_controller.cpp
  src/command.cpp
  src/commands.cpp
  src/menu.cpp
  # Adapted from Metavision SDK samples (Prophesee license applies)
  src/blinking_chessboard_detector.cpp
  src/blinking_dots_grid_detector.cpp
  src/blinking_pattern_focus.cpp
  src/calibration_recording.cpp
  src/metavision_mono_calibration.cpp
)
target_include_directories(calib_core PUBLIC include)
target_link_libraries(calib_core PUBLIC
  MetavisionSDK::core
  MetavisionSDK::driver
  MetavisionSDK::ui
  MetavisionSDK::cv
  MetavisionSDK::calibration
  ${OpenCV_LIBS}
  Boost::filesystem
  Boost::program_options
  ${YAML_CPP_TARGET}
)
target_compile_options(calib_core PRIVATE -Wall -Wextra)

# --- Executable -------------------------------------------------------------
add_executable(calib_cam src/calib_cam.cpp)
target_link_libraries(calib_cam PRIVATE calib_core)

if(EXISTS ${CMAKE_SOURCE_DIR}/assets)
  add_custom_command(TARGET calib_cam POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:calib_cam>/assets)
endif()
