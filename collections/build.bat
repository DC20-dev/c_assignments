@echo off

if exist "bin" (
    RD /S /Q "bin"
)

MD "bin"

clang -o bin\test_collections.exe -Iinclude .\test\test_collections.c .\src\collections.c