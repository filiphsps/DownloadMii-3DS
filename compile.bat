@ECHO OFF
make clean
echo build ...
:: Using >NUL hides everything but the errors/warnings so you can spot them better
make>NUL
pause
:: Create cia file
:: ToDo™
:: makerom.exe -elf DownloadMii.elf -rsf DownloadMii.rsf -icon DownloadMii.icr -banner DownloadMii.bnr -o homebrew.cxi
:: makerom.exe -f cia -content DownloadMii.cxi:0:0 -o DownloadMii.cia