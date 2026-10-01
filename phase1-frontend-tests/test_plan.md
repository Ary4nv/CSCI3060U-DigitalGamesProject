# Phase 1 test plan

## 1. Test folder setup

For us, one test is one folder.

`input.txt` is the terminal input. `accounts.txt` and `games.txt` are the files the Front End starts with. `expected_terminal.txt` is the terminal output we expect, and `expected_daily.txt` is the expected daily transaction file.

If the correct result is that no daily file should be made, that test just doesn't have an `expected_daily.txt`.

The scripts use `diff`, so the expected output has to match exactly.

## 2. How we split the work

We split the tests by transaction mostly so we weren't both editing the same folders.

- Victor Ma: login, logout, create, delete, permission/general invalid input
- Arian Vares: sell, buy, refund, addcredit, list, bad files
- Shared work can use transactions from both sides

For the number of tests, we followed the lab clarification: cover each different behavior instead of repeating basically the same failure many times just to pad the count. Each transaction has a normal case plus the failure cases we found. Important boundaries are checked on both sides when needed, e.g. 15/16 characters and 999.99/1000.00.

## 3. File widths we are using

We followed the field widths from the examples in the project documents.

Daily transaction line lengths:

| Code | Transaction | Length |
| ---- | ----------- | ------ |
| 00   | logout      | 31     |
| 01   | create      | 31     |
| 02   | delete      | 31     |
| 03   | sell        | 51     |
| 04   | buy         | 67     |
| 05   | refund      | 44     |
| 06   | addcredit   | 31     |

## 4. Failed transactions

If something goes wrong during a transaction, we stop that transaction right there, print the error, and go back to `Enter transaction:`. The program shouldn't keep asking later questions from the failed transaction.

Failed transactions are also left out of the daily transaction file.

## 5. Repo layout

The final repo layout is:

```text
phase1-frontend-tests/
|-- README.md
|-- test_plan.md
|-- scripts/
|   |-- run_test.sh
|   |-- run_all.sh
|   |-- compare_runs.sh
|   `-- check_formats.sh
|-- results/
|   `-- README.md
`-- tests/
    |-- login/
    |-- logout/
    |-- create/
    |-- delete/
    |-- general/
    |-- bad_files/
    |-- sell/
    |-- buy/
    |-- refund/
    |-- addcredit/
    `-- list/
```

The review package is split into `Victor Ma`, `Arian Vares`, and `shared` just to make it easier to see what's being updated. In Git, the transaction folders are merged into the single `tests/` folder above.

## 6. Running tests

Run everything:

`FRONTEND=/path/to/frontend ./scripts/run_all.sh`

Run one group:

`./scripts/run_all.sh sell`

Run one test:

`./scripts/run_test.sh tests/sell/successful_sell results/manual`

Check fixed-width files:

`./scripts/check_formats.sh`

A test gets 10 seconds. It fails on a crash, missing program, timeout, wrong terminal output, or wrong daily output.

## 7. Results

Each full run gets its own folder named something like `results/run_<date>_<time>`.

`summary.txt` has PASS/FAIL for each test. `report.txt` has the totals and failed tests. For a failed test, `details/` keeps the actual files, exit code, stderr, and diffs.

`results/latest` points to the newest run.

`compare_runs.sh` compares two saved summaries. We use it after changes to catch tests that used to pass and now fail.

## 8. Requirement choices

If a professor/client answer changes one of our assumptions, we'll update the affected tests and notes.

The main unresolved issue for Phase 1 is starting credit on `create`. One Slack answer said a new user starts at 0, while a later answer said the user enters starting credit. For Phase 1 we're using the 0-credit version since that was the original answer and our create tests were already built around it. We can update it later if the client confirms something different after the communication blackout.

## 9. GitHub

Phase 1 stays in its own folder in the main project repo. Victor Ma and Arian Vares tests are merged into the same `tests/` tree rather than kept as separate suites.
