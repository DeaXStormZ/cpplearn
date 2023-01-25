# TODO

## Scope

## auto

## Operator overload

## Headers (.h)

## Heap/stack

## Classes

## Macros

## STD

vector: cf. [guide](https://code.probayes.net/probayes/devops/code-community-kb/-/wikis/guide/cpp/astuces/std::vector)

## Misc
TODO put this in the right places
  - avoid use of auto
  - new => crée un raw ptr
  - jamais passer en arg des ptrs, utiliser via reference ou const ref; par contre en renvoyer c'est possible
  - mettre des const de partout
  - creer des obj sur la stack si possible. new crée sur la heap, donc éviter au max
TODO stack >> heap. faire des vecteurs d'objet, + rapide car prefetching. jamais de tri sur un vecteur d'obj. vecteur de ref de pointers dans ce cas, les ref de ptrs sont move. demander à Jordi notation constructeur pour limiter nb move et copy 