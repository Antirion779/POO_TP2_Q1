# Simulation de Pigeons

Cette application simule le comportement de pigeons dans un environnement 2D où ils cherchent de la nourriture, dorment ou se dispersent en cas de panique. Chaque pigeon est contrôlé par un thread indépendant, permettant un comportement asynchrone et réaliste. Cette simulation utilise la bibliothèque **SFML** pour l'affichage graphique.

## Fonctionnalités

- **Recherche de nourriture** : Les pigeons détectent et se déplacent vers la nourriture la plus fraîche disponible dans leur champ de vision.
- **Consommation de nourriture** : Une fois en contact avec de la nourriture, celle-ci est immédiatement consommée et disparaît de la scène.
- **État d'endormissement** : En l'absence de nourriture, les pigeons s'endorment et ne se déplacent pas.
- **Panique et dispersion** : Avec une probabilité variable, les pigeons peuvent se disperser aléatoirement même en l'absence de nourriture, simulant un comportement de panique.
- **Affichage graphique** : La position, la couleur et le comportement des pigeons et de la nourriture sont affichés graphiquement avec SFML.

## Prérequis

1. **SFML** : Assurez-vous d'avoir installé la bibliothèque SFML.
   - Vous pouvez télécharger SFML depuis [le site officiel](https://www.sfml-dev.org/download.php).
   - Suivez les instructions pour l'installation et la configuration de SFML avec votre compilateur.
2. **Compilateur C++** : Un compilateur prenant en charge le C++11 (ou version ultérieure) est requis.

## Installation

1. Clonez le dépôt :
   ```bash
   git clone https://github.com/username/simulation-de-pigeons.git
   cd simulation-de-pigeons
   ```

2. Compilez l'application :
   ```bash
   g++ -std=c++11 -o simulation main.cpp Simulation.cpp Pigeon.cpp Food.cpp -lsfml-graphics -lsfml-window -lsfml-system -pthread
   ```
   Assurez-vous que les chemins d'accès à SFML sont correctement configurés en fonction de votre environnement de développement.

## Utilisation

### Démarrage de la Simulation

Lancez l'application avec la commande suivante :
```bash
./simulation
```

### Commandes et Interaction

- **Ajout de nourriture** : Cliquez n'importe où dans la fenêtre pour ajouter de la nourriture à cet emplacement.
- **Observation des comportements** :
  - Les pigeons se dirigent automatiquement vers la nourriture la plus fraîche à proximité.
  - En l'absence de nourriture, les pigeons entrent en état d'endormissement et deviennent inactifs.
  - Une fois qu'un pigeon entre en contact avec de la nourriture, celle-ci est consommée et disparaît.
  - De temps en temps, certains pigeons peuvent entrer en état de panique et se disperser dans des directions aléatoires.

### Arrêt de la Simulation

Pour quitter l'application, fermez la fenêtre de simulation. Tous les threads seront automatiquement terminés.

## Structure du Code

- **main.cpp** : Initialise la simulation et gère la boucle principale.
- **Simulation.cpp / Simulation.h** : Gère l'affichage, la synchronisation des pigeons et le contrôle de la liste de nourriture.
- **Pigeon.cpp / Pigeon.h** : Définit le comportement de chaque pigeon, incluant les interactions avec la nourriture et la panique.
- **Food.cpp / Food.h** : Représente les éléments de nourriture et leur état de fraîcheur.

## Dépendances

- **SFML** pour l'affichage graphique
- **pthread** pour la gestion des threads

## Notes

- Si vous souhaitez ajuster le comportement des pigeons (par exemple, le rayon de vision ou la fréquence de panique), vous pouvez modifier les paramètres dans `Pigeon.cpp`.
- La simulation utilise des verrous (`mutex`) pour garantir la sécurité des threads lors de l'accès à la liste de nourriture partagée.

## Aide et Support

Pour toute question ou assistance, veuillez contacter `Antoine.etu@uquac.ca`.

[LIENS VERS LE DOCUMENT COMPLET](https://docs.google.com/document/d/1Ops5rkYOspdqxg_SeleoJiD2V7fNzVxguQWs-uVDdXU/edit?usp=sharing)
