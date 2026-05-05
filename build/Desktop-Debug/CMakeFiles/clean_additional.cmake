# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Minimax-tictactoe_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Minimax-tictactoe_autogen.dir/ParseCache.txt"
  "Minimax-tictactoe_autogen"
  )
endif()
