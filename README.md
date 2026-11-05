# CMakeProject_Demo
A step by step guidance to use Cmake(Cross-platform make) to build large-scale projects 

# User Guide
Use cmake to generate makefile
```
# How to choose <makefile generator>?
# Linux gcc/gpp:Unix Makefiles, Windows minGW:MinGW Makefiles

cd wrapper
cmake -G "<makefile generator>" ..
```
Execute makefile to build source code into executables
```
cmake --build . # generate execuables in current dir
cmake --install . # After successful build, generate execuables in "install" folder from the root
```

# How to use
Execute NumericalProject under `wrapper`
```
#Linux
./main/NumericalProject
../install/bin/NumericalProject
#windows
main\NumericalProject
..\install\bin\NumericalProject
```
Execute test_math under `wrapper`
```
ctest
#linux
../install/bin/test_math
#windows
..\install\bin\test_math
```
