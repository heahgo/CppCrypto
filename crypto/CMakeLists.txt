add_subdirectory(aes)

set(SUB_LIBS sub1 sub2 sub3)
foreach(LIB_ITEM ${SUB_LIBS})
  set(LIB_LIST ${LIB_LIST} $<TARGET_OBJECTS:aes${LIB_ITEM}>)
endforeach()
add_library(aes STATIC ${LIB_LIST})
