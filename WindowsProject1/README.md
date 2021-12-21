# Компиляция проекта
### Компиляция wxWidget
Скачиваете wxWidget с [оффициального сайта](https://www.wxwidgets.org/downloads/ ) и распоковываете содержимое в удобное для вас место.
Переходите в папку `build/msw` и при помощи Visual Studio открываете файл проекта (`wx_vc*.sln`).
В открытом проекте переходите по пути `Build -> Batch Build`, в открывшемся диалоге выбираете все компоненты (`Select All`) и нажимаете `Build` и ожидаете пока скомпилируются все необходимые библиотеки.
### Настройка проекта
После качаете проект с репозитория, открываете в Visual Studio и в настройках проекта указываете
1. Include директории: `C/C++ -> General -> Additional Include Directories` (`.../include и .../include/msvc`)
2. Директорию с библиотеками: `Linker -> General -> Additional Library Directories` (`.../lib/vc_x64_lib` или `D:\sdks\wxwidg\lib\vc_lib`)

Вместо `...` указываете свой путь до папки с wxWidget
