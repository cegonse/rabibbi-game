# Build log (Fri Nov 10 2017)

* Generated by: daruudaruu (exfer@alumni.uv.es)

## Git Update:

* STDOUT:
Updating 7ffb532..c15458b
Fast-forward
 game/gfx/shadows/shadow_drop_small.png | Bin 160 -> 163 bytes
 1 file changed, 0 insertions(+), 0 deletions(-)

* STDERR:
From github.com:cegonse/rabibbi-game
   7ffb532..c15458b  master     -> origin/master

## Repo clean:

* STDOUT:
rm -f  -f out/gui.o out/gfx.o out/init.o out/character.o out/tween.o out/room.o out/main.o out/gui_controller.o out/sega.o out/rom_head.bin out/rom_head.o out/rom.out
rm -f  -f out.lst out/cmd_ out/rom.nm out/rom.wch out/rom.bin

* STDERR:

## Map files built from JSON to C:

**pause_menu.json**

* STDOUT:

* STDERR:

**rabbibis_den_room_1.json**

* STDOUT:

* STDERR:

**rabbibis_den_room_2.json**

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
/opt/gendev/bin/rescomp gui.res gui.s
rescomp v1.6

Resource: SPRITE gui_hud_lifebar_begin_empty_def "./gfx/gui/hud_lifebar_begin_empty.png" 2 2 NONE 0
--> executing plugin SPRITE...

Resource: SPRITE gui_hud_lifebar_begin_filled_def "./gfx/gui/hud_lifebar_begin_filled.png" 2 2 NONE 0
--> executing plugin SPRITE...

Resource: SPRITE gui_hud_lifebar_end_empty_def "./gfx/gui/hud_lifebar_end_empty.png" 2 2 NONE 0
--> executing plugin SPRITE...

Resource: SPRITE gui_hud_lifebar_end_filled_def "./gfx/gui/hud_lifebar_end_filled.png" 2 2 NONE 0
--> executing plugin SPRITE...

Resource: SPRITE gui_hud_lifebar_segment_empty_def "./gfx/gui/hud_lifebar_segment_empty.png" 2 2 NONE 0
--> executing plugin SPRITE...

Resource: SPRITE gui_hud_lifebar_segment_filled_def "./gfx/gui/hud_lifebar_segment_filled.png" 2 2 NONE 0
--> executing plugin SPRITE...

Resource: SPRITE gui_hud_rabbit_def "./gfx/gui/hud_rabbit.png" 2 2 NONE 0
--> executing plugin SPRITE...

Resource: SPRITE gui_hud_carrot_def "./gfx/gui/hud_carrot.png" 2 2 NONE 0
--> executing plugin SPRITE...

Resource: SPRITE gui_hud_number_0_def "./gfx/gui/number_0.png" 1 1 NONE 0
--> executing plugin SPRITE...

Resource: SPRITE gui_hud_number_1_def "./gfx/gui/number_1.png" 1 1 NONE 0
--> executing plugin SPRITE...

Resource: SPRITE gui_hud_number_2_def "./gfx/gui/number_2.png" 1 1 NONE 0
--> executing plugin SPRITE...

Resource: SPRITE gui_hud_number_3_def "./gfx/gui/number_3.png" 1 1 NONE 0
--> executing plugin SPRITE...

Resource: SPRITE gui_hud_number_4_def "./gfx/gui/number_4.png" 1 1 NONE 0
--> executing plugin SPRITE...

Resource: SPRITE gui_hud_number_5_def "./gfx/gui/number_5.png" 1 1 NONE 0
--> executing plugin SPRITE...

Resource: SPRITE gui_hud_number_6_def "./gfx/gui/number_6.png" 1 1 NONE 0
--> executing plugin SPRITE...

Resource: SPRITE gui_hud_number_7_def "./gfx/gui/number_7.png" 1 1 NONE 0
--> executing plugin SPRITE...

Resource: SPRITE gui_hud_number_8_def "./gfx/gui/number_8.png" 1 1 NONE 0
--> executing plugin SPRITE...

Resource: SPRITE gui_hud_number_9_def "./gfx/gui/number_9.png" 1 1 NONE 0
--> executing plugin SPRITE...

Resource: PALETTE pause_menu_pal_def "./gfx/gui/menu_dialog_9slice.png"
--> executing plugin PALETTE...

Resource: TILESET pause_menu_tiles_def "./gfx/gui/menu_dialog_9slice.png" NONE
--> executing plugin TILESET...
/opt/gendev/bin/m68k-elf-gcc  -m68000 -Wall -fno-builtin -Iinc -Isrc -Ires -I/opt/gendev/sgdk/inc -I/opt/gendev/sgdk/res -B/opt/gendev/sgdk/bin -O3 -flto -fuse-linker-plugin -fno-web -fno-gcse -fno-unit-at-a-time -fomit-frame-pointer -c gui.s -o out/gui.o
/opt/gendev/bin/rescomp gfx.res gfx.s
rescomp v1.6

Resource: SPRITE character_def "./gfx/rabbibi.png" 3 3 NONE 0
--> executing plugin SPRITE...

Resource: PALETTE tiles_pal_def "./gfx/basictiles.png"
--> executing plugin PALETTE...

Resource: TILESET basic_tiles_def "./gfx/basictiles.png" NONE
--> executing plugin TILESET...

Resource: PALETTE rabbibisden_tiles_pal_def "./gfx/tileset_rabbibisden.png"
--> executing plugin PALETTE...

Resource: TILESET rabbibisden_tiles_def "./gfx/tileset_rabbibisden.png" NONE
--> executing plugin TILESET...
/opt/gendev/bin/m68k-elf-gcc  -m68000 -Wall -fno-builtin -Iinc -Isrc -Ires -I/opt/gendev/sgdk/inc -I/opt/gendev/sgdk/res -B/opt/gendev/sgdk/bin -O3 -flto -fuse-linker-plugin -fno-web -fno-gcse -fno-unit-at-a-time -fomit-frame-pointer -c gfx.s -o out/gfx.o
/opt/gendev/bin/m68k-elf-gcc  -m68000 -Wall -fno-builtin -Iinc -Isrc -Ires -I/opt/gendev/sgdk/inc -I/opt/gendev/sgdk/res -B/opt/gendev/sgdk/bin -O3 -flto -fuse-linker-plugin -fno-web -fno-gcse -fno-unit-at-a-time -fomit-frame-pointer -c init.c -o out/init.o
/opt/gendev/bin/m68k-elf-gcc  -m68000 -Wall -fno-builtin -Iinc -Isrc -Ires -I/opt/gendev/sgdk/inc -I/opt/gendev/sgdk/res -B/opt/gendev/sgdk/bin -O3 -flto -fuse-linker-plugin -fno-web -fno-gcse -fno-unit-at-a-time -fomit-frame-pointer -c character.c -o out/character.o
/opt/gendev/bin/m68k-elf-gcc  -m68000 -Wall -fno-builtin -Iinc -Isrc -Ires -I/opt/gendev/sgdk/inc -I/opt/gendev/sgdk/res -B/opt/gendev/sgdk/bin -O3 -flto -fuse-linker-plugin -fno-web -fno-gcse -fno-unit-at-a-time -fomit-frame-pointer -c tween.c -o out/tween.o
/opt/gendev/bin/m68k-elf-gcc  -m68000 -Wall -fno-builtin -Iinc -Isrc -Ires -I/opt/gendev/sgdk/inc -I/opt/gendev/sgdk/res -B/opt/gendev/sgdk/bin -O3 -flto -fuse-linker-plugin -fno-web -fno-gcse -fno-unit-at-a-time -fomit-frame-pointer -c room.c -o out/room.o
/opt/gendev/bin/m68k-elf-gcc  -m68000 -Wall -fno-builtin -Iinc -Isrc -Ires -I/opt/gendev/sgdk/inc -I/opt/gendev/sgdk/res -B/opt/gendev/sgdk/bin -O3 -flto -fuse-linker-plugin -fno-web -fno-gcse -fno-unit-at-a-time -fomit-frame-pointer -c main.c -o out/main.o
/opt/gendev/bin/m68k-elf-gcc  -m68000 -Wall -fno-builtin -Iinc -Isrc -Ires -I/opt/gendev/sgdk/inc -I/opt/gendev/sgdk/res -B/opt/gendev/sgdk/bin -O3 -flto -fuse-linker-plugin -fno-web -fno-gcse -fno-unit-at-a-time -fomit-frame-pointer -c gui_controller.c -o out/gui_controller.o
echo "out/gfx.o out/gui.o out/character.o out/main.o out/gui_controller.o out/tween.o out/init.o out/room.o" > out/cmd_
/opt/gendev/bin/m68k-elf-gcc  -B/opt/gendev/sgdk/bin -n -T /opt/gendev/sgdk/md.ld -nostdlib out/sega.o @out/cmd_ /opt/gendev/sgdk/lib/libmd.a /opt/gendev/sgdk/lib/libgcc.a -o out/rom.out
rm -f  out/cmd_
/opt/gendev/bin/m68k-elf-objcopy  -O binary out/rom.out out/rom.bin
/opt/gendev/bin/sizebnd out/rom.bin -sizealign 131072
rm gui.s gfx.s

* STDERR:
character.c: In function '__character_check_warp':
character.c:173:25: warning: initialization discards 'const' qualifier from pointer target type [-Wdiscarded-qualifiers]
    room_t *targetRoom = ROOM_LIST[room->warpTargetRooms[i]];
                         ^~~~~~~~~
character.c:174:4: warning: implicit declaration of function 'game_change_room_event' [-Wimplicit-function-declaration]
    game_change_room_event(targetRoom, room->warpTargetRoomsSpawn_x[i], room->warpTargetRoomsSpawn_y[i]);
    ^~~~~~~~~~~~~~~~~~~~~~
room.c: In function 'room_load':
room.c:9:6: warning: unused variable 'currentTile' [-Wunused-variable]
  u16 currentTile = 0;
      ^~~~~~~~~~~
In file included from room.c:1:0:
At top level:
room.h:12:22: warning: 'ROOM_LIST' defined but not used [-Wunused-variable]
 static const room_t *ROOM_LIST[MAX_ROOMS] = {
                      ^~~~~~~~~
In file included from gui_controller.h:6:0,
                 from main.c:7:
pause_menu.h:83:17: warning: initialization from incompatible pointer type [-Wincompatible-pointer-types]
  .paletteData = &pause_menu_tiles_def,
                 ^
pause_menu.h:83:17: note: (near initialization for 'pause_menu.paletteData')
pause_menu.h:82:34: warning: missing braces around initializer [-Wmissing-braces]
 static const room_t pause_menu = { .tilesetData = &pause_menu_tiles_def,
                                  ^
pause_menu.h:82:34: note: (near initialization for 'pause_menu')
main.c: In function 'main':
main.c:23:14: warning: assignment discards 'const' qualifier from pointer target type [-Wdiscarded-qualifiers]
  currentRoom = &rabbibis_den_room_1;
              ^
In file included from character.h:5:0,
                 from main.c:3:
At top level:
room.h:12:22: warning: 'ROOM_LIST' defined but not used [-Wunused-variable]
 static const room_t *ROOM_LIST[MAX_ROOMS] = {
                      ^~~~~~~~~
In file included from gui_controller.h:6:0,
                 from gui_controller.c:1:
pause_menu.h:83:17: warning: initialization from incompatible pointer type [-Wincompatible-pointer-types]
  .paletteData = &pause_menu_tiles_def,
                 ^
pause_menu.h:83:17: note: (near initialization for 'pause_menu.paletteData')
pause_menu.h:82:34: warning: missing braces around initializer [-Wmissing-braces]
 static const room_t pause_menu = { .tilesetData = &pause_menu_tiles_def,
                                  ^
pause_menu.h:82:34: note: (near initialization for 'pause_menu')

