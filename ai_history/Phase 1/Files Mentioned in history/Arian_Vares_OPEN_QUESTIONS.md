# Arian Vares - Open Questions (confirmed by assumption, not yet confirmed by the client)

Rule used: exact prompt and error wording from the shared foundation PDF only, word for word. Everything below has a working test built on a stated assumption; none were skipped outright, but these three aren't firmly confirmed by the client yet, and the tests may need to change if she answers differently.

## 1. Game name case sensitivity - answered, but not firmly

- Asked the client directly whether game names are case-sensitive the same way usernames are.
- Her answer was "not to my knowledge," which isn't the same as a firm yes.
- Current tests assume case-sensitive, matching how usernames already work. If the client later says names aren't case-sensitive, `sell/name_already_listed` and the implicit case-matching behavior in the simulator would need revisiting.

## 2. Game name uniqueness scope - answered with a recommendation, not a requirement

- Asked the client whether a game name must be unique across all sellers or only against that seller's own listings.
- She recommended global uniqueness but said it's ultimately the team's call, not a fixed requirement.
- Current tests assume global uniqueness (`sell/name_already_listed`). This is documented as a team decision, not a confirmed client rule, in case it comes up in lab.

## 3. addcredit session limit: cumulative vs per-transaction - deferred, not fully settled

- Asked the client whether the $1000.00 addcredit limit is cumulative across a session or applies per individual transaction.
- She said it's up to the team, and that real testing of this specific behavior happens in Phase 2 once the Front End actually exists.
- Current tests assume cumulative per account per session. This is explicitly flagged since the client herself said Phase 1 isn't where this gets finally verified.

No tests were skipped for missing wording the way Victor Ma had to skip the invalid-user-type case; every transaction assigned to Arian Vares had wording available in the shared foundation document for every test written.
