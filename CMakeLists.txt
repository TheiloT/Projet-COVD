cmake_minimum_required(VERSION 2.8.12)
file(TO_CMAKE_PATH "$ENV{IMAGINEPP_ROOT}/CMake" p)
list(APPEND CMAKE_MODULE_PATH "${p}") #For old Imagine++
list(APPEND CMAKE_SYSTEM_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?
find_package(Imagine REQUIRED)

project(projet-COVD)

add_executable(main
               main.cpp
               Correspondance.h
               Personnage.cpp
               Personnage.h
               Map.cpp
               Map.h
               outils.cpp
               outils.h
               edition.cpp
               edition.h
               jeu.cpp
               jeu.h
               graphismes.h
               graphismes.cpp
               menus.cpp
               menus.h
               niveaux.h
               niveaux.cpp
               Niveaux_perso.txt
               Niveaux_aventure.txt
               regles_du_jeu.txt)
ImagineUseModules(main Images)
