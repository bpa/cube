@echo off

rem ** remove/create a test gadget folder
rd "%LOCALAPPDATA%\Microsoft\Windows Sidebar\Gadgets\cube.gadget\" /S /Q
md "%LOCALAPPDATA%\Microsoft\Windows Sidebar\Gadgets\cube.gadget\"

rem ** copy all of the files into test area
xcopy gadget "%LOCALAPPDATA%\Microsoft\Windows Sidebar\Gadgets\cube.gadget\" /y /s /q /EXCLUDE:exclude.txt

rem cd "%LOCALAPPDATA%\Microsoft\Windows Sidebar\Gadgets\cube\"
rem cabarc -r -p n "%HOMEPATH%\cube.gadget" *

