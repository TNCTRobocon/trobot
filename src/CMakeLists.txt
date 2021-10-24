add_subdirectory(parts)

add_library(trobot trb.cpp)
target_link_libraries(trobot trobot_src_parts)