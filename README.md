# Student Grade Manager - C

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Area](https://img.shields.io/badge/Area-Memory_Management-orange.svg)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A command-line interface (CLI) application developed in C to manage student records, academic disciplines, and grades. This project demonstrates core Computer Science concepts such as dynamic memory allocation (`malloc`/`realloc`), pointer manipulation, recursion, and binary file handling for data persistence.



## 📋 Features

- **Dynamic Data Management**: Uses `realloc` to dynamically resize arrays of students, disciplines, and grades as data is added.
- **Data Persistence**: Automatically saves and loads the database using a binary file (`arquivoBinario`), ensuring data is kept between executions.
- **Recursive Search**: Implements recursive algorithms to search for Student IDs (Matrícula) and Discipline Codes.
- **Weighted Grades**: Supports multiple grades per discipline with custom weights for calculating the final average.
- **Academic Reports**: Generates a bulletin showing the student's performance across enrolled disciplines.



## 🛠️ Tech Stack

- **Language**: C (Standard Library)
- **Concepts**: Structs, Pointers (single and double), Recursion, File I/O (Binary), Dynamic Memory Management.



## 🚀 Getting Started

Follow these steps to get a copy of the project up and running on your local machine.


### Prerequisites

You need a C compiler installed on your system to build the source code.

* **Windows**: MinGW.
* **Linux/macOS**: GCC.


### Installation & Execution

1. **Clone the repository**
```bash
git clone https://github.com/vitor-rodovalho/c-student-grade-manager-cli.git
cd c-student-grade-manager-cli
```


2. **Compile the code**
```bash
gcc student_grade_manager.c -o grade_manager

```


3. **Run the application**
    * **Windows:**
        ```bash
        grade_manager.exe
        ```
    
    * **Linux / macOS:**
        ```bash
        ./grade_manager
        ```



## 📖 Usage Guide

To ensure data integrity, follow this logical flow when populating the database for the first time:

1. **Register Disciplines**: Option `1` in the menu. Create the subjects first.
2. **Register Students**: Option `2`. When adding a student, the system will immediately ask to link them to existing disciplines and insert grades.
3. **Search/View Data**: Use Option `3` to search for a student. Once found, you can view their report card (Bulletin) or add more grades.


### Menu Options

1. **Add new discipline**: Register a subject name and code.
2. **Add new student**: Register a student and input their initial grades.
3. **Search student**: Find a student by ID to view report or add grades.
4. **Search discipline**: Find a discipline by its code.
5. **Delete student**: Remove a student record from memory.
6. **Save & Exit**: Persist all data to `arquivoBinario` and close the program.



## 📝 Note

This project was developed as a coursework assignment during the first semester of the Computer Science degree. It serves as a study on low-level memory management and algorithmic logic in C.


---

## ⚠️ Language Note

Please note that the code comments are currently in **Portuguese**, as this project was originally developed for a university assignment.

## ✒️ Author

Developed by **Vitor Hugo Rodovalho**.

---

## 📜 License

MIT License.

