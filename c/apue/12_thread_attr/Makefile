CFLAGS += -Wall
LIBS += -lpthread
OBJECTS := getenv_r.o getenv_r_v2.o test_getenv.o

test_getenv : $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONE : clean
clean:
	rm -rf getenv_r.o getenv_r_v2.o test_getenv test_getenv.o
