OBJECTS := mqcreate1.o mqunlink.o mqgetattr.o mqcreate.o mqsend.o \
	mqreceive.o mqsysconf.o mqnotifysig1.o mqnotifysig2.o  \
	mqnotifysig3.o mqnotifysig4.o
CFLAGS += -Wall
LIBS += -lrt
TARGETS := mqunlink mqgetattr mqcreate mqcreate1 mqsend mqreceive \
	mqsysconf mqnotifysig1 mqnotifysig2 mqnotifysig3 mqnotifysig4

all: $(TARGETS)

mqcreate1 : mqcreate1.o
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
mqnotifysig1 : mqnotifysig1.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
mqnotifysig2 : mqnotifysig2.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
mqnotifysig3 : mqnotifysig3.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
mqnotifysig4 : mqnotifysig4.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

.PHONE : clean
clean:
	rm -rf $(OBJECTS) $(TARGETS)
