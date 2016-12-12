
.load

_start:
nop 
stop
ld $b, $d
stop
ld $a, 8
ld $b, _start
nop
halt
nop

