# Dangaus kūnų simuliacija

## Projekto tikslas: 

Galutinis projekto tikslas yra sukurti aplinką, kuri simuliuotų Saulės sistemos planetų judėjimą pasikliaudama fizikos formulėmis. Visa tai bus vizualiai perteikiama vartotojui, taip pat jam bus suteikiama galimybė manipuliuoti aplinką sukuriant įvairiausius hipotetinius scenarijus, pvz.:

- Kas būtų, jei Saulės masė akimirksniu padidėtų 100 kartų.
- Kas būtų, jei į Saulės orbitą staiga įskirstų milžiniškas asteroidas ir judėtų Žemės link.
- ir t.t.

## Pirmas etapas (2025.03.07)

Atlikdamas šią užduotį, sukūriau **klasę** Planet.cpp, kuri apibrėžia planetą su jai būdingais laukais ir metodais. 

### Klasės implementacija

✅ Implementavau **privalomus** bei **papildomus** laukus, užtikrindamas, kad bent vienas jų būtų privalomas.   
✅ Sukūriau **konstruktorius** bei **destruktorių**, kuris užtikrina, kad objektų skaitiklis būtų tinkamai atnaujinamas.    
✅ Kiekvienam planetos objektui automatiškai priskiriamas **unikalus ID**.  
✅ Įdiegiau **statinį lauką**, kuris seka šiuo metu egzistuojančių objektų skaičių.

### Klasės funkcionalumo demonstracija

Norėdamas pademonstruoti sukurtos klasės funkcionalumą, `main()` funkcijoje:

- Ištestavau kiekvieną metodą, kviesdamas jį bent po kartą.
- Sukūriau **statinių** bei **dinaminių** planetų objektų masyvus.
- Kviesdamas metodus, pavaizdavau **būsenų kaitą**.

Visi šie žingsniai leidžia išbandyti ir įvertinti mano sukurtos planetų simuliacijos veikimą.

### Programos paleidimas

Programa gali būti paleidžiama nuėjus į projekto katalogą su terminalu ir paleidus šias komandas:

```
make
./PlanetSimulation.exe
```
