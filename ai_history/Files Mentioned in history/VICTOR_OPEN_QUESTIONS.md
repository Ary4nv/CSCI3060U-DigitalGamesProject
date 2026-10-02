# Victor Ma - Open questions and choices

The handout and Slack updates define requirements. Team documentation defines the selected prompt and error wording where the client did not specify it.

## Invalid user type

Create accepts AA, FS, BS, or SS. The team-selected error for other types is `ERROR: invalid user type`. The test `create/invalid_user_type` checks type XX and omits the failed create from the daily file.

## Remaining choices

Permission checks happen before follow-up prompts. Blank and END usernames are rejected as invalid username. Multiple login/logout sessions overwrite the daily output at each logout, leaving the most recent session. These choices can be revised following client clarification.
