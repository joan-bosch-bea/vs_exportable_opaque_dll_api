# Creació d'una DLL amb API exportable opaca en Visual Studio

En aquest document pretenc descriure els passos per crear una DLL amb API exportable opaca en Visual Studio. El projecte estarà fet en C++ i constarà d'una única classe amb un únic mètode.

## Pas 1: Creació del projecte
Obrir Visual Studio, seleccionar la creació d'un projecte Dinamic-Link Library (DLL) en C++ per a Windows, indicar el nom del projecte i crear:

<img width="1013" height="674" alt="captura" src="https://github.com/user-attachments/assets/b4ac6250-b7d6-4554-9b48-931794973c60" />

<img width="1013" height="674" alt="captura" src="https://github.com/user-attachments/assets/783ea31e-8a5e-4b20-a93d-a09d7f84d5dc" />

## Pas 2: Estructurar el projecte
Per facilitar la identificació dels components del projecte és sempre una bona pràctica estructurar el projecte de manera adequada. Una estructura correcta per un projecte de dll amb api opaca és situar els arxius de capçalera visibles pel client de la dll al directori "include" i els arxius amb la lògica al directori "src". Al seu torn, la lògica s'hauria d'organitzar en subdirectoris per a cada component. D'entrada el directori "src" tindrà dos subdirectoris: "src/api" contindrà el wrapper de tota la funcionalitat exportada, i "src/core" on hi haurà la classe principal. L'estructura de directoris per al projecte serà la següent:

- directori/arrel
  - include
    - Opaque.h
    - Opaque.hpp
  - src
      - api
        - Opaque_c_api.cpp
      - core
        - Opaque.h
        - Opaque.cpp


