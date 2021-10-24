add_library(trobot_src_parts
  STATIC
  pins.cpp
)

target_include_directories(trobot_src_parts
  PUBLIC ${PROJECT_SOURCE_DIR}/inc
)