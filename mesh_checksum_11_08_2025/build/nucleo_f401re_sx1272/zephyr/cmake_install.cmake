# Install script for directory: C:/Users/ZainSiddiqui/zephyrproject/external/zephyr

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Zephyr-Kernel")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/Users/ZainSiddiqui/.zephyr_ide/toolchains/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-objdump.exe")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/zephyr/arch/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/zephyr/lib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/zephyr/soc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/zephyr/boards/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/zephyr/subsys/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/zephyr/drivers/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/acpica/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/cmsis/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/cmsis-dsp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/cmsis-nn/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/cmsis_6/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/fatfs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/adi/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/hal_afbr/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/hal_ambiq/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/atmel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/hal_bouffalolab/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/hal_espressif/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/hal_ethos_u/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/hal_gigadevice/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/hal_infineon/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/hal_intel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/microchip/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/hal_nordic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/nuvoton/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/hal_nxp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/openisa/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/quicklogic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/hal_renesas/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/hal_rpi_pico/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/hal_silabs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/hal_st/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/hal_stm32/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/hal_tdk/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/hal_telink/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/ti/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/hal_wch/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/hal_wurthelektronik/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/xtensa/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/hostap/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/liblc3/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/libmctp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/libmetal/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/littlefs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/loramac-node/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/lvgl/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/mbedtls/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/mcuboot/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/mipi-sys-t/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/nrf_wifi/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/open-amp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/openthread/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/percepio/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/picolibc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/segger/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/tinycrypt/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/trusted-firmware-a/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/trusted-firmware-m/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/uoscore-uedhoc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/zcbor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/modules/nrf_hw_models/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/zephyr/kernel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/zephyr/cmake/flash/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/zephyr/cmake/usage/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/zephyr/cmake/reports/cmake_install.cmake")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/ZainSiddiqui/zephyrproject/mesh_checksum_11_08_2025/build/nucleo_f401re_sx1272/zephyr/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
