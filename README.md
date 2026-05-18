# Std-Success Quiz App

Std-Success Quiz App is a C++ desktop application built with GTKMM 4. It provides a simple graphical quiz flow where users choose an available quiz, move through each question, and can later review the answers saved for completed quizzes.

Repository: https://github.com/codingburgas/std-success-quiz

## Current Process

The application starts from a GTK main window and loads the quiz data from the in-memory backend. The user starts from the main menu, opens an available quiz, answers each question through four buttons, and the application writes the chosen answer indexes to `progress.txt` after the quiz is finished.

Completed quizzes are excluded from the main quiz list. A completed quiz can be opened from the review screen to show each question next to the answer that was saved for it. The review screen also provides a restart action, which removes that quiz entry from `progress.txt` and makes the quiz available again.

## Technology Stack

| Area | Technology |
| --- | --- |
| Programming language | C++ |
| GUI framework | GTKMM 4 |
| Build system | Meson |
| Backend build tool | Ninja |
| Main source directory | `src/` |
| Header directory | `include/` |

## Project Structure

| Path | Purpose |
| --- | --- |
| `src/main.cpp` | Creates the GTK application and opens the main window. |
| `src/ui.cpp` | Builds the GTK interface and controls the quiz and review screens. |
| `src/quiz.cpp` | Provides the public quiz-facing functions used by the UI. |
| `src/backend.cpp` | Stores quiz data and reads/writes completed quiz progress. |
| `src/utils.cpp` | Contains small utility functions used by the interface. |
| `include/ui.h` | Declares the main GTK window class. |
| `include/quiz.h` | Declares quiz functions used by the interface layer. |
| `include/backend.h` | Declares backend data structures and persistence functions. |
| `include/utils.h` | Declares utility helpers. |
| `meson.build` | Defines the build configuration and source files. |
| `progress.txt` | Runtime progress file created/updated by the application. |

## Application Flow

1. Open the application.
2. Choose an available quiz from the main menu.
3. Press `Start quiz`.
4. Move through the quiz by pressing one of the four option buttons for each question.
5. When the quiz is finished, the selected option indexes are saved to `progress.txt`.
6. Open a completed quiz from the review screen to inspect the saved answers.
7. Press `Restart quiz` to remove the saved entry for that quiz and make it available again.

## Available Quiz Sets

The current backend contains these built-in quiz sets:

| Quiz |
| --- |
| Safety Basics |
| Protocol Quiz |
| Cyber Security |
| Office Rules |
| Computer Basics |
| Networking Fundamentals |
| First Aid |
| Environmental Awareness |
| Customer Service |
| General Knowledge |

## Dependencies

### Linux

Install GTKMM 4 development packages with your distribution package manager. Package names are commonly `gtkmm-4.0`, `gtkmm-4.0-dev`, or similar.

### Windows

Use MSYS2 and install the GTKMM dependencies. After building, `ldd` can help identify the DLL files required by the executable.

## Build Instructions

Configure the build directory:

```sh
meson setup build
```

Compile the project:

```sh
meson compile -C build
```

Run the application:

```sh
./build/quiz
```

## Development Notes

The quiz content is currently stored directly in `src/backend.cpp`. Progress is saved locally in `progress.txt`, so this file is runtime state and may change when the application is used.

When adding a new quiz, extend the `g_tests` list in `src/backend.cpp`, rebuild with Meson, and run the application again.

## Educational Focus

| Concept | How It Is Used |
| --- | --- |
| C++ functions | UI, quiz access, backend storage, and utility behavior are separated by source file. |
| Vectors | Quiz collections, question collections, and saved answer indexes use dynamic containers. |
| Arrays | Each question stores four option strings in a fixed-size array. |
| File streams | The backend persists completed quiz progress in a local text file. |
| GTK programming | GTKMM creates windows, lists, labels, entries, buttons, and layout containers. |
| Build systems | Meson defines the project and builds the executable. |
