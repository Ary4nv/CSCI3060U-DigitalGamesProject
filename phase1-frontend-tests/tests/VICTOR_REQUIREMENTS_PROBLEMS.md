# Victor Ma (Person A) — Requirements Problems (ambiguities, contradictions, gaps)

Each item says which test(s) cover the assumption. All wording below in backticks is copied from the foundation PDF or handout.

## 1. Games file line length: 49 vs 42 vs 48
- Handout header says `49 characters` lines, constraints say `every line is exactly 42 characters`, game-collection file also says 42. None matches the field math.
- Foundation 2.2 uses 48, which matches `25 + 1 + 15 + 1 + 6 = 48`. Fixtures use 48 and a length-check script verified every line.
- Covers: `fixtures/games.txt`, all tests that rely on shared games (none of Person A success paths depend on game content, but fixtures must still be valid).

## 2. END-line exact padding not spelled out
- Handout: file ends with special user `END` / special game `END` with other fields empty. It does not give the blank padding.
- Assumption used: username/game field left-justified and space-filled, type/price empty means spaces, so accounts END line is 28 chars and games END line is 48 chars.
- Covers: `fixtures/accounts.txt`, `fixtures/games.txt`.

## 3. games.txt in the PDF is missing a line break
- The copy-paste block joins `Quiet Nova Protocol ... 100.00` and `Paperclip Expedition ...` on one visual line.
- Fixed by splitting into two 48-char lines and verifying with a script.
- Covers: `fixtures/games.txt`.

## 4. No error wording for invalid user type on create
- Handout requires asking user type; foundation gives prompt `Enter user type (AA, FS, BS, SS):` but no `ERROR:` wording for a bad type.
- No test written for this; see VICTOR_OPEN_QUESTIONS.md.
- Would-be cover: none (skipped `create_invalid_usertype`).

## 5. Self-delete contradicts the handout
- Handout says delete username must not be the current user; Slack reportedly allowed it; foundation decides the session ends at once with an `02` line immediately followed by a `00` line using the same name/type/credit.
- Assumption for terminal: `User deleted.` then `Enter transaction:` with no typed logout (program waits for next login).
- Covers: `delete/delete_self_admin`.

## 6. Successful logout terminal ending
- Agreed messages are `Logout successful.` and `Enter transaction:` before every transaction word, but the PDF example only shows a refused logout.
- Assumption: after a good logout the program prints `Logout successful.` then `Enter transaction:` again (it still accepts a later login) instead of terminating.
- Covers: every success test ending in logout (`login_success_*`, `create_success*`, `delete_success`, `logout_after_logout`, `logout_blocks_until_login`, etc.).

## 7. Two sessions in one run share one daily file
- Handout says the daily file is written at logout listing every transaction in the session; it does not say what happens with login-logout-login-logout in one run.
- Assumption: the daily file reflects only the most recent session, overwritten at each logout (matches a fresh file write each time, not an accumulating log).
- Covers: `logout/logout_blocks_until_login` (expects `00 MoonlitKai...` only).

## 8. Permission check happens before follow-up prompts
- Foundation rule: at the first error print the error and return to `Enter transaction:` without asking further questions. It does not order privilege vs prompts.
- Assumption: privilege is checked first, so refused create/delete/sell/buy print `ERROR: not allowed for this account type` with no `Enter new username:` / `Enter username to delete:` / sell/buy prompts, and the unconsumed input lines are not present in input.txt.
- Covers: `create/create_as_nonadmin`, `delete/delete_as_nonadmin`, `general/permission_sell_as_buystandard`, `general/permission_buy_as_sellstandard`.

## 9. Unknown word vs `please login first` before login
- Both `ERROR: invalid transaction` and `ERROR: please login first` could apply to garbage typed while logged out. No precedence is given.
- Avoided by testing unknown/wrong-case/empty transaction words only while logged in; before-login test uses only known words (`create`, `delete`, `logout`).
- Covers: `login/transactions_before_login`, `general/invalid_unknown_word`, `general/invalid_wrong_case`, `general/invalid_empty_line`.

## 10. Usernames are case-sensitive
- Handout never states it; foundation decides game names are case-sensitive to match how usernames already work.
- Assumption: `quillfox9` does not match `QuillFox9`, so login gives `ERROR: no such user`.
- Covers: `login/login_case_mismatch`.

## 11. `username too long` is create-only
- Foundation lists `ERROR: username too long (max 15)` only for create. Login/delete with a long unknown name therefore use `ERROR: no such user` (login) or the invalid/nonexistent path (delete).
- Covers: `create/create_too_long`, `create/create_success_15char` (boundary 15 accepted), `login/login_case_mismatch` pattern.

## 12. Empty and END names mean `invalid username`
- Foundation maps `ERROR: invalid username` to empty or literally `END`. Applied to login, create, and delete username prompts.
- Covers: `login/login_empty_username`, `login/login_end_username`, `create/create_empty_username`, `create/create_end_username`, `delete/delete_empty_username`, `delete/delete_end_username`.

## 13. Failed transactions never reach the daily file
- Foundation states only completed transactions get a line. Every refusal test therefore expects the daily file to omit that transaction (or `the daily file is simply absent` when nobody ever logged in).
- Covers: all `*_too_long`, `*_duplicate*`, `*_empty*`, `*_end*`, `*_nonexistent`, `*_as_nonadmin`, `invalid_*`, `permission_*`, `login_unknown_user`, etc.

## 14. Second login does not ask for a username
- From the stop-at-first-error rule: `login` while logged in prints `ERROR: already logged in` at once.
- Covers: `login/login_second_login_refused`.

## 15. Duplicate includes users deleted this session
- Foundation states `ERROR: username already exists` includes someone deleted this session.
- Covers: `create/create_duplicate_existing`, `create/create_duplicate_deleted_this_session`.

## 16. Out of scope for Person A, left to partner
- sell/buy/refund/addcredit/list success and money rules, game-name uniqueness, credit limits, list ordering, collection file. Only two minimal permission refusals are included here to prove BS/SS restrictions without duplicating the partner suite.
- Covers: `general/permission_sell_as_buystandard`, `general/permission_buy_as_sellstandard`.
