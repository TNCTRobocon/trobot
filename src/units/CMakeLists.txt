add_library(trobot_src_units
  STATIC
  motors.cpp
)

target_include_directories(trobot_src_units
  PUBLIC ${PROJECT_SOURCE_DIR}/inc
)