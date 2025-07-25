cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main src/main.cpp "src/Game.cpp" "src/Game.h" "src/Player.cpp" "src/Player.h" "src/Help.h" "src/Projectile.cpp" "src/Projectile.h" "src/Weapon.h" "src/Enemy.cpp" "src/Enemy.h" "src/Weapon.cpp" "src/MovementPattern.cpp" "src/MovementPattern.h" "src/Entity.cpp" "src/Entity.h")
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)
