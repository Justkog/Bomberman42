CC = g++
RM = /bin/rm -f
RMDIR = /bin/rm -rf
MKDIR = /bin/mkdir -p
MAKE = make --no-print-directory

#------------------------------------------------------------------------------#

NAME = Bomberman
LIB_NAME =
LIBS = -lm -framework OPENGL `pkg-config --static --libs glfw3` \
	`pkg-config --static --libs glew` \
	`pkg-config --static --libs glm` \
	`pkg-config --static --libs libpng`\
	`pkg-config --static --libs openal` \
	`pkg-config --static --libs sndfile`

SRC = \
	main.cpp \
	Core/Window.cpp \
	Core/Time.cpp \
	Core/SceneManager.cpp \
	Core/AScene.cpp \
	Core/GameObject.cpp \
	Core/Transform.cpp \
	Core/Input.cpp \
	Core/Camera.cpp \
	Core/Component/Component.cpp \
	Core/Component/MeshRenderer.cpp \
	Core/Component/ACollider.cpp \
	Core/Component/BoxCollider2D.cpp \
	Core/Graphics/Mesh.cpp \
	Core/Graphics/MeshBuilder.cpp \
	Core/Graphics/ShaderProgram.cpp \
	Core/Graphics/Graphics.cpp \
	Core/Graphics/AMaterial.cpp \
	Core/Graphics/Texture.cpp \
	Core/IO/FileUtils.cpp \
	\
	Game/SceneTest.cpp \
	\
	Game/Components/Player.cpp \
	Game/Components/CameraController.cpp \
	Game/Components/Settings.cpp \
	\
	Core/Audio/AudioListener.cpp \
	Core/Audio/AudioSource.cpp \
	Core/Audio/AudioClip.cpp \
	\
	Game/CameraTest.cpp

DIR = Core Core/Component Core/Graphics Core/IO Game Core/Audio Game/Components


CFLAGS = -Ofast -march=native -flto -std=c++11 -Wc++11-extensions \
	`pkg-config glfw3 --cflags-only-I` \
	`pkg-config glew --cflags-only-I` \
	`pkg-config glm --cflags-only-I` \
	`pkg-config libpng --cflags-only-I` \
	`pkg-config openal --cflags-only-I` \
	`pkg-config sndfile --cflags-only-I`




#------------------------------------------------------------------------------#

C_FILE = $(addprefix sources/, $(SRC))
O_FILE = $(addprefix obj/, $(SRC:.cpp=.o))
D_FILE = $(addprefix dep/, $(SRC:.cpp=.d))
CFLAGS += -I include -I ~/.brew/Cellar/nlohmann_json/3.1.2/include $(addprefix -I lib, $(addsuffix /include, $(LIB_NAME)))
LIB_DIR = $(addprefix lib, $(LIB_NAME))
LIBS += $(addprefix -L , $(LIB_DIR)) $(addprefix -l, $(LIB_NAME))
.PHONY: all dircreate clean fclean ffclean run ar re req install

all: dircreate $(join $(addsuffix /, $(LIB_DIR)), $(addsuffix .a, $(LIB_DIR)))
	$(MAKE) $(NAME)

install:
	~/.brew/bin/brew update
	~/.brew/bin/brew install pkg-config
	~/.brew/bin/brew install glm
	~/.brew/bin/brew install glfw
	~/.brew/bin/brew install glew
	~/.brew/bin/brew install libpng
	~/.brew/bin/brew install openal-soft
	~/.brew/bin/brew install libsndfile
	~/.brew/bin/brew tap nlohmann/json
	~/.brew/bin/brew install nlohmann/json
	sh script.sh

relink:
%.a: relink
	$(MAKE) -C $(dir $@)

dircreate:
	@$(MKDIR) obj $(addprefix obj/, $(DIR))
	@$(MKDIR) dep $(addprefix dep/, $(DIR))
req: $(O_FILE)

$(NAME): $(O_FILE) $(D_FILE)
	$(CC) -o $(@F) $(O_FILE) $(LIBS)

obj/%.o: sources/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
dep/%.d: sources/%.cpp
	@set -e; rm -f $@; \
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,obj/\1.o $@ : ,g' < $@.$$$$ >> $@; \
		$(RM) $@.$$$$
clean:
	$(RM) $(O_FILE)
	$(RM) $(D_FILE)
fclean: clean
	$(RM) $(NAME)
	$(RMDIR) obj
	$(RMDIR) dep
ffclean: fclean
	$(addprefix $(MAKE) fclean -C , $(addsuffix ;, $(LIB_DIR)))
run: all
	./$(NAME)
ar: fclean run
re: fclean all

-include $(D_FILE)
