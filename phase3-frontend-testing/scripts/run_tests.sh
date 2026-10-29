#!/bin/bash
# run_tests.sh   (handout step 5)
#
# Runs the Front End once for every test and saves what it produced.
# For a test called  sell_successful_sell  the output directory gets:
#   sell_successful_sell.out    what the program printed on the terminal
#   sell_successful_sell.atf    the daily transaction file it wrote
#   sell_successful_sell.err    anything it printed on standard error
#   sell_successful_sell.code   the exit code of the program
#   sell_successful_sell.group  the group folder of the test (sell)
#
# usage:  ./scripts/run_tests.sh <output_directory> [name_filter]
#   name_filter is optional, for example "sell" only runs tests with sell in the path
# FRONTEND can point at the program, otherwise ./distribution-system is used

SUITE="$(cd "$(dirname "$0")/.." && pwd)"
OUT="$1"
FILTER="$2"
FRONTEND="${FRONTEND:-$SUITE/distribution-system}"

if [ -z "$OUT" ]; then
    echo "usage: run_tests.sh <output_directory> [name_filter]"
    exit 2
fi

if [ ! -x "$FRONTEND" ]; then
    echo "cannot find the program $FRONTEND  (run make first)"
    exit 2
fi

mkdir -p "$OUT"
OUT="$(cd "$OUT" && pwd)"

# the Mac does not have timeout, so use gtimeout or nothing
if command -v timeout >/dev/null 2>&1; then
    LIMIT="timeout 10"
elif command -v gtimeout >/dev/null 2>&1; then
    LIMIT="gtimeout 10"
else
    LIMIT=""
fi

COUNT=0
# every test is a folder inside a group folder, like tests/sell/successful_sell
while IFS= read -r DIR; do
    if [ -n "$FILTER" ]; then
        case "${DIR#$SUITE/tests/}" in
            *"$FILTER"*) ;;
            *) continue ;;
        esac
    fi

    GROUP="$(basename "$(dirname "$DIR")")"
    NAME="${GROUP}_$(basename "$DIR")"

    # most tests use the shared empty-ish games collection file
    # a test can have its own gamescollection.txt if it needs one
    COLLECTION="$DIR/gamescollection.txt"
    if [ ! -f "$COLLECTION" ]; then
        COLLECTION="$SUITE/tests/fixtures/gamescollection.txt"
    fi

    # remove old files from a previous run so they cannot be mistaken for new ones
    rm -f "$OUT/$NAME.out" "$OUT/$NAME.atf" "$OUT/$NAME.err" "$OUT/$NAME.code" "$OUT/$NAME.group"

    echo "running test $NAME"

    # the program is run inside the test folder so accounts.txt and games.txt
    # are found by their short names (a missing one is a test on purpose)
    cd "$DIR"
    $LIMIT "$FRONTEND" accounts.txt games.txt "$COLLECTION" "$OUT/$NAME.atf" \
        < input.txt > "$OUT/$NAME.out" 2> "$OUT/$NAME.err"
    echo $? > "$OUT/$NAME.code"
    echo "$GROUP" > "$OUT/$NAME.group"

    COUNT=$((COUNT + 1))
done < <(find "$SUITE/tests" -mindepth 2 -maxdepth 2 -type d | sort)

echo "ran $COUNT tests, outputs saved in $OUT"
