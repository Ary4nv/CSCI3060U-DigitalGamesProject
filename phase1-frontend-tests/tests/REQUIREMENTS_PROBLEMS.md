# Victor Ma - requirement problems / assumptions

These are the parts I had to make a decision on while writing my tests. I kept them here so the tests do not end up using different assumptions.

## 1. Available games line length

One part says 49 characters and another says 42, but the example fields add up to 48 (`25 + 1 + 15 + 1 + 6`). We used the example field sizes, so our game records are 48 characters.

## 2. END records

The handout says the files end with `END`, but the padding is not shown very clearly. We put `END` at the start of the name field and pad the rest with spaces. That gives a 28-character account END line and a 48-character games END line.

## 3. Example games file formatting

In the copied example, `Quiet Nova Protocol` and `Paperclip Expedition` look like they run together. We treated them as two different records.

## 4. Invalid user type on create

Valid types are `AA`, `FS`, `BS`, and `SS`. Since there was no exact error text for a bad type, we use `ERROR: invalid user type`. The case is tested in `create/create_duplicate_deleted_this_session`.

## 5. Admin deleting their own account

The Slack answer says an admin can delete their own account. Our choice is that doing this ends the current session immediately. The daily file gets the `02` delete line, then the `00` session-end line.

## 6. What happens after logout

A normal logout does not close the whole program. It goes back to `Enter transaction:` and waits for another login.

## 7. More than one session in one input run

If the input has two login/logout sessions, both sessions are kept in the same daily transaction file in the order they happen.

## 8. Permission checks happen first

If the logged-in account cannot use a transaction, the program refuses it before asking for transaction details. The non-admin create/delete tests and the BS/SS permission tests use this behavior.

## 9. Invalid command before login

It was not clear whether a completely made-up command before login should give `invalid transaction` or `please login first`. I did not guess on that ordering. The before-login test uses real transaction names, and invalid command tests are done while logged in.

## 10. Username case

Usernames are case-sensitive. `quillfox9` does not match `QuillFox9`. Covered in `login/login_case_mismatch`.

## 11. Username length

We use the 15-character maximum from the examples/Slack clarification. Create checks both sides of the limit: 15 works and 16 fails.

## 12. Blank username and END

A blank username and the literal word `END` are not valid usernames. For those cases we use `ERROR: invalid username`.

## 13. Failed transactions and the daily file

Failed/refused transactions do not get a daily transaction line. If no login session ever starts, there should not be a daily file at all.

## 14. Logging in twice

If someone is already logged in, another `login` is refused immediately with `ERROR: already logged in`. It does not ask for another username.

## 15. Reusing a deleted username in the same session

Our team choice is that a username deleted earlier in the current session still cannot be reused by `create` in that same session. Covered in `create/create_duplicate_deleted_this_session`.

## 16. Arian Vares coverage

Sell, buy, refund, addcredit, list, game-name rules, and most money edge cases are in Arian Vares's tests. Victor Ma only includes the small buy/sell permission checks needed for account-type permissions.
