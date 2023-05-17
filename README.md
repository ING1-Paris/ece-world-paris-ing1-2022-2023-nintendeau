# ECE WORLD - PROJET ALLEGRO -  By Nintendeau ಠ▃ಠ™

**Projet d'informatique avec Allegro 4 du second semestre (ECE ING1)** 

*Liens : [Sujet](sujet.pdf) / [Barème](bareme.xlsx) *

## Énoncé

Programmer un jeu dans le thème "parc d'attractions" à deux joueurs en C, en utilisant la bibliothèque graphique [Allegro 4.4](https://github.com/carstene1ns/allegro-4.4/blob/master/addons/allegrogl/howto.txt). Chaque étudiant réalise de A à Z une attraction du CDC, et deux jeux bonus (issus du CDC ou non).

* La carte du parc fait office de menu, avec chaque attraction représentée par un lieu-dit, et les joueurs (représentés chacun par un personnage) s'y déplacent et choisissent à tour de rôle les attractions.

  * (Idéalement, les joueurs seront nommés)
  * On peut entrer/sortir de la carte, consulter les stats et lancer un jeu
* Les stats de chaque joueur sont sauvegardées pendant la partie pour comparer + Une sauvegarde globale permet de consulter les meilleurs scores all-time
* Chaque joueur dispose de 5 tickets, jouer à un jeu coûte un ticket, en gagner un peut rapporter 1/2 tickets
* Plus de ticket = défaite, on affiche les stats 

Liste des jeux réalisés :

|        Attraction        | Difficulté | Nom                |
| :----------------------: | :---------: | ------------------ |
|          Snake          |     ❗     | Léon (@PingoLeon) |
|           Chat           |     ❗     | Léon (@PingoLeon) |
|       Guitar Hero       |     ❗     | Alfred             |
|    Palais des glaces    |    ⚠️    | Alfred             |
|      Geometry Dash      |     ❗     | Alfred             |
|        Tape-Taupe        |     ✅     | Mathéo            |
|         Jackpot!         |    ⚠️    | Mathéo            |
| Paris hippiques (animé) |    ⚠️    | Shaïma            |
|       Flappy Bird       |     ❔     | Shaïma            |

(Facile = ✅| Moyen = ⚠️| Difficile = ❗| Inconnu = ❔)

La notation dépendra de la difficulté de l'attraction, la qualité du code, la fluidité du jeu et l'apparence.

## Livrables

Lors de la soutenance, le travail global sera évalué sur la qualité de la conception, l'organisation, la qualité de l'implémentation, la jouabilité, la fluidité ainsi que sur la présentation orale.

A rendre (.zip) :

* Preuves de conception (.pdf)
* Code source
* Slides de soutenance **(Marp imposé)**
* Bonus : vidéo et infographie (+1pts)

## Soutenance

Trois phases : 

* Présentation (slides -> template MARP)
* Démonstration
* Q/R

---

**Fiche technique :**

-> Jeu 2D / Dims : 1200x800 / Requis : CMake+ Compilateur avec Allegro4 installé

---

> Nintendeau ಠ▃ಠ™ 2023, tous droits réservés

---
