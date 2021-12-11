cmake_minimum_required(VERSION 3.21)
project(prog_game)

set(CMAKE_CXX_STANDARD 14)

add_executable(prog_game main.cpp src/Animator.h src/WindowManager.h src/WindowManager.cpp src/SceneManager.h src/FieldScene.h src/KeyboardManager.h src/Keyboard.h src/Drawer.h src/Point.h src/ObjectManager.h src/Collision.h src/CoordinateUtils.h src/Object.h src/Define.h src/objects/Block.h src/Map.h src/Image.h src/ResourceManager.h src/Animator.cpp src/FieldScene.cpp src/Map.cpp src/ResourceManager.cpp)
target_link_libraries(prog_game glpng glut GLU GL)