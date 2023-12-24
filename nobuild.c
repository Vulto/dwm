#define NOBUILD_IMPLEMENTATION
#include "./nobuild.h"


#define BIN "dwm"
#define PREFIX "/usr/local/bin/"
#define VERSION "6.4"
#define MANPREFIX "/usr/local/share/man"

static const char *SOURCE[]={"drw.c", "dwm.c", "util.c"};
static const char *OBJECT[]={"drw.o", "dwm.o", "util.o"};

#define CFLAGS	"-g", 						\
				"-std=c99", 				\
				"-pedantic",				\
				"-Wall",					\
				"-I/usr/X11R6/include",		\
				"-I/usr/include/freetype2",	\
				"-D_DEFAULT_SOURCE",		\
				"-D_BSD_SOURCE",			\
				"-D_POSIX_C_SOURCE=2",		\
				"-DVERSION=\""VERSION"\" ",	\
				"-DXINERAMA",				\
				"-O3"

#define LDFLAGS "-L/usr/X11R6/lib", \
				"-lX11", 			\
				"-lXinerama", 		\
				"-lfontconfig",		\
				"-lXft", 			\
				"-lXrender"

char *cc(void){
    char *result = getenv("CC");
    return result ? result : "cc";
}

#if 0
void BuildObj(void) {
	for(int i=0; i <= 3; i++ ){
	    CMD(cc(), "-o", OBJ[i], "-c", SRC[i]);
	}
}
#endif

int BuildBin(void) {
    CMD(cc(), "-o", BIN, SOURCE[0], SOURCE[1], SOURCE[2], CFLAGS, LDFLAGS, NULL );
	return EXIT_FAILURE;
}
void Install(void) {
	CMD("doas", "cp", BIN, PREFIX);
}

void Remove(void) {
	CMD("doas", "rm", "-v", PREFIX""BIN);
}

void Clean(void) {
	CMD("rm", OBJECT, BIN, "c.old");
}


int main(int argc, char *argv[]) {
    GO_REBUILD_URSELF(argc, argv);
    if (argc <= 1){
//		BuildObj();
		BuildBin();
		return EXIT_SUCCESS;
	}

    if (argc > 1){
        if (strcmp(argv[1], "install") == 0){
			Install();
        }else if (strcmp(argv[1], "remove") == 0){
			Remove();
        }else if (strcmp(argv[1], "clean") == 0){
			Clean();
        }else{
			fprintf(stderr, "Unknow command");
        }
    }
    return EXIT_SUCCESS;
}
