cmake_minimum_required(VERSION 3.15)
project(CrossPlatformBuild)

set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Путь к дополнительным файлам для копирования
set(EXTRA_FILES_DIR "${CMAKE_SOURCE_DIR}/copy_dir")

# Получаем все исходники из src/core
file(GLOB_RECURSE SRC_FILES "src/core/*.cpp")

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
# if(UNIX)
#     add_executable(linux_aaa ${SRC_FILES})
#     target_link_libraries(linux_aaa PRIVATE dl)
#     set_target_properties(linux_aaa PROPERTIES
#         RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/linux"
#     )

#     # Копирование всех файлов из EXTRA_FILES_DIR в целевую папку
#     add_custom_command(TARGET linux_aaa POST_BUILD
#         COMMAND ${CMAKE_COMMAND} -E copy_directory
#         ${EXTRA_FILES_DIR} "${CMAKE_BINARY_DIR}/linux/"
#         COMMENT "Copying extra files to Linux output directory"
#     )
# endif()

# ---------- Windows Target ----------
if(WIN32 OR CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # core
    add_library(Core SHARED ${SRC_FILES})
    target_compile_definitions(Core PRIVATE CORE_EXPORT)
    target_include_directories(Core PUBLIC "${CMAKE_SOURCE_DIR}/src/include")
    set_target_properties(Core PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/windows")

    # win_aaa — главный EXE, включает и AAAEngine.cpp
    add_executable(win_aaa
        "${CMAKE_SOURCE_DIR}/src/AAAEngine.cpp"
    )

    # Линкуем с Core.dll
    target_link_libraries(win_aaa PRIVATE Core)

    # Инклуды
    target_include_directories(win_aaa PRIVATE "${CMAKE_SOURCE_DIR}/src/include")


    set_target_properties(win_aaa PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/windows"
    )

    set(MINGW_DLL_DIR "${CMAKE_SOURCE_DIR}/dlls")
    copy_windows_dlls(win_aaa ${MINGW_DLL_DIR})

    # Копирование всех файлов из EXTRA_FILES_DIR в целевую папку
    add_custom_command(TARGET win_aaa POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${EXTRA_FILES_DIR} "${CMAKE_BINARY_DIR}/windows/"
        COMMENT "Copying extra files to Windows output directory"
    )
endif()

# Пути
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src/include")
set(SDK_INCLUDE_DIR "${CMAKE_BINARY_DIR}/windows/sdk/include")

# Создаём папку sdk/include, если не существует
file(MAKE_DIRECTORY "${SDK_INCLUDE_DIR}")

# Ищем все .h файлы в src и всех его подкаталогах
file(GLOB_RECURSE HEADER_FILES "${SRC_DIR}/*.h")

set(COPIED_HEADERS "")

foreach(src ${HEADER_FILES})
    # Получаем имя файла без пути
    get_filename_component(file_name "${src}" NAME)

    # Куда копировать — без папок
    set(dst "${SDK_INCLUDE_DIR}/${file_name}")

    # Команда копирования
    add_custom_command(
        OUTPUT "${dst}"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${src}" "${dst}"
        DEPENDS "${src}"
        COMMENT "Copying ${file_name} to sdk/include"
        VERBATIM
    )

    list(APPEND COPIED_HEADERS "${dst}")
endforeach()

# Цель, которая будет запускать копирование
add_custom_target(copy_headers ALL DEPENDS ${COPIED_HEADERS})

add_dependencies(win_aaa copy_headers)