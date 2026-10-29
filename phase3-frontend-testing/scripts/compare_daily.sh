#!/bin/bash
# compare_daily.sh   (handout step 6)
#
# Checks the daily transaction file of every test against expected_daily.txt.
# If a test has no expected_daily.txt it means no daily file should be written,
# so the test passes only when the program did not write one.
# The differences for a failed test are saved in <name>.daily.diff
#
# usage:  ./scripts/compare_daily.sh <output_directory> [name_filter]
# prints one PASS or FAIL line per test, exit code is 1 if anything failed

SUITE="$(cd "$(dirname "$0")/.." && pwd)"
OUT="$1"
FILTER="$2"

if [ -z "$OUT" ] || [ ! -d "$OUT" ]; then
    echo "usage: compare_daily.sh <output_directory> [name_filter]"
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
    ACTUAL="$OUT/$NAME.atf"
    DIFF="$OUT/$NAME.daily.diff"
    rm -f "$DIFF"

    if [ -f "$DIR/expected_daily.txt" ]; then
        # a daily file is expected, so it has to exist and match
        if [ ! -f "$ACTUAL" ]; then
            echo "no daily transaction file was written" > "$DIFF"
        else
            diff "$DIR/expected_daily.txt" "$ACTUAL" > "$DIFF" 2>&1
            if [ $? -eq 0 ]; then
                rm -f "$DIFF"
            fi
        fi
    else
        # no daily file expected, so there must not be one
        if [ -f "$ACTUAL" ]; then
            echo "a daily transaction file was written but none was expected" > "$DIFF"
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

echo "daily files: $PASSED passed, $FAILED failed"
if [ "$FAILED" -gt 0 ]; then
    exit 1
fi
exit 0
