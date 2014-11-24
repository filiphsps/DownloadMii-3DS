@ECHO OFF
REM This file is used by the build server!
make clean
make
pause
REM Create cia file
REM makerom.exe -elf DownloadMii.elf -rsf DownloadMii.rsf -icon DownloadMii.icr -banner DownloadMii.bnr -o homebrew.cxi
REM makerom.exe -f cia -content DownloadMii.cxi:0:0 -o DownloadMii.cia