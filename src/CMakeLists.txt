set(TERMCOLOR_SOURCES
  ${TERMCOLOR_SOURCES}
  main.cpp
)

add_subdirectory(backend)
add_subdirectory(gui)

set(TERMCOLOR_TARGET "TermColor")

add_executable(${TERMCOLOR_TARGET}
  ${TERMCOLOR_SOURCES}
)

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

target_link_libraries(${TERMCOLOR_TARGET}
  PRIVATE
  Qt5::Core
  Qt5::Gui
  Qt5::Widgets
  ${OpenCV_LIBS}
)

set_target_properties(${TERMCOLOR_TARGET} PROPERTIES
  LINK_FLAGS "-static"
)