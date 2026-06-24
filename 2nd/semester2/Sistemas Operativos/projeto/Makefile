CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -Iinclude `pkg-config --cflags glib-2.0` -fsanitize=address -g
LDFLAGS = `pkg-config --libs glib-2.0` -fsanitize=address

all: folders controller runner

controller: bin/controller
runner: bin/runner

folders:
	@mkdir -p src include obj bin tmp

bin/controller: obj/main_controller.o obj/controller.o obj/process.o obj/parser.o obj/controller_pipe.o obj/common.o
		$(CC) $^ -o $@ $(LDFLAGS)

bin/runner: obj/main_runner.o obj/runner.o obj/process.o obj/parser.o obj/runner_pipe.o obj/common.o
		$(CC) $^ -o $@ $(LDFLAGS)

obj/%.o: src/%.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -rf obj/* tmp/* bin/*