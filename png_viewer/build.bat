@echo off

if exist "bin" (
    RD /S /Q "bin"
)

MD "bin"
robocopy assets bin\assets /E > output.log
copy src\zlibwapi.dll bin > output.log
copy src\SDL2.dll bin > output.log
del output.log

clang -o bin\viewer.exe .\src\*.c -D_CRT_SECURE_NO_WARNINGS -I.\include\ -I.\zlib\ -L.\zlib\ -lzlibwapi -I.\sdl\ -I.\sdl\include\ -L.\sdl\ -lSDL2
@echo on