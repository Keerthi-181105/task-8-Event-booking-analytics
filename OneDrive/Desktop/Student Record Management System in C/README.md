# Student Record Management System in C

A menu-driven student record manager written in standard C. It uses a singly linked list with dynamic memory allocation and saves records to a text file.

## Features

- Add student records
- Display all records
- Search by student ID
- Update a record
- Delete a record
- Reject duplicate student IDs
- Save and load records from `students.txt`
- Free allocated memory before exiting

## Requirements

- Windows
- MSYS2 with the UCRT64 environment
- GCC

## Install GCC with MSYS2

1. Install MSYS2 from [msys2.org](https://www.msys2.org/).
2. Open **MSYS2 UCRT64** from the Windows Start menu.
3. Update the package database:

```bash
pacman -Syu
```

If MSYS2 asks you to close the terminal, close it, open **MSYS2 UCRT64** again, and run:

```bash
pacman -Su
```

4. Install GCC:

```bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc
```

## Compile and Run

Open **MSYS2 UCRT64**, navigate to the folder containing `main.c`, and run the compile command:

```bash
gcc -Wall -Wextra -pedantic -std=c11 main.c -o student_records.exe
```

If compilation succeeds, run the program:

```bash
./student_records.exe
```

Do not paste the `cd` and `gcc` commands together. The `cd` command must finish before the compile command is entered.

## Using the Program

Choose an option from the menu:

```text
1. Add student
2. Display all students
3. Search student
4. Update student
5. Delete student
6. Save records
0. Exit
```

For each student, enter:

- Student ID: an integer
- Name: one word
- Department: one word
- CGPA: a value from `0.0` to `10.0`

The program saves records automatically after adding, updating, deleting, and exiting. You can also choose option `6` to save manually.

## Data File

Records are stored in `students.txt` in the same folder as the executable. The file is created automatically when the program saves records. It is loaded automatically when the program starts.

Names and departments should not contain spaces because the file format uses whitespace-separated fields.

## Troubleshooting

### `gcc is not recognized`

Run the commands inside the **MSYS2 UCRT64** terminal, not a regular PowerShell window. If GCC works in MSYS2 but not PowerShell, that is expected unless `C:\msys64\ucrt64\bin` has been added to the Windows `PATH`.

### `cd: too many arguments`

Use quotes around the folder path and enter the command by itself:

```bash
cd "/c/Users/keert/OneDrive/Desktop/Student Record Management System in C"
```

### `student_records.exe is not recognized`

The executable does not exist until compilation succeeds. Compile first, then run:

```bash
gcc -Wall -Wextra -pedantic -std=c11 main.c -o student_records.exe
./student_records.exe
```
