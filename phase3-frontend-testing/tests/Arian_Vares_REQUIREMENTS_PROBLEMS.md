# Arian Vares - Requirements Problems (ambiguities, contradictions, gaps)

Each item says which test(s) cover the assumption. All wording below in backticks is copied from the foundation PDF or the handout.

## 1. Price field length and padding

- Handout examples for price are inconsistent about digit count, the same issue as the username/game-name length conflict Arian Vares documented for the accounts and games files.
- Foundation 2.2 settles this at 6 characters, always two decimals, zero padded (e.g. `015.00`, max `999.99`).
- Covers: `sell/whole_dollar_price`, `sell/price_at_max`, `sell/price_over_max`.

## 2. Game name uniqueness: global or per-seller

- The handout never says whether two different sellers can list a game with the same name.
- Asked the client directly; she recommended global uniqueness (one name, one listing, no matter who sells it) but said it's ultimately the team's call.
- Assumption used: global uniqueness.
- Covers: `sell/name_already_listed`.

## 3. Game name case sensitivity

- Not stated in the handout. Usernames are confirmed case-sensitive; game names were assumed to follow the same rule for consistency.
- Asked the client; her answer was "not to my knowledge," not a firm confirmation either way.
- Assumption used: case-sensitive, matching usernames, still open if the client gives a firmer answer later.
- Covers: no dedicated test isolates this by itself; it's implicit in `sell/name_already_listed` using an exact-case match.

## 4. List display order

- The handout doesn't say whether `list` must show games in a specific order.
- Asked the client; her answer was that it's up to the team.
- Assumption used: the order the games file lists them in, with anything newly listed during the session appended at the end.
- Covers: `list/games_for_sale`, `list/reflects_new_listing`.

## 5. list is read-only and not saved to the daily file

- The Lab 1 update adds `list` but doesn't say whether it writes anything to the daily file.
- Assumption used: `list` never changes state and is never written to the daily file, only completed transactions are.
- Covers: `list/read_only`.

## 6. A newly listed game cannot be bought the same session

- Not stated directly, but follows from the handout's general rule that a new listing isn't available for purchase until a later session.
- Covers: `buy/new_listing_same_session`.

## 7. Buy's ownership check is session-only

- Buy must refuse a purchase if the buyer already owns the game, but the Front End is never given the Games Collection File, which is where real ownership history would live.
- Assumption used: only games bought earlier in the same session are checked; true cross-session ownership is a Back End concern.
- Covers: `buy/already_owned`.

## 8. Refund requires the seller to actually have the credit

- Not stated as an explicit rule in the handout.
- Asked the client directly; she confirmed a refund should be denied with an error if the seller's credit is insufficient.
- Covers: `refund/seller_not_enough_credit`.

## 9. Zero and negative amounts are rejected

- Not explicit in the handout for either refund or addcredit.
- Asked the client directly; she confirmed both must be rejected.
- Covers: `refund/invalid_amount`, `addcredit/invalid_amount`.

## 10. The addcredit session limit: cumulative or per transaction

- The handout says a maximum of $1000.00 can be added to an account in a session, but doesn't say whether that resets per transaction or totals across the whole session.
- Asked the client directly; her answer was that it's up to the team, and that real testing of this happens in Phase 2.
- Assumption used: cumulative total per account for the whole session.
- Covers: `addcredit/over_session_limit`, `addcredit/exactly_session_limit`.

## 11. No transaction may push an account over the maximum credit

- The 999,999.99 maximum is only mentioned under `create` in the handout, not explicitly for buy, refund, or addcredit.
- Assumption used: the limit applies to every transaction that can change an account's credit, not just account creation.
- Covers: `buy/seller_over_max_credit`, `refund/buyer_over_max_credit`, `addcredit/over_max_credit`.

## 12. Refund also removes the game from the buyer's collection

- Confirmed by the client directly, but the Front End is never given the Games Collection File, so this can't be shown in a Front End test.
- No Front End test is possible; documented here for completeness, same reasoning as item 7.

## 13. A buyer can re-buy a game they were refunded for

- Confirmed by the client directly.
- Depends on the Games Collection File the same way item 12 does, so it isn't independently testable at the Front End either. It's implied by `buy/already_owned` not applying once a refund has happened, which itself can't be shown without collection data.

## 14. A bought game stays visible in the storefront

- Not stated in the handout. Digital goods don't run out the way physical ones do, so the team chose to keep a sold game listed and purchasable by other buyers afterward.
- Covers: `list/stays_after_purchase`.

## 15. Admins keep every permission, including sell and buy

- The handout lists admin as having full access but doesn't give a worked example of an admin using sell or buy specifically.
- Covers: `sell/admin_can_sell`, `buy/admin_can_buy`.

## 16. Out of scope for Arian Vares, left to partner

- login/logout, create, delete, permission checks for create/delete/sell/buy-standard restrictions on those transactions, invalid transaction word handling, and missing/corrupt input files are covered in the Arian Vares documents.
