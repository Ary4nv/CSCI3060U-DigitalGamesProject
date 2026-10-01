# Victor Ma - open questions / choices

These are the few places where the handout or Slack answers did not fully pin down the behavior. I wrote down the choice I used so the tests stay consistent.

## 1. Invalid account type during create

Create only accepts `AA`, `FS`, `BS`, or `SS`, but there was no exact error message given for something like `XX`.

For the tests I used:

`ERROR: invalid user type`

Covered in `create/create_duplicate_deleted_this_session`. That test also checks trying to reuse a username that was deleted earlier in the same session. Neither failed create should be written to the daily file.

## 2. When permission is checked

I check account permissions before asking for the rest of the transaction input. For example, if a BS user types `sell`, it gets refused before asking for a game name. Same idea for SS trying `buy`, or a non-admin trying `create` or `delete`.

## 3. Username case

Usernames are case-sensitive, so `quillfox9` is not the same as `QuillFox9`.

## 4. Tests I did not repeat

I did not add a separate login test only for a username over 15 characters. The 15-character limit is already tested directly by create with one 15-character name and one 16-character name. Login already has unknown user, blank username, `END`, and case mismatch cases, so another very similar test did not seem useful.
