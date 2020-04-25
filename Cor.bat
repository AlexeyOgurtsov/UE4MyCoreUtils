C:
start /B SetTarg.bat
set location=C:\U4L\LB
set projectname=MyCoreUtils
set projectdirname=MyCoreUtils
set configpostfix=Editor
set sniploc=C:\U4L\Snip
call %sniploc%\MyBuild.bat %projectname%%configpostfix% %location%\%projectdirname%\%projectname%
