# Arian Vares - Review Checklist (one sentence per test)

Read input.txt vs expected_terminal.txt vs expected_daily.txt for each folder and confirm the sentence holds.

- sell/successful_sell: MoonlitKai is full-standard and the game name is new, so the sell is accepted and the 03 line is written before the normal 00 logout line.
- sell/price_over_max: 1000.00 is one cent over the 999.99 maximum so sell stops at the price error and nothing is saved.
- sell/price_at_max: 999.99 is the highest allowed price so the boundary case is accepted and saved.
- sell/name_already_listed: Starlit Driftwood already belongs to a different seller so the new listing is refused, confirming uniqueness is checked across every seller, not just the current one.
- sell/name_too_long: A 26 character game name is one over the limit so sell stops before the price prompt and nothing is saved.
- sell/invalid_price: abc is not a number so the price is refused and no 03 line is written.
- sell/name_exactly_25: A 25 character game name is exactly the limit so it's accepted and the full name appears in the 03 line.
- sell/name_END: END is the games file's end marker so it's refused as a game name before a price is ever asked.
- sell/admin_can_sell: QuillFox9 is an admin and sell succeeds for them the same as any standard account, proving admins keep every permission.
- sell/whole_dollar_price: 15 typed with no decimal is saved as 015.00 in the daily file, confirming the two-decimal padding rule.
- sell/sellstandard_can_sell: CraterJax is sell-standard and the sell succeeds, the positive counterpart to buy-standard being blocked from sell.
- buy/successful_buy: Thistledown7 is buy-standard and has enough credit, so the purchase succeeds and the 04 line records buyer, seller, game, and price.
- buy/not_enough_credit: Nimbus2 has 5.00 credit and Emberfall Circuit costs 30.00 so the purchase is refused and no balances change.
- buy/game_not_found: No game is named Nothing Here so buy stops right after the game name with no seller question asked.
- buy/buying_own_game: MoonlitKai tries to buy their own listing, Starlit Driftwood, and is refused since a seller can't buy their own game.
- buy/already_owned: Thistledown7 buys Starlit Driftwood successfully, then the identical buy is tried again in the same session and is refused as already owned.
- buy/seller_over_max_credit: Paying SilverQuasar1 would push them past 999999.99 so the purchase is refused even though the buyer could otherwise afford it.
- buy/new_listing_same_session: QuillFox9 lists Fresh Copper Ledger and immediately tries to buy it; the buy is refused since a new listing can't be purchased the same session it was created.
- buy/admin_can_buy: QuillFox9 successfully buys a game as an admin, proving admins keep buy permission too.
- refund/successful_refund: QuillFox9 moves 20.00 from MoonlitKai to Thistledown7 and the refund succeeds, writing the 05 line with both usernames and the amount.
- refund/unknown_person: Ghostwalker12 isn't a real account so the refund is refused at the buyer question before a seller is ever asked.
- refund/same_person_twice: MoonlitKai is entered as both buyer and seller so the refund is refused before an amount is requested.
- refund/seller_not_enough_credit: CraterJax has 50.00 credit and the refund asks for 100.00 so it's refused.
- refund/buyer_over_max_credit: SilverQuasar1 is already near the maximum credit so refunding them more is refused even though the seller could afford it.
- refund/invalid_amount: Negative, zero, and nonnumeric values are tried as amounts in the same session and both are refused, confirming negative and zero are rejected the same way.
- addcredit/admin_adds_to_other: QuillFox9 adds 50.00 to MoonlitKai, the amount is asked before the username, matching the agreed order for admins.
- addcredit/standard_adds_own: MoonlitKai adds credit to their own account and only the amount is asked, no username prompt, since standard accounts can only add to themselves.
- addcredit/over_session_limit: 1000.01 is one cent over the 1000.00 session limit so it's refused.
- addcredit/exactly_session_limit: 1000.00 is the highest amount allowed in one session and is accepted at that exact boundary.
- addcredit/over_max_credit: SilverQuasar1 is already near the account maximum so even 100.00, which is under the session limit, is refused for pushing them over 999999.99.
- addcredit/invalid_amount: lots is not a number so the addcredit is refused without crashing.
- addcredit/unknown_user: Ghostwalker12 isn't a real account so the addcredit is refused after a valid amount is entered.
- list/games_for_sale: Every game in the standard fixture is printed with its name, seller, and price in the order the games file lists them.
- list/nothing_for_sale: The games file used here is empty aside from END, so list prints the no-games message instead of an empty list.
- list/read_only: list is run twice in a row and both outputs are identical, and nothing is written to the daily file for either call.
- list/reflects_new_listing: MoonlitKai sells Hollow Paper Kite and list immediately after shows it appended to the end of the listing.
- list/stays_after_purchase: Thistledown7 buys Starlit Driftwood and list afterward still shows it for sale, since digital copies are not removed from the storefront.
- bad_files/corrupt_accounts_file: One account line is cut short, so login reports a format error before anything else happens.
- bad_files/corrupt_games_file: The username is accepted, then one games line is cut short, so login reports a format error at that point.
- bad_files/missing_accounts_file: The accounts file doesn't exist, so login fails immediately with a file error.
- bad_files/missing_games_file: The username is accepted, then the games file doesn't exist, so login fails with a file error.

- refund/refund_as_nonadmin: A standard account cannot refund; rejection happens before buyer or seller prompts.

- refund/unknown_seller: Refund rejects an unknown seller after accepting an existing buyer.

