#
#
#

set (EXE_SRC
  #src.cpp
  showbin.cpp
  )

add_library(exeLib ${EXE_SRC})

target_include_directories(exeLib PUBLIC ../inc)

target_compile_features(exeLib PUBLIC cxx_std_11)
