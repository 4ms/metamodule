set( CMAKE_C_COMPILER arm-none-eabi-gcc )  
set( CMAKE_CXX_COMPILER arm-none-eabi-g++ ) 
set( CMAKE_ASM_COMPILER arm-none-eabi-as ) 
 
find_program(CMAKE_AR NAMES "arm-none-eabi-ar")  
mark_as_advanced(CMAKE_AR)   
find_program(CMAKE_RANLIB NAMES "arm-none-eabi-ranlib")
mark_as_advanced(CMAKE_RANLIB)
