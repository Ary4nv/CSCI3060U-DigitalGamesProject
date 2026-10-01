This folder is filled by `scripts/run_all.sh`. We do not edit the run folders by hand.

Each run creates `run_<date>_<time>` with:
- `summary.txt` - PASS/FAIL for every test
- `report.txt` - totals and failed tests
- `details/` - actual output, diffs, exit code, and stderr

`results/latest` points to the most recent run.

`compare_runs.sh` compares two saved `summary.txt` files so it is easier to notice if a change broke something that passed before.
