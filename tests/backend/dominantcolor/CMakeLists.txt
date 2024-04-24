set(DOMINANTCOLORTEST_TARGET "DominantColorTest")

add_executable(${DOMINANTCOLORTEST_TARGET})

# We need this because some source files depend on other headers
# which location is unknown to cmake
include_directories(
  ${CMAKE_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/src/backend/dominantcolor/ # to have a shorter path to DominantColor.h
)

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

target_sources(${DOMINANTCOLORTEST_TARGET}
  PRIVATE
  DominantColorTest.h
  DominantColorTest.cpp
  ${CMAKE_SOURCE_DIR}/src/backend/dominantcolor/DominantColor.cpp
)

target_link_libraries(${DOMINANTCOLORTEST_TARGET}
  PRIVATE
  Qt5::Core
  Qt5::Test
  ${OpenCV_LIBS}
)

set_target_properties(${DOMINANTCOLORTEST_TARGET} PROPERTIES
  LINK_FLAGS "-static"
)

add_test(DominantColorTest
  ${DOMINANTCOLORTEST_TARGET}
)
