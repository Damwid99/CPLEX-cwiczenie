### Projekt: Projekt dopasowania linii

#### Opis
Projekt ten skupia się na analizie danych i dopasowaniu modeli statystycznych do zbiorów danych, wykorzystując różne podejścia modelowania.

Opracowane na podstawie książki Williams, H. P. (2013). Model building in mathematical programming. John Wiley & Sons.

#### Struktura plików
- **data.dat**: Zawiera dane wejściowe wykorzystywane przez modele. Dane mogą zawierać informacje o wymiarach materiałów, kosztach itp.
- **model_1.mod**, **model_2.mod**, **model_3.mod**, **model_4.mod**: Pliki te zawierają różne modele optymalizacyjne. Każdy z nich może być skonfigurowany do rozwiązania specyficznych problemów w ramach projektu. Modele mogą się różnić parametrami lub metodami optymalizacji.
  - **model_1.mod**: Model minimalizujący sumę bezwzględnych odchyleń dla dopasowania liniowego.
    - **Dane wejściowe**: Zbiór punktów `data` składający się z współrzędnych x i y.
    - **Zmienna decyzyjna**: `a`, `b` (współczynniki prostej), `dev` (odchylenia dla każdego punktu).
    - **Cel**: Minimalizacja sumy bezwzględnych odchyleń `dev`.
    - **Ograniczenia**:
      ```opl
      forall(p in data)
        dev[p] >= p.y - (b * p.x + a);
      forall(p in data)
        dev[p] >= -p.y + (b * p.x + a);
      ```
  - **model_2.mod**: Model minimalizujący maksymalne odchylenie dla dopasowania liniowego.
    - **Dane wejściowe**: Zbiór punktów `data`.
    - **Zmienna decyzyjna**: `a`, `b` (współczynniki prostej), `dev` (odchylenia dla każdego punktu), `max_dev` (maksymalne odchylenie).
    - **Cel**: Minimalizacja maksymalnego odchylenia `max_dev`.
    - **Ograniczenia**:
      ```opl
      forall(p in data)
        max_dev >= p.y - (b * p.x + a);
      forall(p in data)
        max_dev >= -p.y + (b * p.x + a);
      ```
  - **model_3.mod**: Model minimalizujący sumę bezwzględnych odchyleń dla dopasowania krzywej kwadratowej.
    - **Dane wejściowe**: Zbiór punktów `data`.
    - **Zmienna decyzyjna**: `a`, `b`, `c` (współczynniki krzywej kwadratowej), `dev` (odchylenia dla każdego punktu).
    - **Cel**: Minimalizacja sumy bezwzględnych odchyleń `dev`.
    - **Ograniczenia**:
      ```opl
      forall(p in data)
        dev[p] >= p.y - (c * p.x * p.x + b * p.x + a);
      forall(p in data)
        dev[p] >= -p.y + (c * p.x * p.x + b * p.x + a);
      ```
  - **model_4.mod**: Model minimalizujący maksymalne odchylenie dla dopasowania krzywej kwadratowej.
    - **Dane wejściowe**: Zbiór punktów `data`.
    - **Zmienna decyzyjna**: `a`, `b`, `c` (współczynniki krzywej kwadratowej), `dev` (odchylenia dla każdego punktu), `max_dev` (maksymalne odchylenie).
    - **Cel**: Minimalizacja maksymalnego odchylenia `max_dev`.
    - **Ograniczenia**:
      ```opl
      forall(p in data)
        max_dev >= p.y - (c * p.x * p.x + b * p.x + a);
      forall(p in data)
        max_dev >= -p.y + (c * p.x * p.x + b * p.x + a);
      ```

- **line_fitting.cpp**: Plik źródłowy w języku C++, który inicjuje środowisko do uruchomienia modeli optymalizacji. Kod ten ładuje model (`model_1.mod`) oraz dane (`data.dat`), wykonuje modelowanie przy użyciu solvera CPLEX, i prezentuje wyniki. Obsługuje wyjątki i błędy podczas wykonywania, dając informacje zwrotne o stanie wykonania.

- **line_fitting.cpp**: Plik źródłowy w języku C++, który inicjuje środowisko do uruchomienia modeli optymalizacji. Kod ten ładuje model (`model_1.mod`) oraz dane (`data.dat`), wykonuje modelowanie przy użyciu solvera CPLEX, i prezentuje wyniki. Obsługuje wyjątki i błędy podczas wykonywania, dając informacje zwrotne o stanie wykonania. Aby uruchomić inny model niż `model_1.mod`, należy zmienić ścieżkę w linii kodu odpowiedzialnej za ładowanie modelu. Znajduje się ona w fragmencie:
  ```c++
  IloOplModelSource modelSource(env, "..\\cplex\\model_4.mod");
  ```
  Można zmienić `"model_1.mod"` na nazwę innego pliku modelu, na przykład `"model_2.mod"`, `"model_3.mod"` lub `"model_4.mod"`.
  

#### Wymagania
- CPLEX 22.1 Optimization Studio
- Visual Studio 22
- System operacyjny Windows 10 lub 11
