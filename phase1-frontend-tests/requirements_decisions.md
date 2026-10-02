# Requirement decisions

The handout and Slack updates are the sources of requirements. The shared foundation document is a team output convention, not an additional client requirement.

- Create starts new accounts at 0.00 and does not ask for initial credit. After the blackout ends, we will ask the client to resolve the conflicting Slack answers.
- Account credit uses nine characters; game prices use six. Usernames use 15 and game names 25, following example widths.
- Invalid create account types produce `ERROR: invalid user type`. Covered by create/invalid_user_type.
- Permissions are checked before follow-up prompts. Non-admin refund uses the existing permission error.
- Multiple sessions overwrite the daily file at each logout, so the final output contains only the latest session. Failed transactions are omitted. No successful login means no daily file.
- Admin self-delete ends the session immediately, recording delete then session end.
- Game names are globally unique. List uses file order, appending new listings. Bought games stay in the storefront.
- We choose a cumulative addcredit allowance per account per session. Its reset behavior requires later implementation testing.
- Persisted collection ownership, refund ownership removal, and re-buy after refund need later testing with collection data. No claim is made that the present two-file Front End tests establish those behaviors.
- The handling of deleted users' attached data still requires an explicit team decision and corresponding tests where observable.
