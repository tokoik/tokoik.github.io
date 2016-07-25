OGLLIBS	= -lglut -lGLU -lGL
X11LIBS	= -lXmu -lXi -lXext -lX11
LIBS	= $(OGLLIBS) $(X11LIBS) -lm

all:	walk1 walk1-st walk1-crm walk1-multi walk1-crm-multi \
	walk2 walk2-st walk2-crm walk2-multi walk2-crm-multi

walk1: walk1.c
	cc walk1.c -o $@ $(LIBS)
walk1-st: walk1.c
	cc -DSTEREO walk1.c -o $@ $(LIBS)
walk1-crm: walk1.c
	cc -DSTEREO -DCRM walk1.c -o $@ $(LIBS)
walk1-multi: walk1.c
	cc -DMULTI walk1.c -o $@ $(LIBS)
walk1-crm-multi: walk1.c
	cc -DSTEREO -DCRM -DMULTI walk1.c -o $@ $(LIBS)

walk2: walk2.c
	cc walk2.c -o $@ $(LIBS)
walk2-st: walk2.c
	cc -DSTEREO walk2.c -o $@ $(LIBS)
walk2-crm: walk2.c
	cc -DSTEREO -DCRM walk2.c -o $@ $(LIBS)
walk2-multi: walk2.c
	cc -DMULTI walk2.c -o $@ $(LIBS)
walk2-crm-multi: walk2.c
	cc -DSTEREO -DCRM -DMULTI walk2.c -o $@ $(LIBS)

clean:
	-rm -f walk1 walk1-st walk1-crm walk1-multi walk1-crm-multi
	-rm -f walk2 walk2-st walk2-crm walk2-multi walk2-crm-multi
	-rm -f *.o *~
