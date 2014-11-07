OBJECTS := test1.o signal_rt.o
CFLAGS += -Wall
LIBS += -lrt
TARGETS := test1

all: $(TARGETS)

test1: test1.o signal_rt.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONE: clean
clean:
	rm -rf $(OBJECTS) $(TARGETS)
