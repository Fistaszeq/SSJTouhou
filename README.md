# SSJTouhou

Lekkie, proste demo gry typu "Touhou-like" napisane w C++ i SFML.

## Opis
Sterujesz postacią (Goku) unikając spadających przeszkód i strzelając do nich. Zbierasz energię (ki), rozwijasz formy (SSJ) i zdobywasz punkty.

## Jak zbudować
Wymagania:
- Kompilator C++ (g++, clang++)
- SFML (graphics, window, system)

Przykład kompilacji:
```sh
g++ SSJTouhou.cpp -o SSJTouhou -lsfml-graphics -lsfml-window -lsfml-system
