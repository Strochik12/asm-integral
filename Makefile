CC = gcc
ASM = nasm
CFLAGS = -Wall -Wextra -std=gnu99
ASMFLAGS = -f elf32
LDLIBS = -lm

# Имена файлов
NO_ASM_SOURCES = integral.c functions.c
NO_ASM_OBJECTS = $(NO_ASM_SOURCES:.c=.o)
NO_ASM_EXECUTABLE = no-asm-integral

TEST_SOURCES = integral.c test-functions.c
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)
TEST_EXECUTABLE = test-integral

C_SOURCES = integral.c
ASM_SOURCES = functions.asm
OBJECTS = $(C_SOURCES:.c=.o) $(ASM_SOURCES:.asm=.o)
EXECUTABLE = integral


ARGS =

# Компиляция .c файлов в .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

# Ассемблирование .asm файлов в .o
%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@ 



build: $(EXECUTABLE)

run:
	./$(EXECUTABLE) $(ARGS)

all: build build-test

no-asm-build: $(NO_ASM_EXECUTABLE)

no-asm-run:
	./$(NO_ASM_EXECUTABLE) $(ARGS)

no-asm-all: no-asm-build
	./$(NO_ASM_EXECUTABLE) $(ARGS)


build-test: $(TEST_EXECUTABLE)

test: build-test
	./$(TEST_EXECUTABLE) --test-root 1:2:1.5:1.6:0.0001:1.51678
	./$(TEST_EXECUTABLE) --test-root 1:3:-0.6:-0.5:0.0001:-0.58231
	./$(TEST_EXECUTABLE) --test-root 2:3:0.6:0.7:0.0001:0.6031
	./$(TEST_EXECUTABLE) --test-integral 1:-0.58231:1.51678:0.0001:4.3376514
	./$(TEST_EXECUTABLE) --test-integral 2:0.6031:1.51678:0.0001:1.5896628
	./$(TEST_EXECUTABLE) --test-integral 3:-0.58231:0.6031:0.0001:0.39102922

# Линковка всех .o файлов в исполняемый файл
$(NO_ASM_EXECUTABLE): $(NO_ASM_OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

$(TEST_EXECUTABLE): $(TEST_OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)


clean:
	rm -f $(NO_ASM_OBJECTS) $(NO_ASM_EXECUTABLE) $(TEST_OBJECTS) $(TEST_EXECUTABLE) $(OBJECTS) $(EXECUTABLE)

.PHONY: no-asm-all no-asm-build no-asm-run clean build-test test build run all