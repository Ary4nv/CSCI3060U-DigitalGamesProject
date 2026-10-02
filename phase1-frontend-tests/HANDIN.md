# Phase 1 Hand-in Checklist (Canvas)

Due Friday, October 2nd, 2026, 8:00pm. 71 requirements tests total:
login 8, logout 3, create 8, delete 6, general 5, sell 11, buy 8, refund 6,
addcredit 7, list 5, bad_files 4.

## Package contents

1. **Test tables (print to PDF):**
   - `tests/VICTOR_TEST_TABLE.md` — Victor Ma list (30 tests).
   - `tests/Arian_Vares_TEST_TABLE.md` — Arian Vares list (41 tests).
2. **Test files (zip of txt files):** every `tests/<group>/<test>/` folder:
   `input.txt`, `expected_terminal.txt`, `expected_daily.txt`
   (absent = no daily file expected), `description.txt`,
   plus per-test `accounts.txt`/`games.txt`.
   Zip exactly those `*.txt` files, preserving folder names.
3. **Test plan (print to PDF):** `test_plan.md` in this folder.
4. **AI history (mandatory, otherwise grade zero):** full prompt/response
   history if AI was used, else a written no-AI statement. Keep in
   `ai_history/` at the repo root; upload with the submission.

## Agreed expectations snapshot

- Wording is word-for-word from the shared foundation doc; first error in a
  transaction returns to `Enter transaction:` with no further prompts;
  failed transactions never reach the daily file.
- Daily file keeps the latest session only when one run holds two
  login/logout sessions (overwrite); no-login runs produce no daily file.
- `VICTOR_REQUIREMENTS_PROBLEMS.md` records ambiguities
  (42 vs 49/48 line length, END padding, self-delete `02`+`00`,
  permission-first, case-sensitivity) and which tests pin each one.
- `VICTOR_OPEN_QUESTIONS.md` records the skipped invalid-user-type test
  (no agreed error wording in the foundation doc).
- Verify before zipping: `./scripts/check_formats.sh` must pass.
