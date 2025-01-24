cmake_minimum_required(VERSION 3.10)
project(C++)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

 file(GLOB CPP_FILES "*.cpp")

 message(STATUS "Found source files: ${CPP_FILES}")
find_package(Boost REQUIRED)

# Loop through each .cpp file
foreach(CPP_FILE ${CPP_FILES})
    # Extract the filename without the directory or extension
    get_filename_component(EXECUTABLE_NAME ${CPP_FILE} NAME_WE)

    # Debug: Show the executable name being created
    message(STATUS "Creating executable: ${EXECUTABLE_NAME} from ${CPP_FILE}")

    # Add executable for each .cpp file
    add_executable(${EXECUTABLE_NAME} ${CPP_FILE})
    target_link_libraries(${EXECUTABLE_NAME} ${Boost_LIBRARIES})
endforeach()
