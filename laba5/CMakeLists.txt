cmake_minimum_required(VERSION 3.16)

project(lab5 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Папки для выходных файлов
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Добавляем библиотеку BigIntLib
add_subdirectory(BigInt)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    # BigInt.cpp и BigInt.hpp НЕ включаем сюда - они в библиотеке
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(lab5
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(lab5 SHARED ${PROJECT_SOURCES})
    else()
        add_executable(lab5 ${PROJECT_SOURCES})
    endif()
endif()

# Подключаем библиотеки
target_link_libraries(lab5 PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    BigInt  # имя библиотеки из BigInt/CMakeLists.txt
)

# Пути для заголовочных файлов
target_include_directories(lab5 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/BigInt  # для доступа к BigInt.hpp
)

set_target_properties(lab5 PROPERTIES
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(lab5)
endif()
