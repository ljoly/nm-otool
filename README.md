nm-otool
=======

Overview
-------
The goal of this project is to recode commands nm and otool -t

Usage
-------
```
ft_nm [-uUjpg] [mach-O files ...]
ft_otool [mach-O files ...]
```

Flags (nm only)
-----------------------------
+ -u<br/>
    	Display undefined symbols only<br/>
+ -U<br/>
    	Do not display undefined symbols<br/>
+ -j<br/>
    	Display names only<br/>
+ -p<br/>
    	Display symbols without sort<br/>
+ -g<br/>
    	Display extern symbols only<br/>
