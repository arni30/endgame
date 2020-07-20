CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic
INC = inc/{entity.h,entity_factory.h,entity_manager.h,hash_table.h,hash_table_test.h,resource_manager.h,sdl_util.h,sprite.h,string_util.h,tile_map.h,vec2.h,minilib.h,header.h,head.h}
INCD = inc
INCI = src/
INCC = src/{entity.h,entity_factory.h,entity_manager.h,hash_table.h,hash_table_test.h,resource_manager.h,sdl_util.h,sprite.h,string_util.h,tile_map.h,vec2.h,minilib.h,header.h,head.h}
SRC = src/{catgame.c,entity.c,entity_factory.c,entity_manager.c,hash_table.c,hash_table_test.c,resource_manager.c,sdl_util.c,sprite.c,string_util.c,tile_map.c,duo.c,endgame.c,solohardmode.c,solomode.c,simple.c,coingame.c,mx_strlen.c,sdlsnake.c}
OUT = endgame
IN = endgame_in
SDL = -I framework/SDL2.framework/Headers -F framework -framework SDL2 -rpath framework -I framework/SDL2_image.framework/Headers -F framework -framework SDL2_image -rpath framework -I framework/SDL2_mixer.framework/Headers -F framework -framework SDL2_mixer -rpath framework -I framework/SDL2_ttf.framework/Headers -F framework -framework SDL2_ttf -rpath framework

all:
	clang $(CFLAGS) $(SDL) -o $(OUT) $(SRC) -I $(INCD)

install: all
	cp -f $(OUT) $(IN)

uninstall:
	rm -f $(IN)

clean:
	rm -f $(OUT) $(INCC)

reinstall: clean all uninstall install
