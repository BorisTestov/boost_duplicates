find_package(Qt5 REQUIRED COMPONENTS Test)

include_directories(${INCLUDE_DIR}/tests)

file(GLOB TEST_SOURCES "${SRC_DIR}/*.cpp" "${SRC_DIR}/tests/*.cpp")
file(GLOB TEST_HEADERS
        "${INCLUDE_DIR}/*.h" "${INCLUDE_DIR}/*.hpp"
        "${INCLUDE_DIR}/tests/*.h" "${INCLUDE_DIR}/tests/*.hpp")
list(REMOVE_ITEM TEST_SOURCES ${SRC_DIR}/main.cpp)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(BOOST_INCLUDEDIR /usr/include/boost)
set(BOOST_LIBRARYDIR /usr/lib)
find_package(Boost 1.70.0 COMPONENTS program_options filesystem regex REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(test_${PROJECT_NAME} ${TEST_SOURCES} ${TEST_HEADERS})
set_target_properties(test_${PROJECT_NAME} PROPERTIES ${TARGET_PROPERTIES})
target_link_libraries(test_${PROJECT_NAME} PRIVATE Qt5::Test ${Boost_LIBRARIES})
target_compile_options(test_${PROJECT_NAME} PRIVATE ${COMPILE_OPTIONS})

enable_testing()
add_test(test_${PROJECT_NAME} ${BUILD_DIR}/test_${PROJECT_NAME})
