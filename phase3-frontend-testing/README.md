# Phase 3 - Front End Requirements Testing

Everything for Phase 3 is in this folder, so it can be zipped and run on its own.
The Phase 2 folder is left as we handed it in. The final Front End source is the
copy in `src/` here (it is the Phase 2 code plus the Phase 3 fixes in the failure log).

## Folder layout

| Path | What is in it |
|---|---|
| `src/` | Front End source (`.cpp` and `.h`) |
| `Makefile` | builds the program `distribution-system` |
| `tests/<group>/<test>/` | one folder per test (see below) |
| `tests/fixtures/` | shared `accounts.txt`, `games.txt` and `gamescollection.txt` |
| `scripts/` | the shell scripts that run the tests and check the results |
| `results/run_NN_.../` | saved results of every test suite run (used for the failure log) |
| `doc/` | the failure log document |

Handout steps 1 to 3 (inputs, expected outputs, outputs): each test folder holds its
own input and expected files, and the actual outputs of a run are saved in
`results/run_NN_.../outputs/`.

| File in a test folder | Meaning |
|---|---|
| `input.txt` | what is typed into the program (standard input) |
| `accounts.txt`, `games.txt` | the current accounts and available games files for that test |
| `gamescollection.txt` | optional, if it is missing the shared one in `tests/fixtures` is used |
| `expected_terminal.txt` | what should be printed on the terminal |
| `expected_daily.txt` | what the daily transaction file should contain (no file = no daily file expected) |
| `description.txt` | what the test checks (some tests only have it in the test tables in `tests/`) |

Output files of one test called `sell_successful_sell` in a run folder:
`.out` terminal output, `.atf` daily transaction file, `.err` standard error, `.code` exit code,
`.daily.diff` and `.terminal.diff` only if that check failed.

## How to build and run the program

    cd phase3-frontend-testing
    make
    ./distribution-system currentaccounts.txt availablegames.txt gamescollection.txt transout.atf < input.txt

The four file names come from the command line, the transactions come from standard
input and everything printed goes to standard output. Needs g++ with C++11.
On Windows (Git Bash) use `mingw32-make` instead of `make`; the rest is the same.

The program is called `distribution-system` like in the handout. The games collection file
is accepted but not opened: the Front End only writes the daily transaction file and the
Back End looks after the collection (so a refund taking the game out of a buyer's collection
cannot be tested in the Front End).

## How to run all the tests

    cd phase3-frontend-testing
    ./scripts/run_all_tests.sh

That builds the program if needed, runs every test, checks the daily files and the terminal
output, prints PASS/FAIL totals and saves everything in a new `results/run_NN` folder.
It exits with 0 if everything passed. To give a run a name: `./scripts/run_all_tests.sh my_label`.

| Script | What it does |
|---|---|
| `run_all_tests.sh` | does the whole thing below in one command and writes the summary |
| `run_tests.sh <outdir> [filter]` | handout step 5, runs the program on every test and saves terminal output and daily file |
| `compare_daily.sh <outdir> [filter]` | handout step 6, compares the daily files with `expected_daily.txt` |
| `compare_terminal.sh <outdir> [filter]` | handout step 6, compares the terminal output with `expected_terminal.txt` |
| `compare_runs.sh <old_run> <new_run>` | shows which tests were fixed or broken between two runs |
| `check_formats.sh` | checks line lengths of the fixture and expected daily files |

The scripts are bash scripts. They work on Linux and on the Mac. On Windows use WSL or Git Bash.
A filter is part of a test path, for example `./scripts/run_tests.sh /tmp/out search`.
`FRONTEND=/path/to/program` can be set to test another Front End.

## Decisions and assumptions (written down on purpose)

- Command line has 4 file names like the handout (accounts, games, games collection, daily file).
- A username deleted in a session can be created again in the same session (the client said yes on Slack).
  The Phase 1 test for this was wrong and was fixed in Phase 3.
- `listaccounts` is our name for the admin only "show all active accounts" transaction, not in the daily file. The client said on Slack (Nov 2) that there is no required name, so we kept it.
- `search` (Lab 3 update). The client said on Slack (Nov 2) that the command word, prompt, matching and output format are up to us, that every account type can use it, that it stays out of the daily file, and that our reading of the admin rule is right. So these are our choices:
  command word `search`, asks `Enter search text:` on the next line, case sensitive, text can be anywhere
  in the name, games are matched on game name only, users on username, every account type can use it,
  not written to the daily file, blank text gives `ERROR: invalid search text`, and an admin who is not
  selling a game is hidden from non admin users.
  Output looks like this (a heading only appears if that part has matches, `No matches found.` if nothing matches):

      Games found:
      Driftwood Signal Nine | ShadowLynxRider | 50.00
      Users found:
      Nimbus2 | FS

  Game lines are `name | seller | price`, user lines are `username | type` (no credit). All wording is in `src/Messages.h` and `src/Constants.h`.
- Games collection file: the client said on Slack (Nov 2) that she cannot say without knowing our design, and that reusing the data we already have instead of making more files is fine. We kept it as an argument that the program does not open.

## Who did what

- Arian Vares: the test scripts, the 4 file name command line (`main.cpp`, `Session`), the Makefile and program name, runs 1 and 2, the Slack questions, the failure log and the README files.
- Victor Ma: the fix for the wrong create test, the 21 new tests (15 search, 6 listaccounts), `SearchTransaction` and its changes in `Constants.h`, `Messages.h` and `TransactionFactory.cpp`, runs 3, 4 and 5 (on Windows with Git Bash).

Runs 1 and 2 were done on a Mac, runs 3 to 5 on Windows. The `.sh` scripts worked on both.

## AI use and sharing

Each of us hands in our own full AI history on Canvas. A copy of each is also kept in `ai_history/Phase 3/` at the top level of the GitHub repository (that folder is outside this zip).
We are happy for other students to see our Front End (bonus mark eligible).
