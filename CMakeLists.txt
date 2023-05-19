cmake_minimum_required(VERSION 3.10)
project(PROJET C)

set(CMAKE_C_STANDARD 23)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/.cmake-build-debug)

add_executable(ece-world-paris-ing1-2022-2023-nintendeau
main.c
attractions/source/loader.c            attractions/header/loader.h
attractions/source/tag.c               attractions/header/tag.h
attractions/source/geometry_dash.c     attractions/header/geometry_dash.h
attractions/source/guitar_hero.c       attractions/header/guitar_hero.h
attractions/source/palais_des_glaces.c attractions/header/palais_des_glaces.h
attractions/source/snake.c             attractions/header/snake.h
attractions/source/paris_hippiques.c   attractions/header/paris_hippiques.h
attractions/source/tape_taupe.c        attractions/header/tape_taupe.h
attractions/source/jackpot.c           attractions/header/jackpot.h
attractions/source/flappy_bird.c       attractions/header/flappy_bird.h
)
target_link_libraries(ece-world-paris-ing1-2022-2023-nintendeau -lmingw32 -lalleg44)
