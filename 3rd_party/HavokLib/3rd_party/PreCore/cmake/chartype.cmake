if(NOT CHAR_TYPE)
  if(WIN32)
    set(CHAR_TYPE UNICODE)
  else()
    set(CHAR_TYPE CHAR)
  endif()
endif()

if(CHAR_TYPE STREQUAL UNICODE)
  message(STATUS "Compiling with wchar_t.")
  add_definitions(-D_UNICODE -DUNICODE)
else()
  message(STATUS "Compiling with char.")
endif()