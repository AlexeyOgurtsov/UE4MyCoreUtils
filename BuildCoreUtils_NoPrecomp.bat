D:
set location=D:\UNR_SCRIPT\LIB
set projectname=MyCoreUtils
set projectdirname=MyCoreUtils
set configpostfix=Editor_NoPrecomp
set sniploc=D:\UNR_SCRIPT\SNIPPETS
call %sniploc%\MyBuild.bat %projectname%%configpostfix% %location%\%projectdirname%\%projectname%
