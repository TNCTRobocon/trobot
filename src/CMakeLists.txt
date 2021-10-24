add_subdirectory(parts)
add_subdirectory(units)
add_library(trobot trb.cpp)
target_link_libraries(trobot trobot_src_parts trobot_src_units)