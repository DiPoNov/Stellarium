cmake_minimum_required(VERSION 3.16)
project(ObliquityControl)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src)  # путь к core заголовкам Stellarium

add_library(ObliquityControl MODULE
    src/ObliquityControlModule.cpp
    src/ObliquityControlModule.hpp
)

target_link_libraries(ObliquityControl
    PRIVATE
      StellariumCore
      Qt5::Widgets
)

# Установка module.ini в директорию плагина
install(FILES module.ini DESTINATION ${CMAKE_INSTALL_DATADIR}/stellarium/plugins/ObliquityControl)
