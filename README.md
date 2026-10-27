# Génération d'arbres binaires (nombres de Catalan)

Résumé en français des trois fichiers C : `depot_catalon_shell.c`, `parenthese_foret_binary_main.c`, `time.c`.

## Vue d'ensemble

Ces trois fichiers C forment un seul programme (assemblé par des `#include` en cascade) qui :

1. lit un entier `n` (nombre de sommets) ;
2. énumère toutes les séquences de parenthèses bien formées de longueur `2n` — les mots de Dyck, qui représentent tous les arbres binaires à n nœuds (nombres de Catalan) ;
3. convertit chaque séquence en **forêt** (matrice d'adjacence), puis en **arbre binaire** (transformation « fils gauche / frère droit ») ;
4. enregistre chaque arbre dans un fichier Graphviz `.gv`, puis le rend en image `.gif` via l'outil `dot`.

## 1 · `depot_catalon_shell.c` — stockage, nombre de Catalan, rendu

- `stock()` : écrit pour chaque arbre `i` un fichier `binarytree{i}.gv` (nœuds, arêtes, couleurs) à partir des tableaux globaux `strings[]` (arêtes `i -- j`) et `color[]` (styles de nœuds), en avançant les indices globaux `index1`/`index2`.
- `Catalan(n)` : calcule récursivement le n-ième nombre de Catalan, `C(n) = C(n−1)·2(2n−1)/(n+1)`, avec `C(1)=1`.
- `shell()` : lance `system("dot -Tgif ...")` pour chaque `.gv` afin de produire `binarytree{i}.gif`.

## 2 · `parenthese_foret_binary_main.c` — le cœur du programme

- Définit le type `Mytree` (matrice d'adjacence `arc[100][100]` + `n_sommet`) et les constantes `Racine=0`, `ArcFils1=1`, `ArcFils2=2`, `NonArc=8888`.
- `recompose_p()` : énumère toutes les séquences de parenthèses équilibrées (algorithme itératif à `goto`) ; pour chacune, appelle `print_p()` puis `forets()`.
- `forets()` : construit la forêt en analysant la séquence — `(` en tête → racine ; `((` → premier fils (ArcFils1) ; `)(` → autre fils / frère (ArcFils2) ; vérifie aussi l'équilibre des parenthèses.
- `binary()` : transforme la forêt en arbre binaire — les racines sont chaînées comme fils droits, ArcFils1 devient fils gauche (vert), ArcFils2 fils droit (rouge) ; remplit `strings[]`/`color[]` pour Graphviz.
- `print_p()` : affiche la séquence de parenthèses.
- `main()` : lit `n`, lance la génération, puis `Catalan()`, `stock()`, `shell()`.

## 3 · `time.c` — banc de test / chronométrage

- Variante de `main()` qui lit `n`, alloue les mêmes tableaux et mesure avec `clock()` **uniquement** le temps de `recompose_p()` ; la partie `stock()`/`shell()` y est commentée.

## Chaîne d'appels et données partagées

`time.c → parenthese_foret_binary_main.c → depot_catalon_shell.c` (inclusions successives).

Flux : `n → mots de Dyck → forêt → arbre binaire → .gv → .gif`.

Les tableaux globaux `strings`, `color` et les indices `index1`, `index2`, `pt`, `nb_arbre` servent de communication entre les étapes.

## Remarques / points fragiles

- `time.c` inclut un fichier qui définit déjà `main()` : compilé tel quel, double définition de `main` (non compilable isolément).
- Énumération par `goto` (peu lisible), tampons de taille fixe (`10000 × 100`), et quelques allocations utilisent `sizeof(char*)` au lieu de `sizeof(char)` — fragile si `n` devient grand.
