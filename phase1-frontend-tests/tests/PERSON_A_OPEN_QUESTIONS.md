# Person A — Open Questions (missing wording, tests skipped)

Rule used: exact prompt and error wording from Phase1_Step1_Shared_Foundation.pdf only, word for word. If a case needs wording that is not in that PDF, no test is written until you decide the wording.

## 1. Invalid user type on create — SKIPPED, no test written
- Handout requires create to ask for user type (admin or full-standard, buy-standard, sell-standard) but gives no error message for a bad type.
- Foundation PDF gives the prompt `Enter user type (AA, FS, BS, SS):` but lists no `ERROR:` line for an illegal type (e.g. `XX`, `A`, `aa`, empty line).
- Coverage asks for invalid user type, but there is no agreed wording to expect. Options need your decision, e.g. what the program should print for `create` + new valid name + type `XX`.
- No folder was created for this case. Once you pick wording, add one test: admin creates a fresh name with a bad type, expect that error, no user-type retry, failed transaction never written to the daily file.

## 2. Not skipped, but needs your confirmation (wording exists, meaning assumed)
- These are documented in PERSON_A_REQUIREMENTS_PROBLEMS.md, not here, because the wording exists and tests were written on a stated assumption:
  - permission checked before any follow-up prompts (create_as_nonadmin, delete_as_nonadmin, permission_sell_as_buystandard, permission_buy_as_sellstandard);
  - `Login` wrong case and empty transaction line expect `ERROR: invalid transaction` (invalid_wrong_case, invalid_empty_line);
  - login with over-15-char unknown name would expect `ERROR: no such user` (too-long rule is create-only in the PDF) — no separate test written; login_case_mismatch shows the pattern.
- Tell me if you want different wording or different prompt order and I will update the affected tests.
