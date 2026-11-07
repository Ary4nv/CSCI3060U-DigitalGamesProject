# CSCI 3060U - Fall 2026 - Phase 1 Front End tests

Team: ******\_\_\_\_****** Arian Vares ******\_\_\_\_****** Victor Ma ******\_\_\_\_******

## Files in this folder

- `tests/` has the actual test folders grouped by transaction
- `scripts/` has the small scripts we use to run and compare tests
- `results/` is where the scripts save each run
- `test_plan.md` explains how we set up the suite

A normal test folder has `input.txt`, `accounts.txt`, `games.txt`, `expected_terminal.txt`, and usually `expected_daily.txt`.

If a test is supposed to produce no daily transaction file, `expected_daily.txt` is left out completely. A few bad-file tests also leave out or intentionally break one of the starting files.

## Running it

Build the Front End first, then from the Phase 1 test folder run:

`FRONTEND=/path/to/frontend ./scripts/run_all.sh`

To run just one group, for example sell:

`FRONTEND=/path/to/frontend ./scripts/run_all.sh sell`

The newest run is linked at `results/latest/`. If something fails, the actual output and diffs are inside its `details` folder.

`./scripts/check_formats.sh` checks the fixed-width files used by the suite.

The Front End is run like this:

```text
frontend accounts.txt games.txt daily.txt < input.txt > terminal.txt
```

## How to run, step by step

1. Build the Phase 2 Front End: `cd phase2-frontend-prototype && make` (this makes the program `frontend`).
2. Go to this folder: `cd ../phase1-frontend-tests`.
3. Run all the tests: `FRONTEND=../phase2-frontend-prototype/frontend ./scripts/run_all.sh`
4. Run one group only: `FRONTEND=../phase2-frontend-prototype/frontend ./scripts/run_all.sh sell`
5. Look at `results/latest/`. Each failing test has its actual output and the diff in the `details` folder.

The Phase 1 scripts call the program with 3 file names (accounts, games, daily file). The Phase 3 folder has the newer scripts that use the 4 file name command line from the Phase 3 handout (`phase3-frontend-testing`).

## Work split (what each of us did)

There are 74 tests in total, 31 written by Victor and 43 by Arian. Each test folder is in `tests/<group>/<test>/`.

| | Victor Ma | Arian Vares |
|---|---|---|
| Test groups | `login` (8), `logout` (3), `create` (9), `delete` (6), `general` (5: permissions and invalid input) | `sell` (11), `buy` (8), `refund` (8), `addcredit` (7), `list` (5), `bad_files` (4) |
| Number of tests | 31 | 43 |
| Test table (every test and what it checks) | `tests/VICTOR_TEST_TABLE.md` | `tests/Arian_Vares_TEST_TABLE.md` |
| Requirements problems found | `tests/VICTOR_REQUIREMENTS_PROBLEMS.md` | `tests/Arian_Vares_REQUIREMENTS_PROBLEMS.md` |
| Open questions for the client | `tests/VICTOR_OPEN_QUESTIONS.md` | `tests/Arian_Vares_OPEN_QUESTIONS.md` |
| Review checklist | `tests/VICTOR_REVIEW_CHECKLIST.md` | `tests/Arian_Vares_REVIEW_CHECKLIST.md` |

The scripts in `scripts/`, `test_plan.md`, `requirements_decisions.md` and `HANDIN.md` are team files, and any test or setup that involves both sides is shared.

To see only one person's tests, run just their groups (see the steps above), for example `login` or `sell`.

All commits in the GitHub repository appear under one account due to a git configuration issue on Victor's end (his local identity was never set before pushing); actual contribution is documented in the per-person markdown files under tests/ and in the individual Group Feedback Forms submitted separately.
