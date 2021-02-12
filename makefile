CC:=clang $(clang)
CFLAGS+=-pthread -O2 -g -Wall
PTHREAD+=-pthread
OBJS=$(patsubst %.c,%.o,$(wildcard *.c))
TARGET=game
bin: $(TARGET)

$(OBJS): %.o: %.c
	$(CC) -c $< $(CFLAGS) $(CPPFLAGS) -o $@

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(PTHREAD) $(LDFLAGS) -o $@

clean:
	$(RM) $(OBJS) $(TARGET)
