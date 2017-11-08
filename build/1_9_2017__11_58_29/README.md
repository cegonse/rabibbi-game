# Build log (Mon Oct 30 2017)

* Generated by: César González (cegonse@gmail.com)

## Git Update:

* STDOUT:
Updating d0f9e4a..4d92e3b
Fast-forward
 game/character.c                              |  35 ++++++
 game/character.h                              |   1 +
 game/main.c                                   |  31 ++++-
 game/rabbibis_den_room_1.h                    |  57 ---------
 game/room.h                                   |  20 ++--
 game/room_definition.h                        |  29 +++++
 game/rooms/rabbibis_den_room_1.h              |  36 +++++-
 game/rooms/rabbibis_den_room_2.h              | 155 ++++++++++++++++++++++++
 maps/{room1.json => rabbibis_den_room_1.json} |  88 +++++++++++++-
 maps/rabbibis_den_room_2.json                 | 166 ++++++++++++++++++++++++++
 maps/testmap.json                             |  50 --------
 tools/tiled2c.js                              | 113 ++++++++++++++++--
 12 files changed, 639 insertions(+), 142 deletions(-)
 delete mode 100644 game/rabbibis_den_room_1.h
 create mode 100644 game/room_definition.h
 create mode 100644 game/rooms/rabbibis_den_room_2.h
 rename maps/{room1.json => rabbibis_den_room_1.json} (70%)
 create mode 100644 maps/rabbibis_den_room_2.json
 delete mode 100644 maps/testmap.json

* STDERR:
From github.com:cegonse/rabibbi-game
   d0f9e4a..4d92e3b  master     -> origin/master

## Repo clean:

* STDOUT:
rm -f  -f out/gui.o out/gfx.o out/init.o out/character.o out/tween.o out/room.o out/main.o out/gui_controller.o out/sega.o out/rom_head.bin out/rom_head.o out/rom.out
rm -f  -f out.lst out/cmd_ out/rom.nm out/rom.wch out/rom.bin

* STDERR:

## Map files built from JSON to C:

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
character.c:179:25: warning: initialization discards 'const' qualifier from pointer target type [-Wdiscarded-qualifiers]
    room_t *targetRoom = ROOM_LIST[room->warpTargetRooms[i]];
                         ^~~~~~~~~
character.c:180:4: warning: implicit declaration of function 'game_change_room_event' [-Wimplicit-function-declaration]
    game_change_room_event(targetRoom, room->warpTargetRoomsSpawn_x[i], room->warpTargetRoomsSpawn_y[i]);
    ^~~~~~~~~~~~~~~~~~~~~~
In file included from room.c:1:0:
room.h:11:22: warning: 'ROOM_LIST' defined but not used [-Wunused-variable]
 static const room_t *ROOM_LIST[MAX_ROOMS] = {
                      ^~~~~~~~~
main.c: In function 'main':
main.c:24:14: warning: assignment discards 'const' qualifier from pointer target type [-Wdiscarded-qualifiers]
  currentRoom = &rabbibis_den_room_1;
              ^
main.c:31:6: warning: variable 'secondPadState' set but not used [-Wunused-but-set-variable]
  u16 secondPadState = 0;
      ^~~~~~~~~~~~~~
At top level:
main.c:12:20: warning: 'playerTwoCharacter' defined but not used [-Wunused-variable]
 static character_t playerTwoCharacter;
                    ^~~~~~~~~~~~~~~~~~
main.c:10:11: warning: 'game_state' defined but not used [-Wunused-variable]
 static u8 game_state = GAME_STATE_INIT;
           ^~~~~~~~~~
In file included from character.h:5:0,
                 from main.c:3:
room.h:11:22: warning: 'ROOM_LIST' defined but not used [-Wunused-variable]
 static const room_t *ROOM_LIST[MAX_ROOMS] = {
                      ^~~~~~~~~
