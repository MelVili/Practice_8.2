# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Practice_8_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Practice_8_autogen.dir\\ParseCache.txt"
  "Practice_8_autogen"
  )
endif()
