cmake_minimum_required(VERSION 3.21)
project(prog_game)

set(CMAKE_CXX_STANDARD 17)

add_executable(prog_game main.cpp src/Animator.h src/WindowManager.h src/WindowManager.cpp src/SceneManager.h src/FieldScene.h src/KeyboardUtils.h src/Keyboard.h src/Drawer.h src/Point.h src/ObjectManager.h src/Collision.h src/CoordinateUtils.h src/Object.h src/Define.h src/objects/Block.h src/Map.h src/Image.h src/ResourceManager.h src/Animator.cpp src/FieldScene.cpp src/Map.cpp src/ResourceManager.cpp src/Player.cpp src/Player.h src/Physics.cpp src/Physics.h src/TimeManager.cpp src/TimeManager.h src/KeyboardUtils.cpp src/Object.cpp src/CollisionManager.h src/Collision.cpp src/GameArray.h src/GameArrayIterator.h src/objects/KeyInput.h src/objects/Segment.h src/objects/Cable.h src/CableAttachableObject.h src/objects/InvalidObject.h src/KeyboardManager.cpp src/KeyboardManager.h src/MouseUtils.cpp src/MouseUtils.h)
target_link_libraries(prog_game glpng glut GLU GL)