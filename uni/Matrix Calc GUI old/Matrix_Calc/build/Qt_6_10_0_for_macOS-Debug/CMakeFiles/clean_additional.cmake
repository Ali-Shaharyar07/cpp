# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Matrix_Calc_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Matrix_Calc_autogen.dir/ParseCache.txt"
  "Matrix_Calc_autogen"
  )
endif()
