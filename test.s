
.load

_start:
add $b, $c
ld ($hl),$c
loop:
jp loop
bla
daa


