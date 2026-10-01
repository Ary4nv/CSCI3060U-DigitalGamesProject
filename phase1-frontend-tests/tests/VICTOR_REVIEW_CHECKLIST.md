# Victor Ma (Person A) — Review Checklist (one sentence per test)

Read input.txt vs expected_terminal.txt vs expected_daily.txt for each folder and confirm the sentence holds.

- login/login_success_admin: QuillFox9 exists as AA so login succeeds and the logout 00 line carries 000500.00.
- login/login_success_standard: MoonlitKai exists as FS so login succeeds and the logout 00 line carries 000200.00.
- login/login_unknown_user: GhostAccount99 is not in accounts.txt so login gives no such user, the next logout gives please login first, and no daily file exists because nobody logged in.
- login/login_empty_username: Blank username is reserved as invalid username so login fails at once and no daily file exists.
- login/login_end_username: END is reserved as invalid username so login fails at once and no daily file exists.
- login/login_second_login_refused: Already logged in as QuillFox9 so the second login errors without an Enter username prompt and only the logout writes daily.
- login/login_case_mismatch: Usernames are case-sensitive so quillfox9 is no such user and no daily file exists.
- login/transactions_before_login: Nobody is logged in so create, delete, and logout each give please login first with no follow-up prompts and only the later session writes daily.
- logout/logout_not_logged_in: Nobody is logged in so logout gives please login first and no daily file exists.
- logout/logout_after_logout: First logout closes the session and writes 00, so the second logout gives please login first and adds nothing.
- logout/logout_blocks_until_login: Create after logout gives please login first, then a fresh login works, so daily holds two 00 lines in run order.
- create/create_success: Admin QuillFox9 plus fresh name NewTester plus type FS passes all checks so daily gets 01 with 000000.00 then 00.
- create/create_success_15char: FifteenCharUser is exactly 15 characters so the max-length boundary passes and daily gets 01 then 00.
- create/create_too_long: SixteenCharUser1 is 16 characters so create stops at username too long with no user-type prompt and daily holds only 00.
- create/create_duplicate_existing: MoonlitKai already exists so create stops at username already exists with no user-type prompt and daily holds only 00.
- create/create_duplicate_deleted_this_session: Nimbus2 was deleted earlier in the same session so re-create still stops at username already exists and daily holds only 02 then 00.
- create/create_empty_username: Blank new username stops at invalid username with no user-type prompt and daily holds only 00.
- create/create_end_username: New username END stops at invalid username with no user-type prompt and daily holds only 00.
- create/create_as_nonadmin: MoonlitKai is not admin so create stops at not allowed for this account type with no new-username prompt and daily holds only 00.
- delete/delete_success: Nimbus2 exists so admin delete succeeds and daily gets 02 with 000005.00 then 00.
- delete/delete_nonexistent: GhostAccount99 does not exist so delete gives no such user and daily holds only 00.
- delete/delete_empty_username: Blank delete username gives invalid username and daily holds only 00.
- delete/delete_end_username: Delete username END gives invalid username and daily holds only 00.
- delete/delete_as_nonadmin: MoonlitKai is not admin so delete stops at not allowed for this account type with no delete prompt and daily holds only 00.
- delete/delete_self_admin: QuillFox9 deletes self so the session ends at once with User deleted and daily holds 02 then 00 with the same credit and no typed logout.
- general/invalid_unknown_word: Frobnicate is not a transaction code so it gives invalid transaction and daily holds only 00.
- general/invalid_wrong_case: Transaction codes are case-sensitive so Login gives invalid transaction and daily holds only 00.
- general/invalid_empty_line: A blank transaction line gives invalid transaction and daily holds only 00.
- general/permission_sell_as_buystandard: Thistledown7 is BS so sell stops at not allowed for this account type with no sell prompts and daily holds only 00.
- general/permission_buy_as_sellstandard: CraterJax is SS so buy stops at not allowed for this account type with no buy prompts and daily holds only 00.
