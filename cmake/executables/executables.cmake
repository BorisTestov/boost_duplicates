include_directories(${INCLUDE_DIR})

file (GLOB SOURCES "${SRC_DIR}/*.cpp")
file (GLOB HEADERS "${INCLUDE_DIR}/*.h" "${INCLUDE_DIR}/*.hpp")

find_package( Boost  COMPONENTS program_options filesystem regex REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${Boost_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES ${TARGET_PROPERTIES})
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTIONS})

install(TARGETS ${EXECUTABLES_LIST} RUNTIME DESTINATION bin)

