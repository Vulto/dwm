#define NOBUILD_IMPLEMENTATION
#include "./nobuild.h"

#define BIN "dwm"
#define OLD "c.old"
#define PREFIX "/usr/local/bin/"
#define VERSION "6.4"
#define MANPREFIX "/usr/local/share/man"

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

static const char *SOURCES[]={"drw.c", "dwm.c", "util.c"};
static const char *OBJECTS[]={"drw.o", "dwm.o", "util.o"};

char *cc(void){
	char *result = getenv("CC");
	return result ? result : "cc";
}

void BuildObj(void) {
	for(int i=0; i <= 2; i++ ){
		CMD(cc(), "-c", CFLAGS, SOURCES[i]);
	}
}

int BuildBin(void) {
	for(int i=0; i <= 2; i++ ){
		CMD(cc(), "-o", BIN, OBJECTS[0], OBJECTS[1], OBJECTS[2], LDFLAGS, NULL );
	}
}

void Install(void) {
	CMD("doas", "cp", "-f", BIN, PREFIX);
}

void Remove(void) {
	CMD("doas", "rm", "-v", PREFIX""BIN);
}

void Clean(void) {
	size_t objarr = (sizeof(OBJECTS) / sizeof(OBJECTS[1]));
	for (int i=0; i < objarr ; i++) {
		CMD("rm", OBJECTS[i]);
	}
	CMD("rm", BIN, "c.old");
}

int main(int argc, char *argv[]) {
	GO_REBUILD_URSELF(argc, argv);
	if (argc < 2 ){
		BuildObj();
		BuildBin();
		return EXIT_SUCCESS;
	}

	for (int i = 1; i < argc; i++) {
		char *arg = argv[i];

		if (arg[0] == '-') {
			for (int j = 1; j < strlen(arg); j++) {

				switch (arg[j]) {
					case 'r':
						Remove();
						break;
					case 'i':
						Install();
						break;
					case 'c':
						Clean();
						break;
					default:
						printf("Unknown option: %c\n", arg[j]);
						break;
				}
			}
		} else {
			printf("Usage: %s [-d] [-r] [-f]\n", argv[0]);
		}
	}
	return EXIT_SUCCESS;
}
