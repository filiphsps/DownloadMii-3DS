@echo off
for %%* in (.) do set ProjectName=%%~n*
echo Building %ProjectName%
make clean
:: Using >NUL hides everything but the errors/warnings so you can spot them better
make>NUL
:: Create .CIA file
arm-none-eabi-strip.exe %ProjectName%.elf
tools\makerom.exe -f cci -rsf tools\downloadmii.rsf -target d -exefslogo -elf %ProjectName%.elf -icon assets\icon.bin -banner assets\banner.bin -o %ProjectName%.3ds
tools\makerom.exe -f cia -o %ProjectName%.cia -elf %ProjectName%.elf -rsf tools\cia.rsf -icon assets\icon.bin -banner assets\banner.bin -exefslogo -target t
pause