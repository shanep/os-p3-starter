if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/solution.cpp)
  add_library(lab SHARED solution.cpp)
else()
  add_library(lab SHARED lab.cpp)
endif()


include(GenerateExportHeader)
generate_export_header(lab)
configure_file(labconfig.h.in labconfig.h)

target_include_directories(lab PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)

## Set compiler flags for the library
target_compile_options(lab PRIVATE
  "$<$<CXX_COMPILER_ID:MSVC>:/W4;/WX>"
  "$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall;-Wextra;-Werror;-pedantic;>"
)

add_sanitizers(lab)

add_executable(myprogram main.cpp)
target_link_libraries(myprogram PRIVATE lab)

install(TARGETS lab DESTINATION lib)
install(FILES lab.h DESTINATION include)