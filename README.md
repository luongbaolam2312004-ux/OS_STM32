PlatformIO.ini configuration:

[env:bluepill_f103c6]<br>
platform = ststm32<br>
board = bluepill_f103c6<br>
board_build.ldscript = linker_script.ld<br>
build_flags = -nostdlib -ffreestanding<br>

Command for Renode:

mach create<br>
machine LoadPlatformDescription @platforms/cpus/stm32f104.repl<br>
showAnalyzer sysbus.usart2<br>
sysbus LoadELF <.elf's path> <br>
start <br>
