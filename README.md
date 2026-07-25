# Creació d'una DLL amb API exportable opaca en Visual Studio

En aquest document pretenc descriure els passos per crear una DLL amb API exportable opaca en Visual Studio. El projecte estarà fet en C++ i constarà d'una única classe amb un únic mètode.

## Descripció del projecte
Aquí posaré una petita descripció del que vol dir API exportable opaca i la millora que aporta els fets de ser eportable i opaca.

## 1: Creació del projecte
Obrir Visual Studio, seleccionar la creació d'un projecte Dinamic-Link Library (DLL) en C++ per a Windows, indicar el nom del projecte i crear:

<img width="1013" height="674" alt="captura" src="https://github.com/user-attachments/assets/b4ac6250-b7d6-4554-9b48-931794973c60" />

<img width="1013" height="674" alt="captura" src="https://github.com/user-attachments/assets/783ea31e-8a5e-4b20-a93d-a09d7f84d5dc" />

## 2: Estructurar el projecte
Per facilitar la identificació dels components del projecte és sempre una bona pràctica estructurar el projecte de manera adequada. Una estructura correcta per un projecte de dll amb api opaca és situar els arxius de capçalera visibles pel client de la dll al directori "include" i els arxius amb la lògica al directori "src". Al seu torn, la lògica s'hauria d'organitzar en subdirectoris per a cada component. D'entrada el directori "src" tindrà dos subdirectoris: "src/api" contindrà el wrapper de tota la funcionalitat exportada, i "src/core" on hi haurà la classe principal. L'estructura de directoris per al projecte serà la següent:

- arrel/include
- arrel/src/api
- arrel/src/core

## 3: Crear l'arbre de directoris fisics
Des de l'explorador d'arxius o des de la vista **Folder view** cal crear els directoris definits a l'estructura de directoris del projecte

<p align="center" width="100%"><img width="418" height="379" alt="captura" src="https://github.com/user-attachments/assets/732b8c31-378c-484c-a211-23c5e1ca8884" /></p>

## 4: Crear els arxius basics
Els projectes de DLL exportables amb api opaca necessiten un wrapper per exportar els components de forma compatible. Aquests arxius base son:

- arrel/include/Opaque.h és la macro d'exportació estàndar
- arrel/include/Opaque.hpp és la capçalera del wrapper
- arrel/src/api/Opaque_c_api.cpp


