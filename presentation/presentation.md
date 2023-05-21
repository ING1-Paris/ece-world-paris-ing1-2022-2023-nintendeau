---
marp: true
theme: default
paginate: true
_paginate: false
---

<script type="module">
  import mermaid from 'https://cdn.jsdelivr.net/npm/mermaid@10/dist/mermaid.esm.min.mjs';
    mermaid.initialize({ 
        startOnLoad: true,
        theme: 'base',
    });
</script>

<!--
# Style lead only for this slide
_class: lead
_footer: Algorithmique Avancée et Bibliothèque Graphique - 2022-2023
-->

![bg left](./images/fond_ece.png)

**ING1** Projet d'informatique


# ECE World, by Nintendeau

---

# Sommaire
- Thème et Carte 
- Organisation des jeux
- Guitar Hero
- Paris Hippiques
- Snake
- Jackpot
- Floppy Bird
- The Maze
- Tape Taupe
- Geometry Dash
- Bilan
---

# Equipe Nintendeau

![bg right:60%](./images/nintendeau.bmp)

- DALLE Léon
- DE VULPIAN Alfred
- INNOCENT Mathéo
- DEROUICH Shaïma

---

# ECE World

![bg right:55% 150%](./images/eceworld.png)

## Thème

- Fête foraine (médieval et + encore)
- 9 jeux très variés
- 2 joueurs 
- 5 tickets par joueur
---

# Carte `1/2`

*Réalisée par : **Léon**, **Alfred**.*
Fonctionnalités : 
- Logo d'intro de Nintendeau:tm:
- Choix du Nom et des Couleurs (16 Millions de sprites possibles avec un filtre rgb !)
- Déplacement sur la carte avec carte des collisions
- Affichage des règles avant attraction
- Affichage des tickets restants

---

# Carte `2/2`

:warning: Problèmes rencontrés : 
-> Grand volume de variables, d'éléments à passer entre les sous-fonctions
-> Des crash inopinés, rendant l'implémentation difficile
-> Des bugs à la fin d'un jeu et la gestion des tickets associée

---

# Organisation des jeux

Les jeux ont tous été codés dans des fichiers source indépendants. L'arborescence est telle que : 
<div class="mermaid">
%%{init: {'theme':'neutral'}}%%
flowchart LR
    Attractions --> Assets
    Attractions --> Header
    Attractions --> Source
</div>

Les jeux ne prennent quasi rien en paramètres, si ce n'est certains assets utiles du main comme les animations.

Pour lancer un jeu, il suffit de diriger son personnage vers l'une des nombreuses maisons presentes sur la carte, les regles seront affichées et il suffira de cliquer sur la barre espace pour executer le jeu.

---

![bg right:40%](https://th.bing.com/th/id/OIP.wECKrb7x6RpwyGUY7x4x-AHaHa?pid=ImgDet&rs=1)

# GUITAR HERO

*Réalisé par : **Alfred** (100%)*

- Il y'a 4 touches (D, F, J, K) qui correspondent aux 4 cordes de la guitare.
- Les notes tombent du haut de l'écran vers le bas.
- Le joueur doit appuyer sur la touche correspondant à la note au bon moment.
- Si le joueur appuie sur la touche au bon moment, il gagne un point.
- Si le joueur appuie sur la touche au mauvais moment, il perd et donne la main au joueur suivant.

<sup>:bulb: Remplacez les images par des captures d'écran de votre jeu.</sup>

---

![bg right:50%](https://th.bing.com/th/id/OIP.55U-8PJe_zHnA7d7grEveQHaGO?pid=ImgDet&rs=1)


# GUITAR HERO


### Structures

- `struct Note`
    - `int x`
    - `int y`
    - `int vitesse`
    - `int touche`
    - `int estAppuyee`
    - `int estAffichee`

---
![bg right:50%](https://th.bing.com/th/id/OIP.55U-8PJe_zHnA7d7grEveQHaGO?pid=ImgDet&rs=1)

### Fonctions

- `void initialiserNotes()`
- `void afficherNotes()`
- `void detecterAppuiTouche()`
- `void afficherScore()`
- `void afficherGagnant()`



### Tableaux

- `struct Note notes[20]`


---

![bg right:42%](images/algorigramme_guitarhero_partie1.png)

# GUITAR HERO

### Graphe d'appel

<br>

<div class="mermaid">
%%{init: {'theme':'neutral'}}%%
flowchart LR
    GuitarHero --> initialiserNotes
    GuitarHero --> afficherNotes
    GuitarHero --> detecterAppuiTouche
    GuitarHero --> afficherScore
    GuitarHero --> afficherGagnant
</div>


---

![bg right:42%](images/algorigramme_guitarhero_partie2.png)

# GUITAR HERO

### Logigramme

---
![bg right:40%](https://th.bing.com/th/id/R.f2ba0f6dd0d0c4bca7c7625e68ad7229?rik=SKoFRtUm7aRqqw&pid=ImgRaw&r=0)

# Paris hippiques 

*Réalisé par : **Shaïma** (100%)*

-Le jeu se joue à deux joueurs.
-Il y a 5 tickets par joueur.
-Les 2 joueurs choisissent un cheval chacun.
-Les chevaux se déplacent tous à une vitesse aléatoire.
-Le premier cheval à atteindre la ligne d'arrivée gagne la course et le joueur qui a choisi le cheval gagnant gagne 1 ticket. 


---

![bg :40%](https://th.bing.com/th/id/R.676b2e9860d1c230859f356d52eaab13?rik=DDVY97zEIGgeMg&riu=http%3a%2f%2f1.bp.blogspot.com%2f_GJmSkzXiepQ%2fTDes5OU72gI%2fAAAAAAAAAFQ%2femh27J6kX4M%2fw1200-h630-p-k-no-nu%2fcharismatic%2b001.JPG&ehk=GbnLZQVjDHglPg2%2fgSNsKTzVLLdCO%2f27JIMOEUK2TIM%3d&risl=&pid=ImgRaw&r=0)

# Paris hippiques (edition my little pony)

### Graphe d'appel

<br>

<div class="mermaid">
%%{init: {'theme':'neutral'}}%%
flowchart LR
    parisHippiques --> initialiserChoixcheval
    initialiserPosition --> positionnerCheval
    parisHippiques --> deplacerChevaux
    deplacerChevaux --> InitaliserVitesseAleatoire
    parisHippiques --> detecterLigneArrivee
    detecterLigneArrivee --> ChevalGagnant --> ChoixCheval -->afficherGagnant
</div>

---
# Structures

- `struct Cheval`
    - `int x`
    - `int vitesse`
    - `int xArrivee`
    - `int choixjoueur1,choixjoueur2`

![bg right:50%](https://th.bing.com/th/id/OIP.55U-8PJe_zHnA7d7grEveQHaGO?pid=ImgDet&rs=1)

---

# Fonctions
![bg right:50%](https://th.bing.com/th/id/OIP.55U-8PJe_zHnA7d7grEveQHaGO?pid=ImgDet&rs=1)

- `int main` (tout est regroupé dans le main)
- `initialiserChoixCheval()`
- `positionnerCheval()`
- `deplacerChevaux()`
- `InitaliserVitesseAleatoire()`
- `detecterLigneArrivee()`
- `ChevalGagnant()`
- `afficherGagnant()`

---

# Logigramme
![bg right:40%](images/algorigramme_course_hippique_image.png)


---
![bg right:50%](https://th.bing.com/th/id/R.079b197c46059da0428789b4fabe5e8b?rik=RsM3X9D4%2fwSADw&pid=ImgRaw&r=0)

# Snake à 2 joueurs

*Réalisé par : **Léon** (100%)*

- Le jeu se joue à deux joueurs.
- Géré avec des listes chaînées
- Les 2 joueurs se voient attribuer chacun un serpent.
- Le but du jeu est de manger le plus de pommes possible tout en évitant de se mordre la queue, de se prendre un mur ou le corps du serpent adverse.


---

![bg :10%](https://image.winudf.com/v2/image/Y29tLnNuYWtlY29tcGFueS5zbmFrZWdhbWVfc2NyZWVuXzFfanhsM21pams/screen-1.jpg?fakeurl=1&type=.jpg)

# Snake à 2 joueurs

### Graphe d'appel

<br>

<div class="mermaid">
%%{init: {'theme':'neutral'}}%%
flowchart LR
    snake --> initialiserSerpent
    initialiserSerpent --> afficherSerpent
    snake --> deplacerSerpent
    deplacerSerpent --> detecterCollision
    detecterCollision --> afficherGagnant
    afficherGagnant --> afficherScore
    afficherScore --> afficherGagnant
</div>


---
# Structures

- `struct Serpent`
    - `int x, y`
    - `int direction`
    - `int previous_pos_x, previous_pos_y`
    - `struct Snake *next`
    - `bool is_head`

![bg right:55%](https://th.bing.com/th/id/OIP.55U-8PJe_zHnA7d7grEveQHaGO?pid=ImgDet&rs=1)

---

# Fonctions
![bg right:50%](https://th.bing.com/th/id/OIP.55U-8PJe_zHnA7d7grEveQHaGO?pid=ImgDet&rs=1)


- `void initSNAKE()`
- `void initfood()`
- `void lib_memoire()`
- `void draw_SNAKE()`
- `void add_block()`
- `void move_SNAKE()`
- `void gestion_mouvements()`
- `collision_mort()`
- `collision_food()`

---

# Logigramme
![bg right:42%](images/algorigramme_snake_image.png)



---

![bg right:50%](https://th.bing.com/th/id/OIP.GLUOTz6Wzd5QpJcNloihsAHaHN?pid=ImgDet&rs=1)

# Jackpot

*Réalisé par : **Mathéo** (100%)*

- Le jeu se joue à deux joueurs.
- Il y a 5 tickets par joueur.
- A l'aide du bouton START, le joueur lance la machine.
- Les roues tournent et s'arrêtent aléatoirement sur un symbole.
- Si les 3 symboles sont identiques, le joueur gagne 1 ticket.
- Si les 3 symboles sont différents, le joueur perd 1 ticket.

---

![bg :100%](https://th.bing.com/th/id/OIP.Juq-qSumAJgHoaGvW8uphgHaFj?pid=ImgDet&rs=1)

# Jackpot

### Graphe d'appel

<br>

<div class="mermaid">
%%{init: {'theme':'neutral'}}%%
flowchart LR
    jackpot --> initialiserJackpot
    initialiserJackpot --> afficherJackpot
    jackpot --> lancerJackpot
    lancerJackpot --> afficherJackpot
    lancerJackpot --> detecterGagnant
    detecterGagnant --> afficherGagnant
    afficherGagnant --> afficherScore
    afficherScore --> afficherGagnant
</div>

---
# Structures

- `struct Jackpot`
    - `int x`
    - `int y`
    - `int signe1`
    - `int signe2`
    - `int signe3`
    - `bool estGagnant`


![bg right:40%](https://th.bing.com/th/id/OIP.55U-8PJe_zHnA7d7grEveQHaGO?pid=ImgDet&rs=1)

---

# Fonctions
![bg right:40%](https://th.bing.com/th/id/OIP.55U-8PJe_zHnA7d7grEveQHaGO?pid=ImgDet&rs=1)

- `int main()` (tout est regroupé dans le main)
- `void initialiserJackpot()`
- `void afficherJackpot()`
- `void lancerJackpot()`
- `void detecterGagnant()`
- `void afficherGagnant()`
- `void afficherScore()`

---

# Logigramme
![bg right:42%](images/algorigramme_jackpot_image.png)


---
![bg right:40%](https://th.bing.com/th/id/R.0b9c1ea9228696e1b8ec1b103c119771?rik=nYxF5AWapSvOGQ&pid=ImgRaw&r=0)

# JEUX BONUS

## FloppyBird

*Réalisé par : **Shaïma** (100%)*

- Le jeu se joue à 2 joueurs.
- Le premier joueur pourra controler son oiseau grace à la touche espace, l'autre avec la touche entrée.
- Le but du jeu sera de faire le plus grand score possible en essayant de ne pas se heurter aux obstacles.
- Le gagnant se verra attribuer un ticket supplémentaire.

---

![bg :40%](https://th.bing.com/th/id/OIP.yhUkoSouuc2Eah1icWy4YQHaHa?pid=ImgDet&w=512&h=512&rs=1)



### Graphe d'appel

<br>

<div class="mermaid">
%%{init: {'theme':'neutral'}}%%
graph LR
    FloppyBird --> initialiserOiseau
    initialiserOiseau --> afficherOiseau
    FloppyBird --> deplacerOiseau
    deplacerOiseau --> créerCollision
    créerCollision --> detecterCollision
    detecterCollision --> afficherScore
    afficherScore --> afficherGagnant
</div>


---
# Structures

- `struct Oiseau`
    - `int x`
    - `int y`
    - `int vitesse`
    - `bool obstacletouche`


![bg right:50%](https://th.bing.com/th/id/OIP.55U-8PJe_zHnA7d7grEveQHaGO?pid=ImgDet&rs=1)

---

# Fonctions
![bg right:40%](https://th.bing.com/th/id/OIP.55U-8PJe_zHnA7d7grEveQHaGO?pid=ImgDet&rs=1)

- `int main()` (tout est regroupé dans le main)
- `void initialiserOiseau()`
- `void afficherOiseau()`
- `void deplacerOiseau()`
- `void créerCollision()`
- `void detecterCollision()`
- `void afficherGagnant()`
- `void afficherScore()`
---


# JEUX BONUS

## The Maze
![bg right:40%](https://i.ytimg.com/vi/uC3nOV7YQ7s/maxresdefault.jpg)

*Réalisé par : **Alfred** (100%)*

- Le jeu se joue à 2 joueurs.
- Le premier joueur pourra controler son personnage grace aux touches ZQSD, l'autre avec les flèches directionnelles.
- Le but du jeu sera de faire le plus grand score possible en essayant de ne pas se heurter aux murs mais de trouver la sortie du labyrinthe en premier.
- Le gagnant se verra attribuer un ticket supplémentaire.

---
# Graphe d'appel

![bg right:40](https://th.bing.com/th/id/R.3ca8972be64fb427187c700b2f112d56?rik=ko1fpYUqTOS%2fyw&riu=http%3a%2f%2fiversonboyan.50webs.com%2fPhotoshop%2fThe+Maze.jpg&ehk=fjqZY%2fD1aqOGSFgnx1H2gY1TBy%2ff6lqaV9D348QtlQ0%3d&risl=&pid=ImgRaw&r=0)

<br>

<div class="mermaid">
%%{init: {'theme':'neutral'}}%%
graph LR
    TheMaze --> initialiserPersonnage
    initialiserPersonnage --> afficherPersonnage
    TheMaze --> deplacerPersonnage
    deplacerPersonnage --> detecterSortie
    detecterSortie --> afficherGagant
</div>

---

# Structures

- `struct Personnage`
    - `int x`
    - `int y`
    - `int vitesse`
    - `bool estGagnant`

![bg right:50%](https://th.bing.com/th/id/OIP.55U-8PJe_zHnA7d7grEveQHaGO?pid=ImgDet&rs=1)

---

# Fonctions

- `int main()` (tout est regroupé dans le main)
- `void initialiserPersonnage()`
- `void afficherPersonnage()`
- `void deplacerPersonnage()`
- `void detecterSortie()`
- `void determinerGagnant()`

![bg right:50%](https://th.bing.com/th/id/OIP.55U-8PJe_zHnA7d7grEveQHaGO?pid=ImgDet&rs=1)

---

![bg right:50%](https://www.stepindance.fr/wp-content/uploads/2018/11/mattel-jeux-chass-taupes.jpg)
# Tape taupe

*Réalisé par : **Mathéo** (100%)*

- Le jeu se joue à 2 joueurs.
- Le joueur doit taper sur les taupes qui sortent du trou.
- Le joueur gagne 1 point par taupe tapée.
- Le joueur perd 1 point si il tape sur un trou vide.
- Le joueur qui a le plus de points gagne 1 ticket.

---
![bg :40%](https://coolrom.com/screenshots/nds/That's%20So%20Raven%20-%20Psychic%20on%20the%20Scene%20(2).jpg)

# Graphe d'appel

<br>
<div class="mermaid">
%%{init: {'theme':'neutral'}}%%
graph LR
    TapeTaupe --> initialiserTapeTaupe
    initialiserTapeTaupe --> afficherTapeTaupe
    TapeTaupe --> taperTaupe
    taperTaupe --> detecterGagnant
    detecterGagnant --> afficherGagnant
    afficherGagnant --> afficherScore
    afficherScore --> afficherGagnant
</div>

---

# Structures

- `struct TapeTaupe`
    - `int x`
    - `int y`
    - `bool estVivant`
    - `bool estTape`
    - `bool Gagnant`
    - `int score`

![bg right:40%](https://th.bing.com/th/id/OIP.55U-8PJe_zHnA7d7grEveQHaGO?pid=ImgDet&rs=1)

---

# Fonctions

- `int main()` (tout est regroupé dans le main)
- `void initialiserTapeTaupe()`
- `void afficherTapeTaupe()`
- `void taperTaupe()`
- `void detecterGagnant()`
- `void afficherGagnant()`
- `void afficherScore()`

![bg right:40%](https://th.bing.com/th/id/OIP.55U-8PJe_zHnA7d7grEveQHaGO?pid=ImgDet&rs=1)


---
# Attrape Chat (TAG)
![bg right:50%](https://th.bing.com/th/id/R.8120d8d8e07e9ac87e7df7c81de7e5c5?rik=DDsQ%2f5ilxFU14Q&pid=ImgRaw&r=0)

*Réalisé par : **Léon** (100%)*

- Le jeu se joue à 2 joueurs, et est dans le style platformer 2D.
- Le joueur doit attraper la souris (aka le joueur adverse) qui se déplace sur une carte 2D.
- Le joueur gagne 1 point si il attrape la souris.
- Le joueur touché deviendra alors le chat et vice-versa.

---
# Graphe d'appel

<br>
<div class="mermaid">
%%{init: {'theme':'neutral'}}%%
graph LR
    AttrapeChat --> initialiserAttrapeChat
    initialiserAttrapeChat --> afficherAttrapeChat
    AttrapeChat --> attraperChat
    attraperChat --> detecterGagnant
    detecterGagnant --> afficherGagnant
    afficherGagnant --> afficherScore
    afficherScore --> afficherGagnant
</div>

---

# Structures

- `struct AttrapeChat`
    - `int x`
    - `int y`
    - `bool estAttrape`
    - `bool Gagnant`
    - `int score`
    - `int ticket`

![bg right:40%](https://th.bing.com/th/id/OIP.55U-8PJe_zHnA7d7grEveQHaGO?pid=ImgDet&rs=1)

---
# Fonctions

- `int main()` (tout est regroupé dans le main)
- `void initialiserAttrapeChat()`
- `void afficherAttrapeChat()`
- `void attraperChat()`
- `void detecterGagnant()`
- `void afficherGagnant()`
- `void afficherScore()`

![bg right:40%](https://th.bing.com/th/id/OIP.55U-8PJe_zHnA7d7grEveQHaGO?pid=ImgDet&rs=1)

---


# GEOMETRY DASH

![bg right:50%](https://th.bing.com/th/id/R.0df9ec9d7126054da4c8306678c3af92?rik=jve%2frmvWRTBMNA&riu=http%3a%2f%2f2.bp.blogspot.com%2f-Wl1AS-zKl0s%2fVZVcSDOSckI%2fAAAAAAAAAJ8%2fWAFNDi4o_Hc%2fs1600%2fGeometryDash.png&ehk=xkArEQZGRRbWDGd0ekqI1PmY0DVkVFeYebYySbqiUEU%3d&risl=&pid=ImgRaw&r=0)

*Réalisé par : **Alfred** (100%)*

- Le jeu se joue à 2 joueurs.
- Les joueurs pourront controler leurs cubes grace à la barre espace et la fleche directionnelle du haut.
- Le but du jeu sera de faire le plus grand score possible en essayant de ne pas se heurter aux obstacles.
- Le gagnant se verra attribuer un ticket supplémentaire.

---

# Graphe d'appel
![bg :50%](https://i.ytimg.com/vi/tRnVhXQ-ayg/maxresdefault.jpg)

<br>
<div class="mermaid">
%%{init: {'theme':'neutral'}}%%
graph LR
    GeometryDash --> initialiserCube
    initialiserCube --> afficherCube
    GeometryDash --> deplacerCube
    deplacerCube --> detecterCollision
    detecterCollision --> afficherScore
    afficherScore --> afficherGagnant
    afficherGagnant --> afficherScore
</div>

---

# Fonctions

![bg right:40%](https://th.bing.com/th/id/OIP.55U-8PJe_zHnA7d7grEveQHaGO?pid=ImgDet&rs=1)

- `void initaliserCube()`
- `void afficherCube()`
- `void deplacerCube()`
- `void detecterCollision()`
- `void afficherScore()`
- `void afficherGagnant()`

---

# Structures 

![bg right:40%](https://th.bing.com/th/id/OIP.55U-8PJe_zHnA7d7grEveQHaGO?pid=ImgDet&rs=1)

- `struct Cube`
    - `int x`
    - `int y`
    - `int vitesse`
    - `bool estMort`
    - `bool estGagnant`
    - `int score`
    - `int ticket`

---


<!--
_class: lead
-->

# Les slides suivantes ne seront pas présentées oralement lors de la soutenance mais doivent figurer dans la présentation. Nous les survolerons rapidement.

---

# BILAN

## Tâches réalisées (pour chaque membre de l'équipe)

- `✅ 100%` Créer une carte, 2 joueurs et un classement (carte.c)
    - *Pour certains jeux, les regles et les scores ne sont pas affichés mais c'est en route.*
- `✅ 100%` Terminer les 9 jeux (jeu.c)
    - *Tous les jeux sont terminés.*
- `✅ 100%` Relier la carte aux jeux (main.c)
    - *Les jeux sont reliés à la carte et s'executent normalement.*

---

# Bilan individuel
Matheo : projet amusant et interessant / grande comprehension de Github et de la bibliotheque Allegro / Meilleure organisation et meilleure gestion du temps.

Shaima : Super projet / Très bonne communication et cohésion /Très bon moyen d’apprendre et de consolider ses acquis en C

Leon : Beaucoup de plaisir à travailler sur ce projet / Manque de temps global pour implémenter les jeux des autres / Bonne cohésion d'équipe

Alfred : Projet très ressourçant / Intéressant et instructif sur les librairies graphiques / Collaboration Git très efficace / Bon travail d'équipe

---

# Investissement

Si vous deviez vous répartir des points, comment feriez-vous ?

<div class="mermaid">
%%{init: {'theme':'neutral'}}%%
pie showData
    "Shaïma" : 20
    "Mathéo" : 20
    "Léon" : 30
    "Alfred" : 30
</div>

---

# Récapitulatif des jeux

| Jeu | Avancement | Problèmes / reste |  
| --- | --- | --- |
| Paris hippiques | 100% | - |
| Guitar Hero | 100% | - |
| Snake | 100% | - |
| Jackpot | 100% | - |
| Floppybird | 100% | - |
| The Maze | 100% | - |
| Tape-taupe | 100% | - |
| Geometry dash | 100% | - | 
| Attrape-chat | 100% | SAUT MURAL BIZARRE|




<!--
_class: lead
-->


---

# Schémas et Graphes

![bg left : 100%](./images/commit.jpeg)
Comits et activités des membres de l'équipe

---
![bg left : 100%](./images/frequence_code.jpeg)

# Comparaison entre l'ajout des éléments et leurs retraits

---

![bg right : 90%](./images/frequence_commit.jpeg)

## Comparaison entre les commits et les ajouts de lignes de code dans une periode hebdomadaire

---
# Merci de nous avoir écoutés !

![bg right : é0%](./images/nintendeau.bmp)
