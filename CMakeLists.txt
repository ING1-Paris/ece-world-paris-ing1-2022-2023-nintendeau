cmake_minimum_required(VERSION 3.10)
project(PROJET C)

set(CMAKE_C_STANDARD 99)

add_executable(ece-world-paris-ing1-2022-2023-nintendeau
main.c
attractions/jackpot.c headers/jackpot.h
attractions/guitar_hero.c headers/guitar_hero.h
attractions/palais_des_glaces.c headers/palais_des_glaces.h
attractions/paris_hippiques.c headers/paris_hippiques.h
attractions/snake.c headers/snake.h
attractions/tag.c headers/tag.h
attractions/tape_taupe.c headers/tape_taupe.h
attractions/geometry_dash.c headers/geometry_dash.h
attractions/flappy_bird.c headers/flappy_bird.h
)
target_link_libraries(ece-world-paris-ing1-2022-2023-nintendeau -lmingw32 -lalleg44)
