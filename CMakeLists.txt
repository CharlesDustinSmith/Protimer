# The minimum required CMake vrsion
cmake_minimum_required( VERSION 3.28.1 )
# Defining the name of the project, the version, and language permitted
project(
    Protimer
    VERSION 1.0.0
    LANGUAGES C CXX
)
# Setting the C and C++ Standard
set( CMAKE_C_STANDARD 11 )
set( CMAKE_CXX_STANDARD 17 )
# The CMAKE_C_STANDARD_REQUIRED CMAKE_CXX_STANDARD_REQUIRED variables control whether the specified C++ standard version must be strictly adhered to
set( CMAKE_C_STANDARD_REQUIRED ON )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
# The CMAKE_C_EXTENSIONS and CMAKE_C_EXTENSIONS variables controls whether compiler-specific extensions are enabled using a particular C/C++ standards
set( CMAKE_C_EXTENSIONS ) 
set( CMAKE_CXX_EXTENSIONS )
# Directory containing the sketch (.ino file) or source files
set( ARDUINO_SKETCH_DIR ${CMAKE_SOURCE_DIR} )
# FQBN (Fully Qualified Board Name) of your board
# You can discover this with `arduino-cli board list`; the CLI docs show the FQBN option  as `-b/--fqbn`:contentReference[oaicite:1]{index=1}
set( ARDUINO_BOARD arduino:mbed_portenta:envie_m7 )
# Output directory for build products
set( BUILD_DIR ${CMAKE_BINARY_DIR}/protimer_build )
# Compile target - calls arduino-cli compile 
add_custom_target(compile_protimer
    COMMAND arduino-cli compile 
            --fqbn ${ARDUINO_BOARD} 
            --build-path ${BUILD_DIR} 
            ${ARDUINO_SKETCH_DIR}
    COMMENT "Compiling sketch with Arduino CLI"
)
# Upload target - depends on successful compile, then calls arduino-cli upload
# Replace COM5 with the port shown by `arduino-cli board list`.
add_custom_target(upload_protimer
    COMMAND arduino-cli upload 
            -p COM5 
            --fqbn ${ARDUINO_BOARD} 
            --input-dir ${BUILD_DIR} 
            ${ARDUINO_SKETCH_DIR}
    DEPENDS compile_protimer
    COMMENT "Uploading sketch to board"
)