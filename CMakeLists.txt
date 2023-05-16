cmake_minimum_required(VERSION 3.10)
project(PROJET C)

set(CMAKE_C_STANDARD 99)

add_executable(ece-world-paris-ing1-2022-2023-nintendeau
main.c
attractionsexecsolo/jackpot.c headers/jackpot.h
attractionsexecsolo/guitar_hero.c headers/guitar_hero.h
attractionsexecsolo/palais_des_glaces.c headers/palais_des_glaces.h
attractionsexecsolo/paris_hippiques.c headers/paris_hippiques.h
attractionsexecsolo/snake.c headers/snake.h
attractionsexecsolo/tag.c headers/tag.h
attractionsexecsolo/tape_taupe.c headers/tape_taupe.h
attractionsexecsolo/geometry_dash.c headers/geometry_dash.h
attractionsexecsolo/flappy_bird.c headers/flappy_bird.h
)
target_link_libraries(ece-world-paris-ing1-2022-2023-nintendeau -lmingw32 -lalleg44)
