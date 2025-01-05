# Deux Salles - Deux Ambiances

**Projet M2 Synthèse d’Images**

Ce projet est une application 3D immersive permettant de naviguer entre deux environnements distincts, chacun proposant des objets différents et des modèles d’illumination variés.

## 🚀 Fonctionnalités principales

- **Deux salles thématiques :** Explorez des environnements contrastés, une ville de nuit et une journée dans la nature.
- **Modèles d’illumination avancés :** Blinn-Phong, Cell Shading et transparence multi-couches.
- **Animation et interaction :** Objets animés, lumières interactives et contrôle en temps réel.

## 🛠️ Compilation

Pour compiler le projet, suivez ces étapes :

```bash
mkdir build
cd build
cmake ..
make
cd ..
```

## 🎯 Lancement

Une fois compilé, lancez l’application avec la commande suivante :

```bash
./bin/2salles2ambiances
```

## 🎮 Contrôles

Voici les commandes pour interagir avec les environnements 3D :

| Action                                      | Touche               |
| ------------------------------------------- | -------------------- |
| Déplacements                                | Z, Q, S, D           |
| Tourner la caméra                           | Mouvements de souris |
| Quitter l’application                       | Échap                |
| Activer/désactiver le mode fil de fer       | F                    |
| Lancer/stopper l’animation de la salle 1    | A                    |
| Activer/désactiver la lumière de la salle 1 | E                    |

## 🌍 Comparaison des salles

Voici une comparaison du contenu de chacune des deux salles :

|                     | Salle 1                    | Salle 2                                   |
| ------------------- | -------------------------- | ----------------------------------------- |
| Theme               | Ville de nuit              | Journée dans la nature                    |
| Système d'éclairage | Blinn-Phong                | Blinn-Phong + Cell Shading 4              |
| Lumières            | 2 Point Lights             | 1 Directional + 1 Point Light             |
| Objet 1             | Lampadaire                 | Chalet                                    |
| Objet 2             | Luciole                    | Rocher                                    |
| Spécificité         | Luciole animée et éclairée | Transparence multi-couches sur les vitres |
