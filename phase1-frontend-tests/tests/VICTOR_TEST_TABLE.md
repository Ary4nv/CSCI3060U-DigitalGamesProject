# Victor Ma (Person A) — Test Table (login/logout, create, delete, permissions, invalid input)

Scope: Person A only. No sell, buy, refund, addcredit, or list tests except two minimal permission refusals (BS cannot sell, SS cannot buy). Fixtures: `fixtures/accounts.txt` (28 chars/line), `fixtures/games.txt` (48 chars/line).

| Folder | What it tests |
|---|---|
| login/login_success_admin | Admin QuillFox9 can log in and log out; daily gets one 00 line |
| login/login_success_standard | Full-standard MoonlitKai can log in and log out; daily gets one 00 line |
| login/login_unknown_user | Unknown GhostAccount99 refused; next logout refused because never logged in; no daily file |
| login/login_empty_username | Empty username on login refused as invalid username; no session so no daily file |
| login/login_end_username | Username END on login refused as invalid username; no daily file |
| login/login_second_login_refused | Second login while logged in refused without asking username; only logout writes daily |
| login/login_case_mismatch | Lowercase quillfox9 refused as no such user (case-sensitive); no daily file |
| login/transactions_before_login | Create, delete, logout before login each refused with please login first; only later login writes daily |
| logout/logout_not_logged_in | Logout with nobody logged in refused; no daily file |
| logout/logout_after_logout | Logout after a good logout refused; daily keeps only the first 00 line |
| logout/logout_blocks_until_login | After logout, create refused; new login starts second session; daily holds two 00 lines in order |
| create/create_success | Admin creates NewTester FS; daily gets 01 (zero credit) then 00 |
| create/create_success_15char | Exactly-15-char FifteenCharUser accepted (boundary); daily 01 then 00 |
| create/create_too_long | 16-char SixteenCharUser1 refused as username too long; user type never asked; not written |
| create/create_duplicate_existing | Existing MoonlitKai refused as username already exists; user type never asked; not written |
| create/create_duplicate_deleted_this_session | Nimbus2 deleted then re-created in same session still refused as already exists; only 02 and 00 written |
| create/create_empty_username | Empty new username refused as invalid username; user type never asked; not written |
| create/create_end_username | New username END refused as invalid username; user type never asked; not written |
| create/create_as_nonadmin | Full-standard MoonlitKai cannot create; refused before any prompt; not written |
| delete/delete_success | Admin deletes Nimbus2; daily gets 02 with their credit then 00 |
| delete/delete_nonexistent | Delete of GhostAccount99 refused as no such user; not written |
| delete/delete_empty_username | Delete with empty username refused as invalid username; not written |
| delete/delete_end_username | Delete with END refused as invalid username; not written |
| delete/delete_as_nonadmin | Full-standard MoonlitKai cannot delete; refused before any prompt; not written |
| delete/delete_self_admin | Admin deletes self QuillFox9; session ends at once; daily gets 02 then 00 with no typed logout |
| general/invalid_unknown_word | Unknown word frobnicate while logged in refused as invalid transaction; not written |
| general/invalid_wrong_case | Word Login with wrong case refused as invalid transaction (case-sensitive); not written |
| general/invalid_empty_line | Blank line as transaction while logged in refused as invalid transaction; not written |
| general/permission_sell_as_buystandard | Buy-standard Thistledown7 cannot sell; refused before sell prompts; not written |
| general/permission_buy_as_sellstandard | Sell-standard CraterJax cannot buy; refused before buy prompts; not written |

Skipped (see VICTOR_OPEN_QUESTIONS.md): create with invalid user type — no error wording in the foundation PDF, so no test written.
