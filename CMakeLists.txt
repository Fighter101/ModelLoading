cmake_minimum_required(VERSION 3.6)
project(ModelLoading)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Shader.cpp Shader.h Camera.h Camera.cpp TextureLoader.h TextureLoader.cpp Includes.h Mesh.cpp Mesh.h Model.cpp Model.h)
add_executable(ModelLoading ${SOURCE_FILES}  )
target_link_libraries(${CMAKE_PROJECT_NAME} -lGL -lglfw -lGLEW -lSOIL -lassimp )
find_package(Bullet REQUIRED)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${BULLET_INCLUDE_DIR} )
target_LINK_LIBRARIES(${CMAKE_PROJECT_NAME}  BulletDynamics BulletCollision LinearMath)