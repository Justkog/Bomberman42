# Bomberman42
C++ Project 42, Bomberman 3D
## Projet:
Tous se qu'il y a dans le dossier Assets se charge automatiquement
```
Assets::GetModel("..."); => Return BeerEngine::Graphics::Mesh *
Assets::GetTexture("textures/crate1_diffuse.png"); => Return BeerEngine::Graphics::Texture *
Assets::GetAudioClip("..."); => Return BeerEngine::Audio::AudioClip *
```
Cela evitera de charger deux fois la meme texture ou le meme model.
### Link
[GLFW](http://www.glfw.org/docs/latest/index.html)
[GLM](https://glm.g-truc.net/0.9.4/api/a00131.html)
[Nuklear Help](https://github.com/vurtun/nuklear/wiki/Window)
## Help:
### Git
Voici une piqure de rappel de git!
- **git clone "url" [folder]** : Clone un depot en local
- **git checkout "branch"** : Permet de changer de branche du depot
- **git branch "branch"** : Permet de creer une branche au depot
- **git checkout -b "branch"** : Permet de creer et de changer de branche
- **git pull** : Permet de telecharger les changements de la branche courante
- **git status** : Affiche les fichiers different du depot
- **git add "file or dir"** : Ajout les changements au prochain commit
- **git commit -m"msg"** : Enregistre le commit de façon local avec un commentaire
- **git push** : Envoie le(s) commit(s) enregistre sur le depot dans la branche courante
- **git merge "branch"** : Funsionne une branche avec la branche courante.