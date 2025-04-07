@echo off
setlocal enabledelayedexpansion

REM === Конфигурация ===

REM Путь к g++.exe. Здесь он лежит в bin/, в той же папке, где и этот .bat
set COMPILER="../mingw64/bin/g++.exe"

REM Папка со скриптами (исходными .cpp)
set SCRIPT_DIR=scripts

REM Куда класть .dll
set OUT_DIR=build_scripts

REM Флаги компиляции
set FLAGS=-std=c++17 -Wall -O2 -shared -fPIC -DBUILDING_DLL

REM === Проверка наличия компилятора ===
if not exist %COMPILER% (
    echo [ОШИБКА] Компилятор не найден: %COMPILER%
    echo Убедись, что g++.exe лежит в папке bin рядом с этим .bat файлом.
    exit /b
)

REM === Создаем выходную папку ===
if not exist %OUT_DIR% (
    mkdir %OUT_DIR%
)

REM === Компилируем каждый .cpp в .dll ===
for %%f in (%SCRIPT_DIR%\*.cpp) do (
    set "FILE=%%~nf"
    echo [Компиляция] %%f -> %OUT_DIR%\!FILE!.dll
    %COMPILER% %FLAGS% %%f -o %OUT_DIR%\!FILE!.dll
)

echo.
echo [Готово] Все DLL собраны в %OUT_DIR%
