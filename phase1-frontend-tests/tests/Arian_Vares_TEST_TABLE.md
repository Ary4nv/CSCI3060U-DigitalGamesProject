# Person B - Test Table (sell, buy, refund, addcredit, list)

Scope: Arian Vares only. Fixtures: per-test `accounts.txt` (28 chars/line), per-test `games.txt` (48 chars/line), same shared fixtures as Victor Ma.

| Folder                          | What it tests                                                                                                  |
| ------------------------------- | -------------------------------------------------------------------------------------------------------------- |
| sell/successful_sell            | Full-standard user sells a game normally; checks both questions and the 03 daily line                          |
| sell/price_over_max             | Price of 1000.00 is over the 999.99 maximum; refused before anything is saved                                  |
| sell/price_at_max               | Price of exactly 999.99 is accepted (boundary)                                                                 |
| sell/name_already_listed        | Game name already for sale by a different seller; refused, since uniqueness is checked globally across sellers |
| sell/name_too_long              | 26-character game name refused before the price prompt                                                         |
| sell/invalid_price              | Price is not a number; refused without crashing                                                                |
| sell/name_exactly_25            | 25-character game name accepted (boundary)                                                                     |
| sell/name_END                   | END is the file's end marker, so it can't be used as a game name                                               |
| sell/admin_can_sell             | Confirms an admin account can also sell, not just standard users                                               |
| sell/whole_dollar_price         | Price typed with no decimal (15) is saved zero-padded as 015.00                                                |
| sell/sellstandard_can_sell      | Confirms the positive case: a sell-standard account can list a game                                            |
| buy/successful_buy              | Buy-standard user buys a game; checks both questions and the 04 daily line                                     |
| buy/not_enough_credit           | Buyer's credit is below the game price; refused                                                                |
| buy/game_not_found              | No game with that name exists; refused right after the name is typed                                           |
| buy/buying_own_game             | Seller tries to buy their own listing; refused                                                                 |
| buy/already_owned               | Buying the same game twice in one session; second attempt refused                                              |
| buy/seller_over_max_credit      | Purchase would push the seller over the maximum account credit; refused                                        |
| buy/new_listing_same_session    | A game listed this same session can't be bought until the next session                                         |
| buy/admin_can_buy               | Confirms an admin account can also buy                                                                         |
| refund/successful_refund        | Admin moves credit from seller back to buyer; checks all three questions and the 05 line                       |
| refund/unknown_person           | Buyer username doesn't exist; refused before further questions                                                 |
| refund/same_person_twice        | Same username entered as buyer and seller; refused before an amount is asked                                   |
| refund/seller_not_enough_credit | Seller's credit is below the refund amount; refused                                                            |
| refund/buyer_over_max_credit    | Refund would push the buyer over the maximum account credit; refused                                           |
| refund/invalid_amount           | Checks negative, zero, and nonnumeric amounts in one session; all refused                                            |
| addcredit/admin_adds_to_other   | Admin adds credit to another user; amount is asked first, then the username                                    |
| addcredit/standard_adds_own     | A standard user adds credit to their own account; only the amount is asked                                     |
| addcredit/over_session_limit    | 1000.01 is over the session limit; refused                                                                     |
| addcredit/exactly_session_limit | 1000.00 is the highest amount allowed in one session; accepted (boundary)                                      |
| addcredit/over_max_credit       | Addition would push the account over the 999999.99 maximum; refused even though it's under the session limit     |
| addcredit/invalid_amount        | Not a real number; refused without crashing                                                                    |
| addcredit/unknown_user          | Admin names a username that doesn't exist; refused                                                             |
| list/games_for_sale             | Lists every game currently for sale with name, seller, and price                                               |
| list/nothing_for_sale           | Games file has nothing listed; prints the no-games message                                                     |
| list/read_only                  | Running list twice in a row gives identical output; nothing is written to the daily file                       |
| list/reflects_new_listing       | A game listed earlier in the session shows up in list right after                                              |
| list/stays_after_purchase       | A bought game remains listed, since digital copies don't run out                                               |
| bad_files/corrupt_accounts_file | accounts file has a bad line; login errors out with a format error |
| bad_files/corrupt_games_file | games file has a bad line; login errors after the username is accepted |
| bad_files/missing_accounts_file | accounts file doesn't exist; login errors immediately |
| bad_files/missing_games_file | games file doesn't exist; login errors after the username is accepted |
| refund/refund_as_nonadmin | A standard account cannot refund; rejection happens before buyer or seller prompts. |
| refund/unknown_seller | Refund rejects an unknown seller after accepting an existing buyer. |
