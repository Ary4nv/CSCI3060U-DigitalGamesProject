# Victor Ma test table

Quick summary of what each test folder is for.

| Test folder                                  | What it checks                                                   |
| -------------------------------------------- | ---------------------------------------------------------------- |
| login/login_success_admin                    | admin can login/logout and 00 has current credit                 |
| login/login_success_standard                 | standard user can login/logout                                   |
| login/login_unknown_user                     | unknown username is refused; no daily file                       |
| login/login_empty_username                   | blank username is refused                                        |
| login/login_end_username                     | `END` is refused as a username                                   |
| login/login_second_login_refused             | cannot login again during an active session                      |
| login/login_case_mismatch                    | username matching is case-sensitive                              |
| login/transactions_before_login              | transactions are blocked before login                            |
| logout/logout_not_logged_in                  | logout before login is refused                                   |
| logout/logout_after_logout                   | second logout is refused; no extra daily line                    |
| logout/logout_blocks_until_login             | user has to login again after logout                             |
| create/create_success                        | admin creates FS user with 0.00 credit                           |
| create/create_success_15char                 | 15-character username is accepted                                |
| create/create_too_long                       | 16-character username is refused                                 |
| create/create_duplicate_existing             | existing username is refused                                     |
| create/create_duplicate_deleted_this_session | deleted name is still unavailable; bad type `XX` is also refused |
| create/create_empty_username                 | blank new username is refused                                    |
| create/create_end_username                   | `END` is refused as a new username                               |
| create/create_as_nonadmin                    | non-admin cannot create                                          |
| delete/delete_success                        | admin deletes an existing user                                   |
| delete/delete_nonexistent                    | nonexistent user is refused                                      |
| delete/delete_empty_username                 | blank delete username is refused                                 |
| delete/delete_end_username                   | `END` is refused at the delete prompt                            |
| delete/delete_as_nonadmin                    | non-admin cannot delete                                          |
| delete/delete_self_admin                     | admin self-delete is allowed; our design ends the session        |
| general/invalid_unknown_word                 | unknown transaction word is refused                              |
| general/invalid_wrong_case                   | wrong-case transaction word is refused                           |
| general/invalid_empty_line                   | blank transaction is refused                                     |
| general/permission_sell_as_buystandard       | BS cannot sell                                                   |
| general/permission_buy_as_sellstandard       | SS cannot buy                                                    |
