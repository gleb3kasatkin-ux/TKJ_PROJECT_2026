# TKJHAT_SDK

# Define app name once
set(APP_NAME TKJHAT_SDK)

# ---- sources ----
# Explicit sources + glob only for the 3rd-party folder
file(GLOB OPENPDM_SRCS CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/OpenPDM2PCM/*.c"
)

# Generate a library 
add_library(${APP_NAME} STATIC
  src/sdk.c
  src/ssd1306.c
  src/pdm/pdm_microphone.c
  ${OPENPDM_SRCS}
)

# ---- headers / include paths ----
# Public API headers live in include/  -> consumers: #include <tkjhat/sdk.h>, "ssd1306.h", etc.
target_include_directories(${APP_NAME}
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src               
)

# ---- PIO code assembler for the mic ----
pico_generate_pio_header(${APP_NAME}
  ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/pdm_microphone.pio
)

# ---- link dependencies used by implementation ----
# TODO: Check if all those are really needed
target_link_libraries(${APP_NAME} PUBLIC
  pico_stdlib
  FreeRTOS-Kernel
  FreeRTOS-Kernel-Heap4
  hardware_i2c
  hardware_pio
  hardware_dma
  hardware_adc 
  hardware_pwm
  hardware_gpio
   # hardware_spi       # uncomment if any source uses SPI
  # hardware_timer     # uncomment if you use timer APIs
)

# (Optional) tighten C standard
target_compile_features(${APP_NAME} PUBLIC c_std_11)
message("Added support for the  TKJHAT_SDK library")


#Documentation
find_package(Doxygen QUIET)

if (DOXYGEN_FOUND)
  add_custom_target(tkjhat-doc
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs
    COMMENT "Generating TKJHAT SDK documentation with Doxygen"
    VERBATIM)
else()
  message(STATUS "Doxygen not found — 'tkjhat-doc' target will be unavailable.")
endif()
