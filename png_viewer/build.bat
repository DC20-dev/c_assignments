@echo off

if exist "bin" (
    RD /S /Q "bin"
)

MD "bin"
robocopy assets bin\assets /E > output.log
copy src\zlibwapi.dll bin > output.log
del output.log

clang -o bin\viewer.exe .\src\png_viewer.c .\src\collections.c .\src\png_decoder.c -D_CRT_SECURE_NO_WARNINGS -I.\include\ -I.\zlib\ -L.\zlib\ -lzlibwapi
@echo on