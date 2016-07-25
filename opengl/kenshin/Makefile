OGLLIBS	= -L/usr/X11R6/lib -lglut -lGLU -lGL
X11LIBS	= -lXmu -lXi -lXext -lX11
LIBS	= $(OGLLIBS) $(X11LIBS) -lm

all:	lorenz1 lorenz2 lorenz1s lorenz3s \
	lorenz1s-crm rosslers-crm rossler3s-crm \
	rossler rosslers rossler2s rossler3s chaostoy

chaostoy: chaostoy.c
	cc chaostoy.c -o $@ $(LIBS)
lorenz1: lorenz1.c
	cc lorenz1.c -o $@ $(LIBS)
lorenz2: lorenz2.c
	cc lorenz2.c -o $@ $(LIBS)
rossler: rossler.c
	cc rossler.c -o $@ $(LIBS)
lorenz1s: lorenz1s.c
	cc -DSTEREO lorenz1s.c -o $@ $(LIBS)
lorenz3s: lorenz3s.c
	cc -DSTEREO lorenz3s.c -o $@ $(LIBS)
rosslers: rosslers.c
	cc -DSTEREO rosslers.c -o $@ $(LIBS)
rossler2s: rossler2s.c
	cc -DSTEREO rossler2s.c -o $@ $(LIBS)
rossler3s: rossler3s.c
	cc -DSTEREO rossler3s.c -o $@ $(LIBS)
lorenz1s-crm: lorenz1s.c
	cc -DSTEREO -DCRM lorenz1s.c -o $@ $(LIBS)
rosslers-crm: rosslers.c
	cc -DSTEREO -DCRM rosslers.c -o $@ $(LIBS)
rossler3s-crm: rossler3s.c
	cc -DSTEREO -DCRM rossler3s.c -o $@ $(LIBS)

clean:
	-rm -f lorenz1 lorenz2 lorenz1s lorenz3s
	-rm -f lorenz1s-crm rosslers-crm rossler3s-crm
	-rm -f rossler rosslers rossler2s rossler3s chaostoy
	-rm -f *.o *~
