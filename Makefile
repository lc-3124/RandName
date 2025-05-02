BEAR_CC = x86_64-w64-mingw32-g++
CC = wine "C:\\Program Files\\RedPanda-Cpp\\mingw64\\bin\\g++.exe"

INPUT = main.cpp
OUTPUT = main.exe


FLAG =	-Wl,--start-group \
		-lgraphics \
		-lgdi32 -lgdiplus \
		-lole32 -loleaut32 -luuid \
		-lmsvcrt -lmingwex \
		-lkernel32 -luser32 \
		-Wl,--end-group \
		-static

all: making  running

making:
	${CC} ${INPUT} -o ${OUTPUT} ${FLAG}
	
bear:
	${BEAR_CC} ${INPUT} -o ${OUTPUT} ${FLAG}

running:
	wine ${OUTPUT}
	
