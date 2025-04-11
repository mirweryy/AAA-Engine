#!/bin/bash

# Путь к корню проекта (где находится CMakeLists.txt)
PROJECT_DIR=$(pwd)

# Директория для сборки
BUILD_DIR="$PROJECT_DIR/build"

# Создание директории для сборки, если она не существует
if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
    echo "Создана директория для сборки: $BUILD_DIR"
fi

# Переход в директорию для сборки
cd "$BUILD_DIR"

# Запуск CMake для конфигурации проекта
echo "Конфигурирование проекта с использованием CMake..."
cmake .. -DCMAKE_TOOLCHAIN_FILE=../mingw-toolchain.cmake -DCMAKE_BUILD_TYPE=Release

# Проверка, если cmake завершился успешно
if [ $? -eq 0 ]; then
    # Сборка проекта
    echo "Сборка проекта с использованием CMake..."
    cmake --build . --target win_aaa
else
    echo "Ошибка при конфигурации проекта. Завершаю работу."
    exit 1
fi
