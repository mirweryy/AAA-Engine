cmake_minimum_required(VERSION 3.15)
project(CrossPlatformBuild)

set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Путь к дополнительным файлам для копирования
set(EXTRA_FILES_DIR "${CMAKE_SOURCE_DIR}/copy_dir")
set(SDK_HEADER "${CMAKE_SOURCE_DIR}/src/AAAEngine.h")

# Получаем все исходники из src/
file(GLOB_RECURSE SRC_FILES "src/*.cpp")

# Выводим путь к сборке
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")

# Общие флаги
add_compile_options(-Wall -O2)

# Функция для копирования DLL в Windows сборку
function(copy_windows_dlls target dll_dir)
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${dll_dir}/libgcc_s_seh-1.dll
        ${dll_dir}/libstdc++-6.dll
        $<TARGET_FILE_DIR:${target}>
    )
endfunction()

# ---------- Linux Target ----------
if(UNIX)
    add_executable(linux_aaa ${SRC_FILES})
    target_link_libraries(linux_aaa PRIVATE dl)
    set_target_properties(linux_aaa PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/linux"
    )

    # Копирование заголовка SDK
    add_custom_command(TARGET linux_aaa POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDK_HEADER}"
        "${CMAKE_BINARY_DIR}/linux/scripts/AAAEngine.h"
        COMMENT "Copying SDK header to output directory (Linux)"
    )
    # Копирование всех файлов из EXTRA_FILES_DIR в целевую папку
    add_custom_command(TARGET linux_aaa POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${EXTRA_FILES_DIR} "${CMAKE_BINARY_DIR}/linux/"
        COMMENT "Copying extra files to Linux output directory"
    )
endif()

# ---------- Windows Target ----------
if(WIN32 OR CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_executable(win_aaa ${SRC_FILES})
    set_target_properties(win_aaa PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/windows"
    )

    set(MINGW_DLL_DIR "${CMAKE_SOURCE_DIR}/dlls")
    copy_windows_dlls(win_aaa ${MINGW_DLL_DIR})

    # Копирование заголовка SDK
    add_custom_command(TARGET win_aaa POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDK_HEADER}"
        "${CMAKE_BINARY_DIR}/windows/scripts/AAAEngine.h"
        COMMENT "Copying SDK header to output directory"
    )
    # Копирование всех файлов из EXTRA_FILES_DIR в целевую папку
    add_custom_command(TARGET win_aaa POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${EXTRA_FILES_DIR} "${CMAKE_BINARY_DIR}/windows/"
        COMMENT "Copying extra files to Windows output directory"
    )
endif()