mkdir .\bin
mkdir .\bin\Resources\
mkdir .\tmp\win32

copy .\lib\win32\*.dll .\bin\

windres ./src/SwinGame.rc ./src/GameLauncher.res

xcopy .\Resources\* .\bin\Resources\ /E /Y