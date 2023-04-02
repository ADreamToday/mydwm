#!/bin/bash

fcitx5 &
compton &
xautolock -time `cat ~/autoScripts/locktime` -locker slock &





#if use image as wallpaper ,this one
feh --bg-scale ~/wallpaper/1.png &
#if video , this one
#xwinwrap -fs -nf -ov -- mplayer -shuffle -slave -input file=~/wallpaper/wallpaperTmp -loop 0 -fixed-vo -wid WID -nolirc `find ~/wallpaper/ -type f` &
