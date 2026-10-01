# Victor Ma review checklist

This is the list I used for a final pass through my folders.

- `login/login_success_admin` - normal admin login/logout; 00 line keeps the current credit
- `login/login_success_standard` - normal standard account login/logout
- `login/login_unknown_user` - unknown username is refused and no daily file is made
- `login/login_empty_username` - blank username is refused
- `login/login_end_username` - `END` cannot be used as a login username
- `login/login_second_login_refused` - second login is refused while a session is active
- `login/login_case_mismatch` - checks case-sensitive usernames
- `login/transactions_before_login` - real transactions are blocked before login, then login still works
- `logout/logout_not_logged_in` - logout before login is refused; no daily file
- `logout/logout_after_logout` - second logout is refused and does not add another 00 line
- `logout/logout_blocks_until_login` - after logout, another login is needed before transactions work
- `create/create_success` - admin creates an FS user starting at 0.00 credit
- `create/create_success_15char` - exactly 15 characters is accepted
- `create/create_too_long` - 16 characters is refused before asking for type
- `create/create_duplicate_existing` - existing username is refused
- `create/create_duplicate_deleted_this_session` - deleted name still cannot be reused in the same session; also checks type `XX`
- `create/create_empty_username` - blank username is refused
- `create/create_end_username` - `END` cannot be a real username
- `create/create_as_nonadmin` - non-admin cannot create users
- `delete/delete_success` - admin deletes an existing user
- `delete/delete_nonexistent` - unknown user cannot be deleted
- `delete/delete_empty_username` - blank delete username is refused
- `delete/delete_end_username` - `END` is not treated as an account
- `delete/delete_as_nonadmin` - non-admin cannot delete users
- `delete/delete_self_admin` - admin can delete themself; in our design this ends the session
- `general/invalid_unknown_word` - unknown transaction word is invalid
- `general/invalid_wrong_case` - transaction words are lowercase
- `general/invalid_empty_line` - blank transaction is invalid
- `general/permission_sell_as_buystandard` - BS cannot sell
- `general/permission_buy_as_sellstandard` - SS cannot buy

For tests where nobody successfully logs in, there is no `expected_daily.txt` file.
