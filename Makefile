
all:
	mkdir -p build
	gcc src/main.c src/mem.c -o build/out

clean:
	rm -f build/*

run:
	@./build/out
