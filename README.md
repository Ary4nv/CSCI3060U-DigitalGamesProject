# CSCI3060U-DigitalGamesProject

Digital Games Distribution System (like a small Steam). Front End in C++, Back End in Python, both console programs that only use text and text files. CSCI 3060U (Software Quality Assurance), Fall 2026.

Team: **Arian Vares** and **Victor Ma**

Project board: [Front End Tests Board](https://github.com/users/Ary4nv/projects/1/views/1)

## Folders

| Folder | What is in it | Phase |
|---|---|---|
| `phase1-frontend-tests/` | 74 requirements tests, test plan, scripts | 1 |
| `phase2-frontend-prototype/` | Front End prototype (C++11), design document | 2 |
| `phase3-frontend-testing/` | final Front End, 98 tests, test scripts, results of every run, failure log | 3 |
| `phase4-backend-prototype/` | not started | 4 |
| `phase5-backend-testing/` | not started | 5 |
| `phase6-integration-delivery/` | not started | 6 |
| `ai_history/` | the AI prompt history of each person, one folder per phase | all |

## Who did what

| Phase | Arian Vares | Victor Ma |
|---|---|---|
| **1 - Front End requirements tests** | 43 tests: `sell` (11), `buy` (8), `refund` (8), `addcredit` (7), `list` (5), `bad_files` (4). His own test table, requirements problems, open questions and review checklist (`tests/Arian_Vares_*.md`). | 31 tests: `login` (8), `logout` (3), `create` (9), `delete` (6), `general` (5). His own test table, requirements problems, open questions and review checklist (`tests/VICTOR_*.md`). |
| | Team files: scripts, `test_plan.md`, `requirements_decisions.md`, `HANDIN.md`. | |
| **2 - Front End prototype** | `FrontEnd`, `TransactionFactory`, `Transaction`, `Session`, `RecordFile`, `AccountRegistry`, `GameCatalog`, `DailyTransactionLog`, and the login, sell, buy, refund and addcredit transactions. | `Constants.h`, `Messages.h`, `FieldFormat`, `Console`, `Account`, `Game`, the logout, create, delete, list and listaccounts transactions, `main.cpp` and the Makefile. |
| | Design document: team (the file split is in Section 8 of the document). | |
| **3 - Front End requirements testing** | The test scripts (`run_all_tests.sh`, `run_tests.sh`, `compare_daily.sh`, `compare_terminal.sh`, `compare_runs.sh`), the 4 file name command line (`main.cpp`, `Session`), the Makefile and program name, runs 1, 2, 6, 7 and 8, the overflow fix and tests (F18), the exit code check in `run_all_tests.sh` (H2), the Slack questions to the client, the failure log, the README files. | Fixed the wrong create test, wrote the 21 new tests (15 `search`, 6 `listaccounts`), wrote `SearchTransaction` and its changes in `Constants.h`, `Messages.h` and `TransactionFactory.cpp`, runs 3, 4 and 5 (on Windows with Git Bash). |
| **4 - Back End prototype** | not started | not started |
| **5 - Back End unit testing** | not started | not started |
| **6 - Integration and delivery** | not started | not started |

Each of us hands in our own AI history for every phase (see `ai_history/`), and each of us fills in the Group Feedback Form. Commits in Phase 1 show under one account because Victor's git identity was not set at the time (his commits show under his own name from Phase 2 on).

## How to build and run

### Phase 1 tests (against the Phase 2 program)

    cd phase2-frontend-prototype && make
    cd ../phase1-frontend-tests
    FRONTEND=../phase2-frontend-prototype/frontend ./scripts/run_all.sh

Add a group name to run only that group, for example `./scripts/run_all.sh sell`. Results are in `results/latest/`. More in `phase1-frontend-tests/README.md`.

### Phase 2 program

    cd phase2-frontend-prototype
    make
    ./frontend accounts.txt games.txt daily.txt < input.txt

The design document is `phase2-frontend-prototype/doc/Phase2_Design_Document.pdf`.

### Phase 3 (final Front End and all tests)

    cd phase3-frontend-testing
    make
    ./distribution-system currentaccounts.txt availablegames.txt gamescollection.txt transout.atf < input.txt
    ./scripts/run_all_tests.sh

On Windows use Git Bash or WSL (`make` has to work in that shell, see the Phase 3 README). `run_all_tests.sh` builds the program, runs all 98 tests, checks the daily files and the terminal output, and saves everything in a new `results/run_NN` folder. The failure log is `phase3-frontend-testing/doc/Phase3_Failure_Log.pdf` and the details are in `phase3-frontend-testing/README.md`.

Needs g++ with C++11 and bash.
