# 🤖 Robot u lavirintu u Knososu

Interaktivna tekstualna igra inspirisana grčkom mitologijom: pomoću specijalnih predmeta i strategije, igraj kao robot koji mora da pronađe izlaz iz lavirinta pre nego što ga sustigne Minotaur.

---

## 🔍 Opis projekta

Ovaj projekat je razvijen kao ispitna obaveza u okviru kursa **Objektno orijentisano programiranje 2** na Fakultetu tehničkih nauka u Novom Sadu. Cilj je bio dizajnirati i implementirati igru koja koristi napredne principe objektno-orijentisanog programiranja u jeziku C++.

---

## 🌐 Pravila i cilj igre

- Lavirint je matrica sastavljena od:

  - Zidova `#`
  - Prolaza `.`
  - Ulaza `E` i izlaza `X`
  - Robota `R` (igrač) i Minotaura `M` (neprijatelj)
  - Predmeta `?`

- Cilj: doći do izlaza pre nego što Minotaur ubije robota.

- Lavirint se generiše dinamički prilikom pokretanja programa.

---

## 🚀 Pokretanje igre

```
./robot_game <broj_redova> <broj_kolona> <broj_predmeta>
```

> Primer:
>
> ```bash
> ./robot_game 25 25 5
> ```

---

## ⌨️ Komande

| Taster | Akcija         |
| ------ | -------------- |
| `W`    | Pomeri se gore |
| `A`    | Levo           |
| `S`    | Dole           |
| `D`    | Desno          |
| `Q`    | Izlaz iz igre  |

---

## 🍒 Predmeti i efekti

Svi efekti traju **3 poteza**, osim ako nisu uništeni od strane Minotaura.

| Predmet        | Efekat                                           |
| -------------- | ------------------------------------------------ |
| 🗡️ Štit       | Blokira napad Minotaura, zamrzava ga na 2 poteza |
| ⚔️ Mač         | Ubija Minotaura ako ga robot napadne             |
| 🔨 Čekić       | Omogućava prolaz kroz zidove                     |
| 🌫️ Magla rata | Ograničava vidljivost na 3x3 matricu oko robota  |

---

## ✅ Završetak igre

Igra se završava kada:

- Robot stigne na izlaz
- Minotaur ubije robota
- Korisnik prekine igru (`Q`)

Po završetku, stanje igre se snima u `build/output.txt` sa opisom završetka i lavirintom.

---

## 📊 Struktura projekta

```
project/
├── main.cpp
├── game/
├── maze/
├── maze_generator/
├── item/
├── entity/
├── io/
├── utils/
├── common/
├── docs/
├── build/
└── CMakeLists.txt
```

- `item/`  — klase za efekte (mač, štit...)
- `maze_generator/` — generacija lavirinta pomoću backtracking algoritma
- `game/`  — logika toka igre (Game loop)
- `io/`    — upis/ispis i upravljanje fajlovima
- `entity/` — logika kretanja entiteta (robot, Minotaur)

---

## 📊 Performanse

- **Linearna zavisnost** vremena generacije od veličine lavirinta
- Algoritam koristi stack-based backtracking
- Za testiranje performansi generisanja postoji shell skripta unutar .benchmark/ foldera

---

## 🔧 Testiranje

- Validacija neispravnih argumenata
- Minimalne/maksimalne dozvoljene dimenzije
- Interakcije robot/Minotaur sa i bez predmeta
- Robusno ponašanje sistema pri svim ulazima

---

## 📝 Autor

- **Aleksa Ćurčić**
- Fakultet tehničkih nauka, Novi Sad
- Mentor: Dušan Stojković

---

## 📁 Output primer

```
# # # # # # # # # # # # # # # E # # 
# . # . . . . . . . . . . . . . # # 
# . # . # # . . . . # # # # # . # # 
# . . . # . . . . . # . . . . . # # 
# . # # # . # . # . # . # # # . # # 
# . # . . . # . # . # . # . . . # # 
# . # . . # # . # . # . . . . . # # 
# . # . . . . . . . # . . . # . # # 
# . # # # ? . . # . . . # . # . # # 
# . . . . . # . . . . . # . # . # # 
# # # . # . # # # . # . . . . . # # 
# . # . # . . . # . # . # . . . # # 
# . # . . . # . # # # . # . . . # # 
# ? # . . . # . . . . . # . . . # # 
# . # # # . . # # . # # # # # . # # 
# . . . . . . . . . . . . M . . # # 
# . . . . . . . . . . . . . . . . # 
# # # # # R # # # # # # # # # # # # 

GENERATION-TIME: 0.000005
```

---

Za više informacija pogledajte izvještaj u `docs/` folderu.

