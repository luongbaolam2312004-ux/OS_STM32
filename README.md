Command for Renode:

mach create<br>
machine LoadPlatformDescription @platforms/cpus/stm32f104.repl<br>
showAnalyzer sysbus.usart2<br>
sysbus LoadELF <.elf's path> <br>
start <br>
