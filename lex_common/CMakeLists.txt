cmake_minimum_required(VERSION 3.0.2)
project(lex_common)

SET(LEX_COMMON_VERSION 1.0.0)

find_package(aws_common REQUIRED)

add_compile_options(-std=c++11 -fPIC)

if (AWSSDK_FOUND)
    set(SERVICE lex)
    AWSSDK_DETERMINE_LIBS_TO_LINK(SERVICE AWSSDK_LIBS)
    link_directories("${AWSSDK_LIB_DIR}")
endif ()

include_directories(
        include
        ${aws_common_LIBRARIES})

## Declare a C++ library
add_library(${PROJECT_NAME}
        src/lex_common.cpp
        src/lex_param_helper.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}
        ${aws_common_LIBRARIES})

target_include_directories(${PROJECT_NAME} PRIVATE ${AWSSDK_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)


#############
## Install ##
#############

## Mark executables and/or libraries for installation
install(TARGETS ${PROJECT_NAME}
        EXPORT "${PROJECT_NAME}-targets"
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        )

## Mark cpp header files for installation
install(
        DIRECTORY include/
        DESTINATION include/
)

export(TARGETS ${PROJECT_NAME}
        FILE "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-targets.cmake")
export(PACKAGE ${PROJECT_NAME})

CONFIGURE_FILE(${PROJECT_NAME}Config.cmake.in
        ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake @ONLY)
CONFIGURE_FILE(${PROJECT_NAME}ConfigVersion.cmake.in
        ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake @ONLY)

INSTALL(FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake DESTINATION share/${PROJECT_NAME}/cmake)
INSTALL(FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake DESTINATION share/${PROJECT_NAME}/cmake)
INSTALL(EXPORT ${PROJECT_NAME}-targets DESTINATION share/${PROJECT_NAME}/cmake)

#############
## Testing ##
#############
SET(BUILD_TESTING ON)
enable_testing()
find_package(catkin QUIET)
find_package(ament QUIET)
find_package(ament_cmake_gtest QUIET)
set(TEST_TARGET test_lex_common)
set(TEST_FILES test/lex_param_test.cpp
        test/lex_common_test.cpp
        test/parameter_reader_mock.cpp)

# Catkin relies on system installed gmock 
set(TEST_1_8_MOCK_FILES ${TEST_FILES} test/lex_interactor_test.cpp)

if (catkin_FOUND)
    if (NOT GMOCK_FOUND AND NOT TARGET gmock)
      include_directories(/usr/include/gmock /usr/src/gmock)
      add_library(gmock /usr/src/gmock/src/gmock-all.cc)
    endif ()
    catkin_destinations()
    if (CATKIN_ENABLE_TESTING)
        message(STATUS "Building tests using catkin ${TEST_FILES}")
        catkin_add_gtest(${TEST_TARGET} ${TEST_FILES})
    endif ()
elseif (ament_cmake_gtest_FOUND)
    find_package(ament_cmake_gmock REQUIRED)
    message(STATUS "Building tests using ament ${TEST_1_8_MOCK_FILES}")
    ament_add_gmock(${TEST_TARGET} ${TEST_1_8_MOCK_FILES})
else ()
    message(STATUS "Not building tests as neither catkin nor ament were found.")
endif ()

if (DEFINED GMOCK_LIBRARIES)
    set(GMOCK_LIBRARY ${GMOCK_LIBRARIES})
else ()
    set(GMOCK_LIBRARY gmock)
endif ()

set(LIBS_FOR_TESTS
        ${GTEST_LIBRARIES}
        pthread
        ${GMOCK_LIBRARY}
        ${aws_common_LIBRARIES}
        ${PROJECT_NAME})

set(HEADERS_FOR_TESTS
        ${aws_common_INCLUDE_DIRS}
        ${AWSSDK_INCLUDE_DIR}
        ${GTEST_INCLUDE_DIR}
        test/include)

macro(link_test_target target_name)
    if (TARGET ${target_name})
        target_include_directories("${target_name}" PRIVATE ${HEADERS_FOR_TESTS})
        target_link_libraries("${target_name}" ${LIBS_FOR_TESTS})
    endif ()
endmacro()
link_test_target(${TEST_TARGET})
