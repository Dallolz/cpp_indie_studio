BIN 		= BomberMan

SRCS_FILES 	= main.cpp \
		  Block.cpp \
		  Bomb.cpp \
		  Bonus.cpp \
		  Character.cpp \
		  CreateGame.cpp \
		  Draw.cpp \
		  Game.cpp \
		  GameManager.cpp \
		  Gameplay.cpp \
		  MainMenu.cpp \
		  NewHighScore.cpp \
		  Object.cpp \
		  OptionsMenu.cpp \
		  ScoreMenu.cpp \
		  Square.cpp \
		  utils.cpp \

SRCS 		= $(addprefix srcs/,$(SRCS_FILES))
OBJS 		= $(SRCS:.cpp=.o)

# general compiler settings
CPPFLAGS = -Wl,-rpath=./includes/lib/ -I/usr/X11R6/include -Iincludes -Iincludes/irrlicht_includes -std=gnu++11 -lpthread 

CXXFLAGS = -O3 -ffast-math -lIrrlicht  -lGL -lGLU 

all: all_linux

ifeq ($(HOSTTYPE), x86_64)
LIBSELECT=64
endif

all_linux: LDFLAGS = -L/usr/X11R6/lib$(LIBSELECT) -L./includes/lib/ -lIrrlicht -lGL -lXxf86vm -lXext -lX11 -lXcursor 

all_linux clean_linux: SYSTEM=Linux

all_win32: LDFLAGS = -L../../lib/Win32-gcc -lIrrlicht

static_win32: LDFLAGS += -lgdi32 -lopengl32 -ld3dx9d -lwinmm -lm

static_win32: CPPFLAGS += -D_IRR_STATIC_LIB_

static_win32 all_win32 clean_win32: SYSTEM=Win32-gcc

static_win32 all_win32 clean_win32: SUF=.exe

# name of the binary - only valid for targets which set SYSTEM
DESTPATH = bin/$(SYSTEM)/$(BIN)$(SUF)

all_linux all_win32 static_win32: $(OBJS)
		$(warning Building...)
		$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(OBJS) -o $(DESTPATH) $(LDFLAGS)

re: fclean all

hugo:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) Backup/Hugo/hugo.cpp -o Backup/hugo -L/usr/X11R6/lib -L../../lib/Linux -lIrrlicht -lGL -lXxf86vm -lXext -lX11 -lXcursor

clean: clean_linux clean_win32
	$(warning Cleaning...)

clean_linux clean_win32:
		@$(RM) $(OBJS)

fclean: clean
		@$(RM) $(DESTPATH)

.PHONY: all all_win32 clean clean_linux clean_win32 static_win32
