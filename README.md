# Proiect POO - Minesweeper în C++

Acesta este un joc de Minesweeper jucat în consolă, creat pentru a pune în practică conceptele de Programare Orientată pe Obiect (POO). 

## Noutăți Tema 3 (Programare Generică & Design Patterns)

* **Programare Generică (Templates):** Clasa `Jucator` a fost transformată într-un șablon (`template <typename T>`) pentru a oferi flexibilitate la măsurarea și afișarea timpului (ex: `int` pentru secunde întregi, `float` pentru zecimale). Aceasta include atribute dependente de `T` (`timpUltimulJoc`, `recordGlobal`), metode adaptate (`terminaJoc()`) și o funcție `friend template` pentru supraîncărcarea `operator<<`.
* **Simple Factory Pattern:** Am creat clasa `CelulaFactory` pentru a centraliza instanțierea claselor derivate (`CelulaMina`, `CelulaGoala`, `CelulaNumar`). Folosind un `enum class` pentru siguranța tipurilor, am decuplat clasa `Tabla` de crearea directă a obiectelor, respectând principiul Single Responsibility.
* **Singleton Pattern:** Am implementat clasa `LoggerJoc` folosind abordarea Meyers' Singleton. Aceasta oferă un punct global și unic de acces pentru jurnalizarea evenimentelor și a erorilor din sistem, separând logica de fundal de afișările din interfața utilizatorului (UI).
* **Prototype Pattern:** Baza acestuia exista deja prin metoda virtuală `clone()`. Este folosit pentru a realiza corect *deep copy-ul* polimorfic în constructorul de copiere al tablei, permițând duplicarea celulelor fără a le ști tipul exact la compilare și fără a încălca principiul Open/Closed.

## Concepte implementate din baremurile anterioare

* **Moștenire și Polimorfism:** Am creat o clasă de bază `Celula` din care derivă `CelulaMina`, `CelulaNumar` și `CelulaGoala`. Am folosit metoda NVI (Non-Virtual Interface) pentru funcția `dezvaluie()`. Polimorfismul dictează ce se întâmplă pe tablă, fără să fiu nevoit să folosesc `dynamic_cast` masiv pentru a verifica pe ce am dat click.
* **Gestiunea memoriei:** Tabla este salvată într-un `std::vector` care conține pointeri inteligenți (`std::shared_ptr<Celula>`). Asta înseamnă zero memory leaks fără să am nevoie de un destructor manual cu `delete`.
* **Copy-and-Swap:** Pentru a putea copia tabla corect, am suprascris constructorul de copiere și operatorul `=`, folosind idiom-ul copy-and-swap.
* **Excepții Custom:** Am o ierarhie proprie derivată din `std::exception` cu 3 erori specifice (ex: coordonate greșite, mutări ilegale). Input-ul de la jucător este citit super sigur cu `std::stringstream` și pus într-un `try-catch`, așa că programul nu va crăpa niciodată dacă scrii litere în loc de numere.
* **Variabile Statice & Cronometru:** Clasa `Jucator` reține un record global de timp (folosind `<chrono>`) și numărul de jocuri jucate prin atribute și metode `static`.

## Cum se joacă

Când rulezi jocul, introduci un rând, o coloană și litera corespunzătoare acțiunii, despărțite prin spațiu.

**Acțiuni:**
* `D` (sau d) -> Dezvăluie celula
* `M` (sau m) -> Pune/Scoate un steag (dacă crezi că e mină acolo)

**Exemplu:**
* `2 3 D` -> descoperă căsuța de la rândul 2, coloana 3.
* `0 1 M` -> pune un steag pe rândul 0, coloana 1.

Dacă dai click pe un spațiu gol (fără mine în jur), jocul va dezvălui automat toate celulele sigure vecine (cascadă / flood fill). La finalul jocului, poți vedea statisticile și poți alege să mai joci o rundă.

## Bibliografie
* https://www.youtube.com/watch?v=kjogmOXkipw - pentru algoritmul de random
* https://cplusplus.com/reference/random/ - documentație random
* https://www.youtube.com/watch?v=myGrhTNUAPY&t=102s - pentru ideea de vector 1D și algoritmi de generare a tablei
* https://www.youtube.com/watch?v=QYaQStudgnE - pentru biblioteca chrono
* https://refactoring.guru/design-patterns/cpp - documentație design patterns
