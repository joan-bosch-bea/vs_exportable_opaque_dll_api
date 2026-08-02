# Exportació d'una DLL amb API opaca en Visual Studio

En aquest document pretenc descriure els passos per exportar una DLL amb API opaca en Visual Studio. Per simplificar l'exemple, el projecte implementa una única classe amb un únic mètode funcional, centrant l'atenció en l'arquitectura d'exportació de la DLL i no en la complexitat de la implementació.

## Descripció del projecte
Aquí posaré una petita descripció del que vol dir "exportar DLL amb API opaca" i la millora que aporta els fets de ser exportable i opaca.

* Compatibilitat binària (ABI): la representació de les classes C++ pot variar entre compiladors i versions
* Encapsulació: els usuaris no coneixen ni depenen de la implementació interna
* Compatibilitat entre llenguatges: una API C és fàcil d'utilitzar des de C, C#, Python(ctypes), Rust, etc...
* Evolució de la biblioteca: actualització / modificació de la llibreria privada sense canviar la interfície pública

## Exporting a DLL using an Opaque C API in Visual Studio

* This repository is documented in Catalan
* The source code, identifiers and public API are written in English
* Automatic translation tools should provide a good reading experience for non-Catalan speakers

## 1-. Creació del projecte
Obrir Visual Studio, seleccionar la creació d'un projecte Dinamic-Link Library (DLL) en C++ per a Windows, indicar el nom del projecte i crear:

<img width="1013" height="674" alt="captura" src="https://github.com/user-attachments/assets/b4ac6250-b7d6-4554-9b48-931794973c60" />


<img width="1013" height="674" alt="captura" src="https://github.com/user-attachments/assets/783ea31e-8a5e-4b20-a93d-a09d7f84d5dc" />

## 2-. Estructurar el projecte
Per facilitar la identificació dels components del projecte és sempre una bona pràctica estructurar el projecte de manera adequada. Una estructura correcta per un projecte de dll amb api opaca és situar els arxius de capçalera visibles pel client de la dll al directori "include" i els arxius amb la lògica al directori "src". Al seu torn, la lògica s'hauria d'organitzar en subdirectoris per a cada component. D'entrada el directori "src" tindrà dos subdirectoris: "src/api" contindrà el wrapper de tota la funcionalitat exportada, i "src/core" on hi haurà la classe principal. L'estructura de directoris per al projecte serà la següent:

- arrel/include (directori visible pel client)
- arrel/src/api (enllaç entre les classes de la llibreria i l'api en C)
- arrel/src/core (implementació privada de la llibreria)

## 3-. Crear l'arbre de directoris fisics
Des de l'explorador d'arxius o des de la vista **Folder view** cal crear els directoris definits a l'estructura de directoris del projecte

<p align="center" width="100%"><img width="418" height="379" alt="captura" src="https://github.com/user-attachments/assets/732b8c31-378c-484c-a211-23c5e1ca8884" /></p>

## 4-. Crear els arxius basics
Els projectes de DLL exportables amb api opaca necessiten un wrapper per exportar els components de forma compatible. Aquests arxius base son:

- arrel/include/Opaque.h (macro d'exportació estàndar)
- arrel/include/Opaque.hpp (capçalera del wrapper)
- arrel/src/api/Opaque_c_api.cpp (mètodes auxiliars del wrapper)
- arrel/src/core/Opaque.cpp (llibreria a exportar)
- arrel/src/core/Opaque.h (llibreria a exportar)

## 5-. Afegir arxius a la solució
Un cop creats l'arbre de directoris i els arxius físics cal afegir aquests arxius a la solució. Si per defecte s'han afegit a la solució pch i framework i se n'ha modificat (Tal com he fet en aquest projecte), caldrà eliminar-los de la solució i tornar-los a afegir:

<p align="center" width="100%"><img width="323" height="246" alt="captura" src="https://github.com/user-attachments/assets/b26db9a0-0907-46a0-b61a-68669b4ccfd1" /></p>

## 6-. Declarar macro d'exportació
EL precompilador de C++ ha de conèixer la macro d'exportació del projecte, per tant obro Project/Properties/C++/Preprocessor/Preprocessor Dfinitions i hi afegeixo la macro OPAQUELIB_EXPORTS que és la que he utilitzat al projecte:

<p align="center" width="100%"><img width="800" height="546" alt="captura" src="https://github.com/user-attachments/assets/25569fc8-716d-41cc-b02b-689a42f92e88" /></p>

## 7-. Configurar els precompiled headers (pch)
En aquest projecte no utilitzo pch. En cas que s'hagin creat per defecte durant la creació inicial del projecte elimino pch.h, pch.cpp i framework.h de la solució i després els elimino del disc. Des de Project/Properties/C++/Precompiled headers al camp _Precompiled Header_ seleccio l'opció _Not Using Precompiled Headers_. Finalment comprovo que cap arxiu intenta incloure pch.h.

## 8-. Declarar directoris d'inclusió addicional (opcional)
Opcionalment es poden declarar els directoris root/include i root/src com a directoris d'inclusió addicional per simplificar les rutes d'inclusió. En aquest projecte no ho aplico per a que es vegi clarament d'on s'inclou cada arxiu.

## 9-. Compilació del projecte
Executar la compilació del projecte.

## 10-. Testar el projecte
Per testar el projecte creo un nou projecte dins la mateixa solució (serà el projecte OpaqueTest). Per a que el test pugui enllaçar la dll del projecte cal accedir a Project/Properties/C++/General/Additional include directories i afegir la ruta al directori arrel/include. Després cal accedir al Project/Properties/Linker/General/Additional include libraries i afegir la ruta al directori de sortida (*.dll i *.lib) del projecte que es vol incloure; després cal indicar la llibreria a linkar, des de Project/Properties/Linker/Input al camp _Additional dependencies_ afegir el nom de l'arxiu de la llibreria exportada Opaque.lib

## 11-. Incloure instància d'Opaque al test
Incloure la llibreria exportada Opaque.h i utilitzar el handler per accedir a l'api exportada:
```
#include "Opaque.h"

int main() {
	OpaqueHandle *hOpaque = Opaque_Create();
	Opaque_Destroy(hOpaque);
}
```

## 12-. Exportar mètodes de la classe del projecte
Per fer una exportació compatible cal que els valors d'intercanvi siguin de tipus estàndar. Dins la classe del projecte declaro un mètode que accepta dos enters i retorna la seva suma:

```
//Opaque.h
#include <stdio.h>

class Opaque {
public:
    Opaque();
    int suma(int , int );

private:
};
```

```
//Opaque.cpp
#include "Opaque.h"

Opaque::Opaque() {
	printf("Hola des de Opaque");
}

int Opaque::suma(int a, int b) {
	return a + b;
}
```

Després declaro la signatura de la funció exportada al wrapper:
```
//arrel/include/Opaque.hpp
int suma(int a, int b) {
  return Opaque_Suma(handle, a, b); 
}
```

Amb la signatura declarada ja puc afegir la funció d'intercanvi:
```
//arrel/src/api/Opaque_c_api.cpp
OPAQUELIB_API int Opaque_Suma(OpaqueHandle *h, int a, int b) {
    return (h)? h->instance.suma(a, b) : 0;
}
```

I finalment ja puc declarar la crida a la capçalera exportada, la que cridarà el client de la dll:
```
//arrel/include/Opaque.h
OPAQUELIB_API int Opaque_Suma(OpaqueHandle *, int, int);
```
Des del test ja puc accedir a la funció suma:
```
int a = 123;
int b = 456;
int resultat;

OpaqueHandle *hOpaque = Opaque_Create();

resultat = Opaque_Suma(hOpaque, a, b);
printf("%d + %d = %d", a, b, resultat);

Opaque_Destroy(hOpaque);
```
