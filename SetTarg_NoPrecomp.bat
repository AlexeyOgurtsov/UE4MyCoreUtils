set location=C:\U4L\LB
set projectname=MyCoreUtils
set projectdirname=MyCoreUtils
set projectdir=%location%\%projectdirname%
set sniploc=C:\U4L\snip\
set TargUtil=%sniploc%SetTargUtil.bat
set ModePostfix=_NoPrecomp
start /B %TargUtil% %projectname% %projectdir% %ModePostfix%
