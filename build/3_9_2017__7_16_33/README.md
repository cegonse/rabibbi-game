# Build log (Wed Oct 18 2017)

* Generated by: César González (cegonse@gmail.com)

## Git Update:

* STDOUT:
Updating 5bdac47..6cdd700
Fast-forward
 game/character.c | 30 +++++++++++++++++++++---------
 game/character.h |  8 +++++---
 game/init.c      | 13 +++++++++++++
 game/main.c      | 10 +++++++---
 4 files changed, 46 insertions(+), 15 deletions(-)

* STDERR:
From github.com:cegonse/rabibbi-game
   5bdac47..6cdd700  master     -> origin/master

## Repo clean:

* STDOUT:
rm -f  -f out/gfx.o out/init.o out/character.o out/tween.o out/main.o out/sega.o out/rom_head.bin out/rom_head.o out/rom.out
rm -f  -f out.lst out/cmd_ out/rom.nm out/rom.wch out/rom.bin

* STDERR:

## Map files built from JSON to C:

**testmap.json**

* STDOUT:

* STDERR:

## Game and rescomp build:

* STDOUT:
mkdir -p src/boot
mkdir -p out
mkdir -p out/src
mkdir -p out/res
/opt/gendev/bin/m68k-elf-gcc  -m68000 -Wall -fno-builtin -Iinc -Isrc -Ires -I/opt/gendev/sgdk/inc -I/opt/gendev/sgdk/res -B/opt/gendev/sgdk/bin -c src/boot/rom_head.c -o out/rom_head.o
/opt/gendev/bin/m68k-elf-ld -T /opt/gendev/sgdk/md.ld -nostdlib --oformat binary -o out/rom_head.bin out/rom_head.o
/opt/gendev/bin/m68k-elf-gcc  -m68000 -Wall -fno-builtin -Iinc -Isrc -Ires -I/opt/gendev/sgdk/inc -I/opt/gendev/sgdk/res -B/opt/gendev/sgdk/bin -c src/boot/sega.s -o out/sega.o
/opt/gendev/bin/rescomp gfx.res gfx.s
rescomp v1.6

Resource: SPRITE character_def "./gfx/rabbibi.png" 3 3 NONE 0
--> executing plugin SPRITE...

Resource: PALETTE tiles_pal_def "./gfx/basictiles.png"
--> executing plugin PALETTE...

Resource: TILESET basic_tiles_def "./gfx/basictiles.png" NONE
--> executing plugin TILESET...

Resource: PALETTE rabbibi_tiles_pal_def "./gfx/rabbibi_tileset.png"
--> executing plugin PALETTE...

Resource: TILESET rabbibi_tiles_def "./gfx/rabbibi_tileset.png" NONE--> executing plugin TILESET...
/opt/gendev/bin/m68k-elf-gcc  -m68000 -Wall -fno-builtin -Iinc -Isrc -Ires -I/opt/gendev/sgdk/inc -I/opt/gendev/sgdk/res -B/opt/gendev/sgdk/bin -O3 -flto -fuse-linker-plugin -fno-web -fno-gcse -fno-unit-at-a-time -fomit-frame-pointer -c gfx.s -o out/gfx.o
/opt/gendev/bin/m68k-elf-gcc  -m68000 -Wall -fno-builtin -Iinc -Isrc -Ires -I/opt/gendev/sgdk/inc -I/opt/gendev/sgdk/res -B/opt/gendev/sgdk/bin -O3 -flto -fuse-linker-plugin -fno-web -fno-gcse -fno-unit-at-a-time -fomit-frame-pointer -c init.c -o out/init.o
/opt/gendev/bin/m68k-elf-gcc  -m68000 -Wall -fno-builtin -Iinc -Isrc -Ires -I/opt/gendev/sgdk/inc -I/opt/gendev/sgdk/res -B/opt/gendev/sgdk/bin -O3 -flto -fuse-linker-plugin -fno-web -fno-gcse -fno-unit-at-a-time -fomit-frame-pointer -c character.c -o out/character.o
/opt/gendev/bin/m68k-elf-gcc  -m68000 -Wall -fno-builtin -Iinc -Isrc -Ires -I/opt/gendev/sgdk/inc -I/opt/gendev/sgdk/res -B/opt/gendev/sgdk/bin -O3 -flto -fuse-linker-plugin -fno-web -fno-gcse -fno-unit-at-a-time -fomit-frame-pointer -c tween.c -o out/tween.o
/opt/gendev/bin/m68k-elf-gcc  -m68000 -Wall -fno-builtin -Iinc -Isrc -Ires -I/opt/gendev/sgdk/inc -I/opt/gendev/sgdk/res -B/opt/gendev/sgdk/bin -O3 -flto -fuse-linker-plugin -fno-web -fno-gcse -fno-unit-at-a-time -fomit-frame-pointer -c main.c -o out/main.o
echo "out/gfx.o out/init.o out/character.o out/tween.o out/main.o" > out/cmd_
/opt/gendev/bin/m68k-elf-gcc  -B/opt/gendev/sgdk/bin -n -T /opt/gendev/sgdk/md.ld -nostdlib out/sega.o @out/cmd_ /opt/gendev/sgdk/lib/libmd.a /opt/gendev/sgdk/lib/libgcc.a -o out/rom.out
Makefile:109: recipe for target 'out/rom.out' failed
rm gfx.s

* STDERR:
In file included from /opt/gendev/sgdk/inc/bmp.h:24:0,
                 from /opt/gendev/sgdk/inc/tools.h:13,
                 from /opt/gendev/sgdk/inc/genesis.h:12,
                 from character.h:4,
                 from character.c:1:
character.c: In function 'character_update':
/opt/gendev/sgdk/inc/maths.h:186:45: warning: statement with no effect [-Wunused-value]
 #define fix16Add(val1, val2)        ((val1) + (val2))
                                     ~~~~~~~~^~~~~~~~~
character.c:26:2: note: in expansion of macro 'fix16Add'
  fix16Add(ptr->vel_x, ax);
  ^~~~~~~~
/opt/gendev/sgdk/inc/maths.h:186:45: warning: statement with no effect [-Wunused-value]
 #define fix16Add(val1, val2)        ((val1) + (val2))
                                     ~~~~~~~~^~~~~~~~~
character.c:27:2: note: in expansion of macro 'fix16Add'
  fix16Add(ptr->vel_y, ay);
  ^~~~~~~~
main.c: In function 'main':
main.c:47:3: warning: implicit declaration of function 'character_joyToSpeed' [-Wimplicit-function-declaration]
   character_joyToSpeed(JOY_1, &(playerChara.accel_x), &(playerChara.accel_y));
   ^~~~~~~~~~~~~~~~~~~~
main.c:39:25: warning: variable 'secondPadState' set but not used [-Wunused-but-set-variable]
  u16 firstPadState = 0, secondPadState = 0;
                         ^~~~~~~~~~~~~~
main.c:39:6: warning: variable 'firstPadState' set but not used [-Wunused-but-set-variable]
  u16 firstPadState = 0, secondPadState = 0;
      ^~~~~~~~~~~~~
/tmp/cc1tguOP.ltrans0.ltrans.o: In function `main':
<artificial>:(.text.startup+0xfe): undefined reference to `character_joyToSpeed'
collect2: error: ld returned 1 exit status
make: *** [out/rom.out] Error 1

