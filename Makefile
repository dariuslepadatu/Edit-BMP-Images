build: Task.c
	gcc Task.c -o bmp -Wall -Wextra

run: ./bmp

clean:
	rm -f bmp
