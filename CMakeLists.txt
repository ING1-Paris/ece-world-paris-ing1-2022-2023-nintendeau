cmake_minimum_required(VERSION 3.10)
project(PROJET C)

set(CMAKE_C_STANDARD 99)

add_executable(ece-world-paris-ing1-2022-2023-nintendeau main.c jackpot.c jackpot.h guitar_hero.c guitar_hero.h palais_des_glaces.c palais_des_glaces.h paris_hippiques.c paris_hippiques.h snake.c snake.h)
target_link_libraries(ece-world-paris-ing1-2022-2023-nintendeau -lmingw32 -lalleg44)
