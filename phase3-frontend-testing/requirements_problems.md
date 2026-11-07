# Requirements problems and how we handled them

These are the places where the handout and the lab updates were unclear, missing or
contradicted each other (or the client). Each person also has their own longer list from
Phase 1 in `tests/Arian_Vares_REQUIREMENTS_PROBLEMS.md` and `tests/VICTOR_REQUIREMENTS_PROBLEMS.md`,
and the open questions we asked the client are in the `*_OPEN_QUESTIONS.md` files there.

| # | Problem in the requirements | What we did | Where it shows |
|---|---|---|---|
| 1 | Field lengths in the handout text do not match its examples (username, game name, credit, price) | Followed the examples: username 15, game name 25, credit 9 (including `.00`), price 6. Account lines are 28 characters, game lines 48 | `check_formats.sh`, the `sell` and `create` boundary tests |
| 2 | Slack answers contradicted each other on whether `create` asks for starting credit | Client confirmed 0.00 and no prompt | `create` tests |
| 3 | Can a deleted username be created again in the same session? Our Phase 1 test said no, the client said yes on Slack | The code follows the client, the test was wrong and was fixed | failure F2 in the failure log |
| 4 | No session limit for `addcredit` in the handout | We chose $1000 per account per session, the client said it applies to every `addcredit` (admin too) | `addcredit` tests |
| 5 | Max credit 999,999.99: does `.00` count inside the 9 characters? | Yes, it is inside the field. Anything that would go over is refused and not written to the daily file | `buy`, `refund`, `addcredit` tests |
| 6 | Lab 2 update (show all accounts) has no transaction name or output format | We use `listaccounts` (admin only, `username \| type \| credit`, not in the daily file). The client said there is no required name | `listaccounts` tests |
| 7 | Lab 3 update (`search`) has no command word, prompt or output format | Our choices are in `README.md` (case sensitive, games by game name, users by username, headings `Games found:` / `Users found:`, `No matches found.`, hidden non selling admins) and the client agreed that these are up to us | `search` tests |
| 8 | The Phase 3 command line has a games collection file but the Front End has no use for it | The program takes the file name and does not open it | failure F1, `README.md` |
| 9 | Things the client left to the team: loading the collection at login, whether a bought game leaves the storefront, gifting, deleting a user's data, list order, how to show permission errors, case sensitivity of game names | We picked the simplest option for each and wrote it down in `tests/*_OPEN_QUESTIONS.md` and `README.md` | various tests |
| 10 | Refund removes the game from the buyer's collection, but the Front End never gets that file | Not testable in the Front End, left for the Back End phases | `README.md` |
