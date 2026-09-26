<div align="center">

# ✈️ Flight Management System

A flight, airport, passenger and reservation data analysis system written in **C**.

![C](https://img.shields.io/badge/-C-A8B9CC?style=for-the-badge\&logo=c\&logoColor=white)
![Makefile](https://img.shields.io/badge/-Makefile-427819?style=for-the-badge\&logo=gnu\&logoColor=white)
![Doxygen](https://img.shields.io/badge/-Doxygen-2C4AA8?style=for-the-badge\&logo=doxygen\&logoColor=white)
![Valgrind](https://img.shields.io/badge/-Valgrind-orange?style=for-the-badge)

</div>

## 📖 About the Project

**Flight Management System** is a data analysis application developed in **C**.

The project processes information about flights, airports, aircraft, passengers and reservations stored in CSV files. The data is loaded and organized using custom data structures, allowing the user to perform different queries over the dataset.

The project focuses on modular programming, data validation, efficient data processing and careful memory management.

## ✈️ Data

The system works with several types of data:

| Entity          | Description                                                                                          |
| --------------- | ---------------------------------------------------------------------------------------------------- |
| ✈️ Flights      | Flight information, including departure, arrival, status, origin, destination, aircraft and airline. |
| 🛫 Airports     | Airport codes, names, cities, countries, coordinates and type.                                       |
| 🛩️ Aircraft    | Aircraft identification, manufacturer, model, year, capacity and range.                              |
| 👤 Passengers   | Passenger identification, name, date of birth, nationality and contact information.                  |
| 🎫 Reservations | Reservation information, flights, passengers, seats, prices and additional services.                 |

## 🔎 Available Queries

| Query | Description                                                                                |
| ----- | ------------------------------------------------------------------------------------------ |
| `Q1`  | Show the number of arrivals and departures for a given airport.                            |
| `Q2`  | Show the top N aircraft with the most flights, optionally filtered by manufacturer.        |
| `Q3`  | Find the airport with the most departures between two dates.                               |
| `Q4`  | Find the passenger who appears most often among the top 10 spenders during a given period. |
| `Q5`  | Show the top N airlines by average delay per flight.                                       |
| `Q6`  | Find the most common destination airport for passengers of a given nationality.            |

Queries support two different output formats:

* `;` separated output — default format.
* `=` separated output — available through the `<N>S` variant.

## 🚀 Executables

The project provides three different executables:

| Executable            | Description                                                                               |
| --------------------- | ----------------------------------------------------------------------------------------- |
| `programa-principal`  | Runs a list of queries from a command file against a dataset.                             |
| `programa-interativo` | Allows queries to be executed manually through an interactive terminal.                   |
| `programa-testes`     | Tests query results against expected results and reports execution time and memory usage. |

## ✅ Data Validation

The application validates the data before it is used by the queries.

Validation includes both **syntactic** and **logical** checks.

### 🔍 Syntactic Validation

The system validates information such as:

* Dates and timestamps.
* Email addresses.
* Coordinates.
* Identifiers.
* Enumerated values.
* Required fields and formats.

### 🧩 Logical Validation

The system also checks relationships between different entities.

For example:

* A flight cannot have the same origin and destination.
* Referenced aircraft must exist.
* Referenced passengers must exist.
* References between related entities must be valid.

Invalid records are excluded from query results and stored in:

```text
resultados/<entity>_errors.csv
```

## ⚙️ Compilation

The project uses a **Makefile** to automate compilation.

### 🔨 Compile the Project

```bash
make
```

### ▶️ Run the Main Program

```bash
./programa-principal <dataset_dir>/ <commands_file>
```

The generated query results are stored in the `resultados/` directory.

### 💻 Run the Interactive Program

```bash
./programa-interativo
```

### 🧪 Run the Tests

```bash
./programa-testes <dataset_dir>/ <commands_file> <expected_results_dir>/
```

### 🧹 Clean Generated Files

```bash
make clean
```

## 📚 Documentation

The project uses **Doxygen** to generate documentation for the source code.

To generate the documentation, use:

```bash
doxygen Doxyfile
```

## 🧪 Memory Analysis

The project uses **Valgrind** to detect memory leaks and analyze dynamic memory usage.

For example:

```bash
valgrind ./programa-principal <dataset_dir>/ <commands_file>
```

This allows memory allocation and deallocation to be checked during program execution.

## 🛠️ Technologies

* 🇨 — **C**
* 🔨 — **Makefile**
* 📚 — **Doxygen**
* 🧪 — **Valgrind**
* 🐞 — **GDB**
* 💻 — **Command-Line Interface (CLI)**

## 📁 Project Structure

```text
.

├── include/                  # Header files
├── src/                      # Source code
├── resultados/               # Query results and validation errors
├── resultados-esperados/     # Expected results for tests
├── Makefile                  # Build automation
├── Doxyfile                  # Doxygen configuration
├── relatorio-fase1.pdf       # Phase 1 report
├── relatorio-fase2.pdf       # Phase 2 report
└── README.md                 # Project documentation
```

## 🎯 Objective

The main objective of the project is to develop a system capable of efficiently processing and analyzing a large dataset containing flight-related information.

The project applies concepts such as **modular programming, data structures, file processing, data validation, query processing and dynamic memory management**.

---
