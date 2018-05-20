CC = clang++
RM = /bin/rm -f
RMDIR = /bin/rm -rf
MKDIR = /bin/mkdir -p
MAKE = make --no-print-directory

#------------------------------------------------------------------------------#

NAME = Bomberman
LIB_NAME =
LIBS = -lm -framework OPENGL `pkg-config --static --libs glfw3 glew glm libpng openal sndfile assimp`

SRC = \
	main.cpp \
	\
	sigslot/src/signal.cpp \
	\
	Core/Window.cpp \
	Core/Time.cpp \
	Core/SceneManager.cpp \
	Core/Json/Json.cpp \
	Core/Json/JsonSerializable.cpp \
	Core/AScene.cpp \
	Core/GenericScene.cpp \
	Core/GameObject.cpp \
	Core/Transform.cpp \
	Core/Input.cpp \
	Core/Camera.cpp \
	Core/Mathf.cpp \
	\
	Core/Component/Component.cpp \
	Core/Component/MeshRenderer.cpp \
	Core/Component/RaysRenderer.cpp \
	Core/Component/ACollider.cpp \
	Core/Component/BoxCollider2D.cpp \
	Core/Component/CircleCollider.cpp \
	Core/Component/RigidBody2D.cpp \
	Core/Component/ParticleBase.cpp \
	Core/Component/ParticleExplode.cpp \
	Core/Component/ModelRenderer.cpp \
	\
	Core/Graphics/Mesh.cpp \
	Core/Graphics/MeshBuilder.cpp \
	Core/Graphics/ShaderProgram.cpp \
	Core/Graphics/Graphics.cpp \
	Core/Graphics/AMaterial.cpp \
	Core/Graphics/Lights/ALight.cpp \
	Core/Graphics/Lights/AmbiantLight.cpp \
	Core/Graphics/Lights/DirectionalLight.cpp \
	Core/Graphics/Cubemap.cpp \
	Core/Graphics/Texture.cpp \
	Core/Graphics/Framebuffer.cpp \
	\
	Core/Physics/Physics.cpp \
	\
	Core/IO/FileUtils.cpp \
	\
	Core/Audio/AudioListener.cpp \
	Core/Audio/AudioSource.cpp \
	Core/Audio/AudioClip.cpp \
	\
	Core/BeerRoutine/BeerRoutine.cpp \
	Core/BeerRoutine/ARoutineRunner.cpp \
	\
	Game/SceneLoader.cpp \
	Game/SceneTest.cpp \
	Game/SceneMain.cpp \
	Game/Level1.cpp \
	Game/Level2.cpp \
	Game/Level3.cpp \
	Game/Level4.cpp \
	Game/Level5.cpp \
	Game/Versus1.cpp \
	Game/Versus2.cpp \
	Game/Versus3.cpp \
	\
	Game/Assets.cpp \
	Game/Input.cpp \
	Game/Components/GameManager.cpp \
	Game/Components/Character.cpp \
	Game/Components/MouseRayTest.cpp \
	Game/Components/Player.cpp \
	Game/Components/IA.cpp \
	Game/Components/CameraController.cpp \
	Game/Components/Settings.cpp \
	Game/Components/GameProgression.cpp \
	Game/Components/Item.cpp \
	Game/Components/Bomb.cpp \
	Game/Components/Map.cpp \
	Game/Components/Breakable.cpp \
	Game/Components/BeerRoutineTester.cpp \
	Game/Components/MainMenu.cpp \
	Game/Components/VersusMenu.cpp \
	Game/Components/AdventureMenu.cpp \
	Game/Components/AdventureContinueMenu.cpp \
	Game/Components/SettingsMenu.cpp \
	Game/Components/InputsMenu.cpp \
	Game/Components/InGameMenu.cpp \
	Game/Components/GameOverMenu.cpp \
	Game/Components/VictoryMenu.cpp \
	Game/Components/TimeUI.cpp \
	Game/Components/StartTimerUI.cpp \
	Game/Components/ItemsUI.cpp \
	Game/Components/Message.cpp \
	Game/Components/LevelInstructions.cpp \
	Game/Components/UIThemeManager.cpp \
	Game/Components/BackgroundDrawer.cpp \
	Game/Components/AudioManager.cpp


DIR = $(dir $(SRC))
# Core Core/Component Core/Graphics Core/IO Core/Maths Core/Audio \
	Game Game/Components Core/Json Core/Physics sigslot/src Core/BeerRoutine

# -g
# -Ofast -march=native -flto
CFLAGS = -g -Wall -Wextra -std=c++11 -Wc++11-extensions \
	`pkg-config --cflags-only-I glfw3 glew glm libpng openal sndfile assimp`




#------------------------------------------------------------------------------#

C_FILE = $(addprefix sources/, $(SRC))
O_FILE = $(addprefix obj/, $(SRC:.cpp=.o))
D_FILE = $(addprefix obj/, $(SRC:.cpp=.d))
CFLAGS += -I include -I ~/.brew/Cellar/nlohmann_json/3.1.2/include \
	-I tinyobjloader/ -I stb/ $(addprefix -I lib, $(addsuffix /include, $(LIB_NAME))) \
	-I nuklear/ -I sources/

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
	~/.brew/bin/brew install nlohmann_json
	~/.brew/bin/brew install assimp
	sh script.sh
	git clone https://github.com/mimusangel/Bomberman42Asset.git Bomberman42Asset
	mv Bomberman42Asset/assets .
	mv Bomberman42Asset/html .
	rm -rf Bomberman42Asset
	
relink:
%.a: relink
	$(MAKE) -C $(dir $@)

dircreate:
	@$(MKDIR) obj $(addprefix obj/, $(DIR))

req: $(O_FILE)

$(NAME): $(O_FILE)
	$(CC) -o $(@F) $(O_FILE) $(LIBS)

obj/%.o: sources/%.cpp
	$(CC) -MMD -o $@ -c $< $(CFLAGS)

clean:
	$(RM) $(O_FILE)
	$(RM) $(D_FILE)

fclean: clean
	$(RM) $(NAME)
	$(RMDIR) obj

ffclean: fclean
	$(addprefix $(MAKE) fclean -C , $(addsuffix ;, $(LIB_DIR)))

run: all
	./$(NAME)

ar: fclean run

re: fclean all

-include $(D_FILE)
