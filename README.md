# Cafena

Un proiect  destinat gestionarii unei retele de cafenele din Romania. Acest sistem permite managementul eficient al angajatilor, stocurilor, comenzilor, evenimentelor speciale si generarea de rapoarte financiare.

## Functionalitati

1. **Gestionarea angajatilor**
   - Adaugare si stergere angajati (Manager, Ospatar, Barista).
   - Gestionarea turelor de lucru.

2. **Gestionarea stocurilor si produselor**
   - Adaugare, actualizare si stergere produse din stoc.
   - Calcularea profitului zilnic pe baza costului produselor si veniturilor generate.

3. **Gestionarea comenzilor**
   - Adaugare comenzi si calcularea pretului total.
   - Aplicarea reducerilor pentru clienti fideli (10% pentru 10 comenzi, 20% pentru 30 comenzi).

4. **Planificarea evenimentelor speciale**
   - Adaugarea si stergerea evenimentelor speciale (ex: degustari de cafea, concerte live).
   - Salvarea si incarcarea evenimentelor din fisiere CSV.

5. **Rapoarte financiare**
   - Generarea de rapoarte zilnice care includ veniturile totale, costurile, salariile si profitul.

6. **Import si export CSV**
   - Gestionarea datelor prin fisiere CSV pentru angajati, produse, comenzi, evenimente si rapoarte financiare.

## Cerinte de sistem

- **Compilator**: G++ (standard C++17 sau mai recent).
- **Sisteme de operare**: Windows, macOS, Linux.

## Structura proiectului

- **src/**: Contine fisierele sursa C++ (.cpp).
- **include/**: Contine fisierele header (.h).
- **data/**: Contine fisierele CSV utilizate pentru stocarea datelor (Produse.csv, Comenzi.csv, Angajati.csv, Evenimente.csv).
- **bin/**: Director pentru fisierele binare rezultate in urma compilarii.

## Instalare si utilizare

1. Cloneaza proiectul de pe GitHub:
   ```bash
   git clone https://github.com/TIBz0/Cafenea
   cd Cafenea
   ```

2. Compileaza proiectul utilizand G++:
   ```bash
   g++ -std=c++17 -o Cafenea src/*.cpp
   ```

3. Ruleaza aplicatia:
   ```bash
   ./Cafenea
   ```

## Fisiere CSV utilizate

- **Produse.csv**: 
  - Format: `Nume,Pret,Cantitate`
- **Angajati.csv**: 
  - Format: `Nume,Functie,OraInceput,OraSfarsit`
- **Comenzi.csv**: 
  - Format: `ClientID,Produse,Total,Data`
- **Evenimente.csv**: 
  - Format: `Nume,Cost`

## Exemple de utilizare

1. **Adaugare produs nou**:
   - Introducerea detaliilor produsului (`Nume`, `Pret`, `Cantitate`).
   - Produsul va aparea in `Produse.csv`.

2. **Adaugare comanda**:
   - Selectarea clientului existent sau adaugarea unui client nou.
   - Alegerea produselor si aplicarea reducerilor (daca este cazul).

3. **Stergere eveniment**:
   - Introducerea numelui evenimentului care trebuie eliminat.
   - Evenimentul va fi sters din `Evenimente.csv`.

## Principii OOP utilizate

- **Encapsulare**: Toate clasele utilizeaza metode getter/setter pentru a controla accesul la atribute.
- **Mostenire**: Clase precum `Manager`, `Ospatar` si `Barista` mostenesc clasa de baza `Angajat`.
- **Polimorfism**: Implementat pentru metode precum gestionarea comenzilor.
- **Abstractizare**: Clase abstracte utilizate pentru a defini structura generala a sistemului.

## Autori
- **Nume**: Tibi
- **Universitate**: Facultatea de Automatica si Calculatoare, Romania

## Licenta
Acest proiect este licentiat sub [MIT License](LICENSE).

## Contributii
Contributiile sunt binevenite! Pentru a contribui:
1. Creeaza un fork al proiectului.
2. Creeaza o ramura noua pentru modificarile tale.
3. Trimite un pull request.
