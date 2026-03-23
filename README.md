Command for Renode:

mach create
machine LoadPlatformDescription @platforms/cpus/stm32f104.repl
showAnalyzer sysbus.usart2
sysbus LoadELF <.elf's path>
start
