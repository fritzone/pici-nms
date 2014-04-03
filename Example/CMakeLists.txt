set(project pnms-async-example)

set(${project}_files
    ${CMAKE_CURRENT_SOURCE_DIR}/AsyncExample.cpp
)

include_directories(../libnms)

add_executable(${project} ${${project}_files} )

target_link_libraries(${project} nms)