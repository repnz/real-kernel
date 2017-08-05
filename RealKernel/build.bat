PATH=C:\Tools\Compilers\dm\bin;%PATH%
dmc.exe -c -g -Isource -mt -o+space source\kernel_main.cpp -oobj\kernel_main.obj 
dmc.exe -c -g -Isource -mt -o+space source\bios\video.cpp  -oobj\video.obj
dmc.exe -c -g -Isource -mt -o+space source\bios\disk.cpp   -oobj\disk.obj
dmc.exe -c -g -Isource -mt -o+space source\bios\keyboard.cpp -oobj\keyboard.obj
dmc.exe -c -g -Isource -mt -o+space source\std\str.cpp -oobj\str.obj
dmc.exe -c -g -Isource -mt -o+space source\ui\console.cpp  -oobj\console.obj
dmc.exe -c -g -Isource -mt -o+space source\ui\shell.cpp -oobj\shell.obj
dmc.exe -c -g -Isource -mt -o+space source\ui\commands\echo_command.cpp -oobj\echo_command.obj
dmc.exe -c -g -Isource -mt -o+space source\ui\commands\exit_command.cpp -oobj\exit_command.obj
dmc.exe -c -g -Isource -mt -o+space source\ui\commands\help_command.cpp -oobj\help_command.obj
dmc.exe -c -g -Isource -mt -o+space source\ui\commands\dir_command.cpp -oobj\dir_command.obj
dmc.exe -c -g -Isource -mt -o+space source\system\apm.cpp -oobj\apm.obj
dmc.exe -c -g -Isource -mt -o+space source\std\arr.cpp -oobj\arr.obj
dmc.exe -c -g -Isource -mt -o+space source\io\disk.cpp -oobj\io_disk.obj
dmc.exe -c -g -Isource -mt -o+space source\io\disk_cache.cpp -oobj\disk_cache.obj
dmc.exe -c -g -Isource -mt -o+space source\file_system\file.cpp -oobj\file.obj
dmc.exe -c -g -Isource -mt -o+space source\file_system\directory.cpp -oobj\directory.obj


nasm source\bootloader.asm -f bin -o bin\bootloader.bin
.\VC152\ML.EXE /AT /c source\kernel_point.asm
mv kernel_point.obj obj\kernel_point.obj
.\VC152\LINK.EXE /T /NODEFAULTLIBRARYSEARCH obj\kernel_point.obj obj\kernel_main.obj obj\video.obj obj\disk.obj obj\console.obj obj\keyboard.obj obj\str.obj obj\shell.obj obj\echo_command.obj obj\help_command.obj obj\exit_command.obj obj\dir_command.obj obj\apm.obj obj\directory.obj obj\file.obj obj\disk_cache.obj oobj\io_disk.obj obj\arr.obj
mv kernel_point.com bin\kernel_point.com
python boot_file_creator.py bin\bootloader.bin bin\kernel_point.com bin\image.bin
