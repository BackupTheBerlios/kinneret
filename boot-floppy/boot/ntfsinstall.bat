@echo off
date /t >> c:\boot\ntfsinstall.log
time /t >> c:\boot\ntfsinstall.log
echo -------------- >> C:\boot\ntfsinstall.log
c:\kinneret-boot\ntfsinstall -d (hd0,0) -1 c:/boot/stage1 -2 c:/boot/stage2 -m c:/boot/menu.lst >> c:\boot\ntfsinstall.log
echo ==================================================== >> C:\boot\ntfsinstall.log
echo. >> c:\boot\ntfsinstall.log