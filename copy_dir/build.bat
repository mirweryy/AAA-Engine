@echo off
setlocal enabledelayedexpansion

REM === Конфигурация ===

REM Путь к g++.exe. Здесь он лежит в bin/, в той же папке, где и этот .bat
set COMPILER="../mingw64/bin/g++.exe"

REM Папка со скриптами (исходными .cpp)
set SCRIPT_DIR="../scripts"

REM Куда класть .dll
set OUT_DIR=build_scripts

REM Флаги компиляции

REM === Проверка наличия компилятора ===
if not exist %COMPILER% (
    echo [ERROR] Compiler not found: %COMPILER%
    exit /b
)

REM === Создаем выходную папку ===
if not exist %OUT_DIR% (
    mkdir %OUT_DIR%
)

REM === Компилируем каждый .cpp в .dll ===
for %%f in (%SCRIPT_DIR%\*.cpp) do (
    set "FILE=%%~nf"
    echo [Compilation] %%f -> %OUT_DIR%\!FILE!.dll
    %COMPILER% -std=c++17 -I"sdk/include" -o %OUT_DIR%\!FILE!.dll %%f libCore.dll -L"." -lCore -shared -fPIC -DBUILDING_DLL
)

echo.
echo [Done] All .dll compiled into %OUT_DIR%
pause