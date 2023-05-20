---
marp: true
theme: projet
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


# ECE World

Nintendeau

---

# Equipe Nintendeau

![bg right:50%](./images/equipe.avif)

- DALLE Léon
- DE VULPIAN Alfred
- INNOCENT Mathéo
- DEROUICH Shaïma

---

# ECE World

![bg right:50% 198%](./images/theme.webp)

## Thème

- Fête foraine 
- 9 jeux 
- 2 joueurs 
- 1 classement
- 5 tickets par joueur
---

# Carte `1/2`

*Réalisée par : **Léon**, **Alfred**.*

Décrire ici les fonctionnalités implémentées : choix joueurs, saisie des noms, affichage des scores/classement... Comment avez-vous fait ? Quels étaient les problèmes rencontrés.

---

# Carte `2/2`

Suite si ça ne tient pas sur une slide. 

:bulb: *Vous pouvez faire comme ça à chaque fois qu'une slide ne suffit pas, il vaut mieux 5 slides légères qu'une surchargée.*

---

# Organisation des jeux

Les jeux ont tous été enregistrés dans un dossier specialement créé pour eux nommé attractions. Chaque jeu est dans un fichier séparé où l'on retrouve les fonctions principales du jeu, les assets et les CMAKE.

Les jeux prennent en parametres le solde de tickets de chaque joueur et leurs choix de jeux. Ils retournent le solde de tickets de chaque joueur à la fin de la partie.

Pour lancer un jeu, il suffit de se diriger vers une des nombreuses maisons qui sont sur la map,les regles s'afficheront sur un parchemin, il suffira de cliquer sur espace pour executer le jeu.


---

![bg right:40%](images/peche_canards.jpg)

# GUITAR HERO

*Réalisé par : **Alfred** (100%)*

- Il y'a 4 touches (A, Z, E, R) qui correspondent aux 4 cordes de la guitare.
- Les notes tombent du haut de l'écran vers le bas.
- Le joueur doit appuyer sur la touche correspondant à la note au bon moment.
- Si le joueur appuie sur la touche au bon moment, il gagne un point.
- Si le joueur appuie sur la touche au mauvais moment, il perd et donne la main au joueur suivant.

<sup>:bulb: Remplacez les images par des captures d'écran de votre jeu.</sup>

---

![bg right:40%](images/peche_canards.jpg)


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
![bg right:40%](images/peche_canards.jpg)

### Fonctions

- `void initialiserNotes()`
- `void afficherNotes()`
- `void detecterAppuiTouche()`
- `void afficherScore()`
- `void afficherGagnant()`


### Tableaux

- `struct Note notes[20]`
---

![bg right:40%](images/peche_canards.jpg)

### Graphe d'appel
<br>

<div class="mermaid">
%%{init: {'theme':'neutral'}}%%
flowchart LR
    GuitarHero --> afficherNotes
    GuitarHero --> detecterAppuiTouche
    GuitarHero --> afficherScore
    GuitarHero --> afficherGagnant
</div> GuitarHero --> initialiserNotes
   


---

![bg right:40%](images/peche_canards.jpg)

# GUITAR HERO

### Logigramme





---
![bg right:40%](images/peche_canards.jpg)

# Paris hippiques

*Réalisé par : **Shaïma** (100%)*

-Le jeu se joue à deux joueurs.
-Il y a 5 tickets par joueur.
-Les 2 joueurs choisissent un cheval chacun.
-Les chevaux se déplacent tous à une vitesse aléatoire.
-Le premier cheval à atteindre la ligne d'arrivée gagne la course et le joueur qui a choisi le cheval gagnant gagne 1 ticket. 


---

![bg right:40%](images/peche_canards.jpg)

# Paris hippiques

### Graphe d'appel

<br>

<div class="mermaid">
%%{init: {'theme':'neutral'}}%%
flowchart LR
    parisHippiques --> initialiserChoixCheval
    initialiserChoixCheval --> positionnerCheval
    parisHippiques --> deplacerChevaux
    deplacerChevaux --> detecterLigneArrivee
    detecterLigneArrivee --> ChevalGagnant
    ChevalGagnant --> afficherGagnant
    afficherGagnant --> afficherScore
    afficherScore --> afficherGagnant
</div>


---
# Structures

- `struct Cheval`
    - `int x`
    - `int vitesse`
    - `int xArrivee`
    - `int choixjoueur1,choixjoueur2`

![bg right:40%](images/peche_canards.jpg)

---

# Fonctions
![bg right:40%](images/peche_canards.jpg)

- `int main` (tout  est regroupé dans le main)
- `initialiserChoixCheval()`
- `positionnerCheval()`
- `deplacerChevaux()`
- `InitaliserVitesseAleatoire()`
- `detecterLigneArrivee()`
- `ChevalGagnant()`
- `afficherGagnant()`

---

# Logigramme
![bg right:40%](images/peche_canards.jpg)


---
![bg right:40%](images/peche_canards.jpg)

# Paris hippiques

*Réalisé par : **Léon** (100%)*

-Le jeu se joue à deux joueurs.
-Il y a 5 tickets par joueur.
-Les 2 joueurs se voient attribuer chacun un serpent.
-Le but du jeu est de manger le plus de pommes possible tout en évitant de se mordre la queue, de se prendre un mur ou le corps du serpent adverse.


---

![bg right:40%](images/peche_canards.jpg)

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
    - `int x`
    - `int y`
    - `int vitesse`
    - `int direction`
    - `int taille`
    - `int estVivant`
    - `int estAffiche`
    - `int estMange`
    - `int estMort`
    

![bg right:40%](images/peche_canards.jpg)

---

# Fonctions
![bg right:40%](images/peche_canards.jpg)


- `void initialiserSerpent()`
- `void afficherSerpent()`
- `void deplacerSerpent()`
- `void detecterCollision()`
- `void afficherGagnant()`
- `void afficherScore()`


---

# Logigramme
![bg right:40%](images/peche_canards.jpg)



---

![bg right:40%](images/peche_canards.jpg)

# Jackpot

*Réalisé par : **Mathéo** (100%)*

- Le jeu se joue à deux joueurs.
- Il y a 5 tickets par joueur.
- A l'aide du bouton START, le joueur lance la machine.
- Les roues tournent et s'arrêtent aléatoirement sur un symbole.
- Si les 3 symboles sont identiques, le joueur gagne 1 ticket.
- Si les 3 symboles sont différents, le joueur perd 1 ticket.





---

![bg right:40%](images/peche_canards.jpg)

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


![bg right:40%](images/peche_canards.jpg)

---

# Fonctions
![bg right:40%](images/peche_canards.jpg)

- `int main()` (tout est regroupé dans le main)
- `void initialiserJackpot()`
- `void afficherJackpot()`
- `void lancerJackpot()`
- `void detecterGagnant()`
- `void afficherGagnant()`
- `void afficherScore()`


---

# Logigramme
![bg right:40%](images/peche_canards.jpg)


---
![bg right:40%](images/peche_canards.jpg)

# Snake à 2 joueurs

*Réalisé par : **Léon** (100%)*

-Le jeu se joue à deux joueurs.
-Il y a 5 tickets par joueur.
-Les 2 joueurs se voient attribuer chacun un serpent.
-Le but du jeu est de manger le plus de pommes possible tout en évitant de se mordre la queue, de se prendre un mur ou le corps du serpent adverse.


---

![bg right:40%](images/peche_canards.jpg)

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
    - `int x`
    - `int y`
    - `int vitesse`
    - `int direction`
    - `int taille`
    - `int estVivant`
    - `int estAffiche`
    - `int estMange`
    - `int estMort`
    

![bg right:40%](images/peche_canards.jpg)

---

# Fonctions
![bg right:40%](images/peche_canards.jpg)


- `void initialiserSerpent()`
- `void afficherSerpent()`
- `void deplacerSerpent()`
- `void detecterCollision()`
- `void afficherGagnant()`
- `void afficherScore()`
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
- `❌ 80%` Relier la carte aux jeux (carte.c)
    - *Les jeux sont reliés à la carte mais l'execution des programmes demeure tres instable (beaucoup de crashs).*

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
| Floppybird | 90% | Jeu totalement fonctionnel, seul petit soucis avec la marge de collision entre l'obstacle et l'oiseau  |
| The Maze | -% | pas plus d'infos |
| Tape-taupe | 100% | - |
| Geometry dash | -% | pas plus d'infos |
| Attrape Chat | -% | pas plus d'infos |



<!--
_class: lead
-->
