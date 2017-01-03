all: linux windows

linux:
	gcc -o bin/linux_logsplitter src/logsplitter.c
	gcc -o bin/linux_loggenerator src/loggenerator.c

windows:
	i686-w64-mingw32-gcc -o bin/windows32_logsplitter.exe src/logsplitter.c
	i686-w64-mingw32-gcc -o bin/windows32_loggenerator.exe src/loggenerator.c

clean:
	rm bin/*
