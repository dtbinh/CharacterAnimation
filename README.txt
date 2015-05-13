 
 
 
* Le code 
svn checkout https://svn.liris.cnrs.fr/ameyer/code/teaching/CharAnim_m2pro --username m2pro
login: m2pro
passwd: -m2pro-


 
* Les dépendances du code
 - OpenGL/GLUT : cf doc du cours de rendu
 - cmake pour generer un makefile, un projet codeblocks ou un projet Visual
 - En option : BulletPhysics pour la 3e partie du TP : MoCap et Animation Physique
 - Le code a été testé sous Linux au Nautibus, un windows disposant de SVN/cmake/GLUT/(Bullet en option)

 
* Pour compiler
 Compiler avec un Makefile 
     cd ....../CharAnim_m2pro/build
     /home/pers/alexandre.meyer/lib/Linux/cmake-2.8.3-Linux-i386/bin/cmake ..
     make
     ...../CharAnim_m2pro/build/CharA

 Compiler avec codeblocks 
     cd ....../CharAnim_m2pro/build-cb
     /home/pers/alexandre.meyer/lib/Linux/cmake-2.8.3-Linux-i386/bin/cmake -G "CodeBlocks - Unix Makefiles" ..
     codeblocks
     ouvrir le projet CharA.cbp dans ..../CharAnim_m2pro/build

 - La class CAViewer contient les fonctions init/draw qui s'occupent de l'affichage
 - Pour ajouter des fichiers au projet, regarder ..../CharAnim/CMakeLists.txt
 - Pour la 3e partie du TP, ce code utilise libBullet qui est dans ~alexandre.meyer/lib/Linux/bullet. Pour désactiver Bullet, editer le fichier ..../CharAnim/CMakeLists.txt et indiquer "NO" devant "WITH_BULLET".