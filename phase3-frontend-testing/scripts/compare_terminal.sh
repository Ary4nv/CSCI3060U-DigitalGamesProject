#!/bin/bash
# compare_terminal.sh   (handout step 6, the terminal output part)
#
# Checks the terminal output of every test against expected_terminal.txt.
# The differences for a failed test are saved in <name>.terminal.diff
#
# usage:  ./scripts/compare_terminal.sh <output_directory> [name_filter]
# prints one PASS or FAIL line per test, exit code is 1 if anything failed

SUITE="$(cd "$(dirname "$0")/.." && pwd)"
OUT="$1"
FILTER="$2"

if [ -z "$OUT" ] || [ ! -d "$OUT" ]; then
    echo "usage: compare_terminal.sh <output_directory> [name_filter]"
    exit 2
fi

PASSED=0
FAILED=0

while IFS= read -r DIR; do
    if [ -n "$FILTER" ]; then
        case "${DIR#$SUITE/tests/}" in
            *"$FILTER"*) ;;
            *) continue ;;
        esac
    fi

    GROUP="$(basename "$(dirname "$DIR")")"
    NAME="${GROUP}_$(basename "$DIR")"
    ACTUAL="$OUT/$NAME.out"
    DIFF="$OUT/$NAME.terminal.diff"
    rm -f "$DIFF"

    if [ ! -f "$ACTUAL" ]; then
        echo "no terminal output was saved for this test" > "$DIFF"
    else
        diff "$DIR/expected_terminal.txt" "$ACTUAL" > "$DIFF" 2>&1
        if [ $? -eq 0 ]; then
            rm -f "$DIFF"
        fi
    fi

    if [ -f "$DIFF" ]; then
        echo "FAIL $NAME"
        FAILED=$((FAILED + 1))
    else
        echo "PASS $NAME"
        PASSED=$((PASSED + 1))
    fi
done < <(find "$SUITE/tests" -mindepth 2 -maxdepth 2 -type d | sort)

echo "terminal outputs: $PASSED passed, $FAILED failed"
if [ "$FAILED" -gt 0 ]; then
    exit 1
fi
exit 0
