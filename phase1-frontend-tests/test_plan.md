# Phase 1 Test Plan — Front End Requirements Tests

## 1. Organization

All requirements tests live under `phase1-frontend-tests/tests/`, one folder per
test, grouped by area:

- `login/`, `logout/`, `create/`, `delete/`, `general/` — Person A
  (login/logout, create, delete, permission checks, invalid input).
- `sell/`, `buy/`, `refund/`, `addcredit/`, `list/` — Person B.
- `bad_files/` — corrupt/missing fixture handling (missing file is intentional).
- `fixtures/` — the shared `accounts.txt` (28 chars/line) and `games.txt`
  (48 chars/line) both halves reuse. Every runnable test folder also carries
  its own identical copies, because the runner starts the program from inside
  the test folder.

Each test folder contains:

- `input.txt` — exactly what is typed (one line per entry).
- `expected_terminal.txt` — exactly what the program prints, including every
  `Enter transaction:` prompt. Wording is copied word for word from the shared
  foundation doc.
- `expected_daily.txt` — the expected daily transaction file. Omitted entirely
  when no login session ever starts (the program writes no daily file then);
  failed transactions never appear in it.
- `description.txt` — one line: what the test checks and why.
- `accounts.txt`, `games.txt` — the starting files for that run.

Per-test tables: `tests/PERSON_A_TEST_TABLE.md` (Person A hand-in list).

## 2. Pre-run format check

Before running anything:

```
./scripts/check_formats.sh
```

It verifies every `accounts.txt` line is 28 chars, every `games.txt` line is
48 chars, and every `expected_daily.txt` line matches its transaction code
length (`00/01/02/06` = 31, `03` = 51, `04` = 67, `05` = 44) and ends in `00`.
Intentionally corrupt fixtures under `bad_files/*corrupt*` are skipped.

## 3. Running

Build the Phase 2 Front End first (program takes
`accounts.txt games.txt daily_out` plus stdin), then from
`phase1-frontend-tests/`:

```
./scripts/run_all.sh                 # whole suite
./scripts/run_all.sh login           # one group only (name filter)
./scripts/run_test.sh tests/login/login_unknown_user results/manual
```

`run_test.sh` runs one test: it feeds `input.txt` to the program, saves the
real `terminal.txt`/`daily.txt` plus exit code, and diffs them against the
expected files (a written daily file with no `expected_daily.txt` is a fail).
`run_all.sh` runs every `tests/<group>/<test>/` folder, writes
`results/run_<timestamp>/summary.txt` (one `PASS`/`FAIL` line per test),
`details/` per-test outputs and diffs, and a `report.txt` with totals plus a
per-group breakdown. `results/latest` always points at the newest run.

## 4. Reporting and comparing

- Each run is self-contained under `results/run_<timestamp>/` and is never
  overwritten; keep them to show progress across Front End versions.
- To compare two runs (e.g. before/after a fix):

```
./scripts/compare_runs.sh results/run_<old> results/run_<new>
```

  It prints `REGRESSION` (PASS→FAIL), `FIXED` (FAIL→PASS), `CHANGED`, and
  `NEW TEST` lines plus old/new totals.
- Known design decisions baked into expectations (see
  `tests/PERSON_A_REQUIREMENTS_PROBLEMS.md`): permission is checked before
  follow-up prompts; a second `login` never asks for a username; usernames
  are case-sensitive; a username deleted this session still counts as taken;
  an admin self-delete ends the session (`02` then `00`); if one input run
  holds two login/logout sessions the daily file keeps the latest session
  (overwrite, not append).
