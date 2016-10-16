# Name of the executable created (.exe will be added automatically if necessary)

Target 	= indie_studio

Sources = src/main.cpp \
					src/Sound/Sound.cpp \
					src/Events/Events.cpp	\
					src/Game/Game.cpp \
					src/Graphics/Particle/Particle.cpp \
					src/GameObject/Block.cpp \
					src/GameObject/Bomb.cpp \
					src/GameObject/GameObject.cpp \
					src/Character/Character.cpp \
					src/ConfigFileParser/CFGParser.cpp \
					src/GameObject/Bonus.cpp \
					src/AI/AI.cpp \
					src/Graphics/Texture/Texture.cpp \
					src/Launcher/Launcher.cpp \
					src/Launcher/LauncherEventReceiver.cpp \
					src/Launcher/Loader/Loader.cpp \
					src/Launcher/Loader/fileDeletion.cpp \
					src/Launcher/GUI/GUIContext.cpp \
					src/Thread/Mutex.cpp	\
					src/Game/Instance.cpp	\

#Sources += src/Sound/Sound.cpp

Objects = $(Sources:.cpp=.o)

# Path to Irrlicht directory, should contain include/ and lib/
IrrlichtHome 	= ./lib/irrlicht-1.8.3/
irrKlangHome	=	./lib/irrKlang-64bit-1.5.0/

# IRRLICHT INCLUDES
CPPFLAGS 	=  -std=c++11
CPPFLAGS	+= -I$(IrrlichtHome)include -I$(irrKlangHome)include
CPPFLAGS	+= -O3 -ffast-math
CPPFLAGS 	+= -I./src/Graphics/Game/ -I./src/Events/ -I./src/Character/
CPPFLAGS 	+= -I./src/GameObject/
CPPFLAGS 	+= -I./src/Game/
CPPFLAGS	+= -I./src/ConfigFileParser/
CPPFLAGS	+= -I./src/Sound/
CPPFLAGS	+= -I./src/Graphics/Texture/
CPPFLAGS	+= -I./src/Graphics/Particle/
CPPFLAGS	+= -I./src/Thread/

# LUA INCLUDES
CPPFLAGS    += -I./lib/LuaBridge/Source/LuaBridge
CPPFLAGS    += -I./lib/lua-5.2.4/include
CPPFLAGS    += -I./src/AI

#PREPARATION FLAGS WINDOWS-LINUX
ifdef	SYSTEMROOT
	RM = del /Q
	FixPath = $(subst /, \, $1)
	LDFLAGS = -static-libgcc -static-libstdc++ -L$(IrrlichtHome)bin/Win32-gcc -lIrrlicht
	LDFLAGS	+= -L$(irrKlangHome)bin/Win32-gcc/ -lIrrKlang
	LDFLAGS += -lopengl32 -lm -lwinmm -lgdi32 -lgdi32 -lwinspool -lcomdlg32
	LDFLAGS	+= 	-lole32 -loleaut32 -luuid -lodbc32 -lodbccp32 -D_IRR_STATIC_LIB_
else
	ifeq	($(shell uname), Linux)
		RM = rm -f
		FixPath = $1
		CPPFLAGS += -I/usr/X11R6/include
		LDFLAGS = -L$(IrrlichtHome)lib/Linux/ -lIrrlicht -lGL -lXxf86vm -lXext -lX11 -lXcursor
		LDFLAGS	+= -L$(irrKlangHome)bin/linux-gcc-64/ $(irrKlangHome)bin/linux-gcc-64/libIrrKlang.so
		LDFLAGS	+= -L$(irrKlangHome)bin/linux-gcc-64/ $(irrKlangHome)bin/linux-gcc-64/ikpMP3.so
		LDFLAGS	+= -pthread
	    # LUA LIB
	    LDFLAGS += ./lib/lua-5.2.4/liblua52.so -ldl

	endif
endif

$(Target):	$(Objects)
	$(CXX) $(CPPFLAGS) $(Objects) -o $(Target) $(LDFLAGS)
#default target is Linux
all: $(Target)

clean:
	$(RM) $(Objects)

fclean: clean
	rm -f $(Target)

re: fclean all

install:
	$(MAKE) -C $(IrrlichtHome)source/Irrlicht/
