PATH=C:\Tools\Compilers\dm\bin;%PATH%
dmc.exe -c -g -Isource -mt -o+space source\kernel_main.cpp -obuild\kernel_main.obj 
dmc.exe -c -g -Isource -mt -o+space source\bios\video.cpp  -obuild\video.obj
dmc.exe -c -g -Isource -mt -o+space source\bios\disk.cpp   -obuild\disk.obj
dmc.exe -c -g -Isource -mt -o+space source\bios\keyboard.cpp -obuild\keyboard.obj
dmc.exe -c -g -Isource -mt -o+space source\std\str.cpp -obuild\str.obj
dmc.exe -c -g -Isource -mt -o+space source\ui\console.cpp  -obuild\console.obj
dmc.exe -c -g -Isource -mt -o+space source\ui\shell.cpp -obuild\shell.obj
dmc.exe -c -g -Isource -mt -o+space source\ui\commands\echo_command.cpp -obuild\echo_command.obj
dmc.exe -c -g -Isource -mt -o+space source\ui\commands\exit_command.cpp -obuild\exit_command.obj
dmc.exe -c -g -Isource -mt -o+space source\ui\commands\help_command.cpp -obuild\help_command.obj
dmc.exe -c -g -Isource -mt -o+space source\ui\commands\dir_command.cpp -obuild\dir_command.obj
dmc.exe -c -g -Isource -mt -o+space source\system\apm.cpp -obuild\apm.obj
dmc.exe -c -g -Isource -mt -o+space source\std\arr.cpp -obuild\arr.obj
dmc.exe -c -g -Isource -mt -o+space source\io\disk.cpp -obuild\io_disk.obj
dmc.exe -c -g -Isource -mt -o+space source\io\disk_cache.cpp -obuild\disk_cache.obj
dmc.exe -c -g -Isource -mt -o+space source\file_system\file.cpp -obuild\file.obj
dmc.exe -c -g -Isource -mt -o+space source\file_system\directory.cpp -obuild\directory.obj


nasm source\bootloader.asm -f bin -o bin\bootloader.bin
.\VC152\ML.EXE /AT /c source\kernel_point.asm
mv kernel_point.obj build\kernel_point.obj
optlink /TINY /NODEFAULTLIBRARYSEARCH build\kernel_point.obj build\kernel_main.obj build\video.obj build\disk.obj build\console.obj build\keyboard.obj build\str.obj build\shell.obj build\echo_command.obj build\help_command.obj build\exit_command.obj build\dir_command.obj build\apm.obj build\directory.obj build\file.obj build\disk_cache.obj build\io_disk.obj build\arr.obj
mv kernel_point.com bin\kernel_point.com
python boot_file_creator.py bin\bootloader.bin bin\kernel_point.com bin\image.bin
