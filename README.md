# av-auto-switcher-1

An arduino UNO project to auto configure an AV system

# Dependencies

[~/dev/Arduino-IRremote]$ git remote -v
mariusoei	git@github.com:mariusoei/Arduino-IRremote.git (fetch)
mariusoei	git@github.com:mariusoei/Arduino-IRremote.git (push)
origin	git@github.com:z3t0/Arduino-IRremote.git (fetch)
origin	git@github.com:z3t0/Arduino-IRremote.git (push)

[~/dev/Arduino-IRremote]$ git branch -vv
* mariusoei-master fe200d6 [mariusoei/master] Adjust sendRC5x to be more similar to sendRC5
  master           eb7a0be [origin/master] #481 note (#484)

[~/dev/Arduino-IRremote]$ ls -al ~/Documents/Arduino/libraries/
total 32
drwxr-xr-x@ 18 ma  1820212269   612 18 May 12:09 IRLib2
drwxr-xr-x@  6 ma  1820212269   204 18 May 12:09 IRLibFreq
drwxr-xr-x@ 28 ma  1820212269   952  8 Jul 01:08 IRLibProtocols
drwxr-xr-x@  6 ma  1820212269   204 18 May 12:09 IRLibRecv
drwxr-xr-x@  6 ma  1820212269   204 18 May 12:09 IRLibRecvPCI
lrwxr-xr-x   1 ma  1820212269    34  7 Jul 23:27 IRremote -> ~/dev/Arduino-IRremote

# References

```
http://lirc.sourceforge.net/remotes/rc-5/RC-5-extented
// RC5
// # Bit   0    1   2   3    4    5    6    7    8    9    10   11   12   13
// #     | S |~C6 | T | A4 | A3 | A2 | A1 | A0 | C5 | C4 | C3 | C2 | C1 | C0 |
```

```
http://lirc.10951.n7.nabble.com/Marantz-RC5-22-bits-Extend-Data-Word-possible-with-lircd-conf-semantic-td9784.html
// BIT 0  1    2    3  4  5  6  7        8  9  10 11 12 13 14 15 16 17 18 19
// START,~C6,TOGGLE,S4,S3,S2,S1,S0,PAUSE,C5,C4,C3,C2,C1,C0,D5,D4,D3,D2,D1,D0
```

## Refs Not Used:
```
[m@mll1p04458 ~/dev/IRLib2]$ git remote -v
origin	git@github.com:cyborg5/IRLib2.git (fetch)
```
