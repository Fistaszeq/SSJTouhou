# SSJ Touhou

Bullet-hell shooter inspirowany **Touhou Project** oraz **Dragon Ball** (formy SSJ). Gra napisana w **C++** z użyciem biblioteki **SFML**.

---

## Gameplay

![Gameplay GIF](/gra_ssj1.png)

---

## Opis gry

SSJ Touhou to zręcznościowa gra typu bullet-hell, w której gracz steruje postacią poruszającą się po ekranie, unika przeszkód i eliminuje je za pomocą pocisków energetycznych. Wraz ze wzrostem wyniku odblokowywane są kolejne formy postaci, zwiększające obrażenia oraz maksymalną ilość energii KI.

---

## Główne mechaniki

* Kilka trybów strzelania przełączanych w trakcie gry
* System energii KI wykorzystywanej do ataku
* Możliwość ładowania KI kosztem punktów życia
* Transformacje postaci (Base, SSJ, SSJ Blue)
* Pasek życia gracza oraz przeciwników
* Przeciwnicy o losowej skali i ilości HP
* System punktów oraz licznik przebytego dystansu
* Prosty interfejs użytkownika

---

## Sterowanie

| Klawisz       | Akcja                       |
| ------------- | --------------------------- |
| W / A / S / D | Ruch gracza                 |
| Lewy Shift    | Wolniejszy, precyzyjny ruch |
| Spacja        | Strzelanie                  |
| F             | Ładowanie KI                |
| 1 / 2 / 3     | Zmiana trybu strzelania     |
| Q             | Wyjście z gry               |

---

## System form

| Forma    | Wymagany wynik | Obrażenia | Maks. KI |
| -------- | -------------- | --------- | -------- |
| Base     | 0              | 2         | 100      |
| SSJ      | 400            | 4         | 150      |
| SSJ Blue | 2500           | 6         | 225      |


---

## Wymagania

* Kompilator C++ obsługujący standard C++17 lub nowszy
* Biblioteka SFML (wersja 2.5 lub nowsza)
* System Windows lub Linux

---

## Kompilacja

### Linux (g++)

```bash
g++ main.cpp -o SSJTouhou \
-lsfml-graphics -lsfml-window -lsfml-system
```

---

## Zasoby

Projekt wymaga obecności plików graficznych oraz czcionki w katalogu głównym:

* tekstury tła i postaci (`.png`, `.jpg`)
* czcionka `Noserta.otf`

Przykładowa struktura projektu:

```
SSJTouhou/
├── main.cpp
├── background.png
├── bg_space.jpg
├── bg_water.jpeg
├── Goku-1.png.png
├── Goku-2.png.png
├── Goku-3.png.png
├── ki_blast_0.png
├── ki_blast_1.png
├── ki_blast_2.png
├── Noserta.otf
```

---

## Autorzy

* Kod: Fistaszeq
* Grafika: Iwa

---

## Status projektu

Projekt hobbystyczny / edukacyjny. Kod może zawierać uproszczenia i niedociągnięcia. Możliwa dalsza rozbudowa.


---

## Licencja

Projekt udostępniony w celach edukacyjnych i niekomercyjnych.
