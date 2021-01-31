CC:=clang $(clang)
CFLAGS+=-O2 -g -Wall
OBJS=$(patsubst %.c,%.o,$(wildcard *.c))
TARGET=game
bin: $(TARGET)

$(OBJS): %.o: %.c
	$(CC) -c $< $(CFLAGS) $(CPPFLAGS) -o $@

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

clean:
	$(RM) $(OBJS) $(TARGET)
