OBJECTS := mqcreatel.o mqunlink.o mqgetattr.o mqcreate.o mqsend.o \
	mqreceive.o mqsysconf.o
CFLAGS += -Wall
LIBS += -lrt
TARGETS := mqunlink mqgetattr mqcreate mqcreatel mqsend mqreceive \
	mqsysconf

all: $(TARGETS)

mqcreatel : mqcreatel.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
mqunlink : mqunlink.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
mqgetattr : mqgetattr.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
mqcreate : mqcreate.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
mqsend : mqsend.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
mqreceive : mqreceive.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
mqsysconf : mqsysconf.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

.PHONE : clean
clean:
	rm -rf $(OBJECTS) $(TARGETS)
