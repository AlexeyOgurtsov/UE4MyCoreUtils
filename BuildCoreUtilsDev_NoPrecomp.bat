C:
start /B MyCleanCoreUtils.bat
start /B SetTarg_NoPrecomp.bat
set location=C:\U4L\LB
set projectname=MyCoreUtils
set projectdirname=MyCoreUtils
set configpostfix=Editor
set sniploc=C:\U4L\Snip
call %sniploc%\MyBuildDev.bat %projectname%%configpostfix% %location%\%projectdirname%\%projectname%
