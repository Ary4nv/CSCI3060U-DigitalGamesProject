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

## Work split

- Victor Ma: login, logout, create, delete, permissions/invalid input
- Arian Vares: sell, buy, refund, addcredit, list, bad files
- Shared: tests or setup that involve both sides

All commits in the GitHub repository appear under one account due to a git configuration issue on Victor's end (his local identity was never set before pushing); actual contribution is documented in the per-person markdown files under tests/ and in the individual Group Feedback Forms submitted separately.
