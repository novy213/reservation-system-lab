# System rezerwacji

Konsolowy program do obslugi klientow, pokoi i rezerwacji. Dane mozna zapisac do pliku `stan_aplikacji.txt` i pozniej wczytac.

## Kompilacja i uruchomienie

W katalogu projektu wykonaj:

```bash
g++ -std=c++11 main.cpp Entity.cpp Client.cpp ClientList.cpp Room.cpp RoomList.cpp DateTime.cpp -o rezerwacje
./rezerwacje
```

## Przykladowe uzycie

1. Wybierz `1`, aby dodac klienta.
2. Wybierz `3`, aby dodac pokoj.
3. Wybierz `6`, podaj ID klienta, numer pokoju i daty pobytu.
4. Wybierz `10`, aby pokazac rezerwacje klienta.
5. Wybierz `8`, aby zapisac dane; przy kolejnym uruchomieniu wybierz `9`, aby je wczytac.

Daty wpisuj w formacie `rrrr-mm-dd`. Opcje `11` i `12` edytuja lub usuwaja klienta, a `13` i `14` edytuja lub usuwaja pokoj. Klienta ani pokoju z rezerwacjami nie mozna usunac.

## Architektura

- `Entity` jest abstrakcyjna klasa bazowa z identyfikatorem i wirtualna metoda `show`.
- `Client` i `Room` dziedzicza po `Entity` i nadpisuja `show`.
- `ClientList` i `RoomList` przechowuja obiekty i udostepniaja operacje dodawania, wyszukiwania, edycji oraz usuwania.
- `DateTime` sprawdza poprawny format i dzien kalendarzowy. Przeciazone operatory `<`, `==` i `<<` ulatwiaja porownywanie i wyswietlanie dat.

Diagram klas znajduje sie w [UML.md](UML.md).

## Plik stanu

Plik tekstowy zawiera po kolei liczbe klientow i ich dane, liczbe pokoi i ich dane, a nastepnie liczbe rezerwacji. Rezerwacja przechowuje numer pokoju, ID klienta oraz date przyjazdu i wyjazdu.
