# Proiect POO - Minesweeper în C++

Acesta este un joc de Minesweeper jucat în consolă, creat pentru a pune în practică conceptele de Programare Orientată pe Obiect (POO). 

## Concepte implementate din barem

* **Moștenire și Polimorfism:** Am creat o clasă de bază `Celula` din care derivă `CelulaMina`, `CelulaNumar` și `CelulaGoala`. Am folosit metoda NVI (Non-Virtual Interface) pentru funcția `dezvaluie()`. Polimorfismul dictează ce se întâmplă pe tablă, fără să fiu nevoit să folosesc `dynamic_cast` masiv pentru a verifica pe ce am dat click.
* **Gestiunea memoriei:** Tabla este salvată într-un `std::vector` care conține pointeri inteligenți (`std::shared_ptr<Celula>`). Asta înseamnă zero memory leaks fără să am nevoie de un destructor manual cu `delete`.
* **Copy-and-Swap & Prototype:** Pentru a putea copia tabla corect (deep copy), am suprascris constructorul de copiere și operatorul `=`, folosind idiom-ul copy-and-swap și funcții virtuale `clone()` în clasele derivate.
* **Excepții Custom:** Am o ierarhie proprie derivată din `std::exception` cu 3 erori specifice (ex: coordonate greșite, mutări ilegale). Input-ul de la jucător este citit super sigur cu `std::stringstream` și pus într-un `try-catch`, așa că programul nu va crăpa niciodată dacă scrii litere în loc de numere.
* **Variabile Statice & Cronometru:** Clasa `Jucator` reține un record global de timp (folosind `<chrono>`) și numărul de jocuri jucate prin atribute și metode `static`.

## Cum se joacă

Când rulezi jocul, introduci un rând, o coloană și litera corespunzătoare acțiunii, despărțite prin spațiu.

**Acțiuni:**
* `D` (sau d) -> Dezvăluie celula
* `M` (sau m) -> Pune/Scoate un steag (dacă crezi că e mină acolo)

**Exemplu:** `2 3 D` -> descoperă căsuța de la rândul 2, coloana 3.
`0 1 M` -> pune un steag pe rândul 0, coloana 1.

Dacă dai click pe un spațiu gol (fără mine în jur), jocul va dezvălui automat toate celulele sigure vecine (cascadă / flood fill). La finalul jocului, poți vedea statisticile și poți alege să mai joci o rundă.

Bibliografie:
https://www.youtube.com/watch?v=kjogmOXkipw - pt random
https://cplusplus.com/reference/random/ - pt random
https://www.youtube.com/watch?v=myGrhTNUAPY&t=102s- pt ideea de vector 1D si anumiti algoritmi de generare a tablei
https://www.youtube.com/watch?v=QYaQStudgnE - pt chrono
