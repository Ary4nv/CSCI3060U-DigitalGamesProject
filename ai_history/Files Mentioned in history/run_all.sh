#!/bin/bash
# Runs the Phase 1 test suite and saves the results for this run.
# Make sure the scripts are executable before running them.

# run all tests and save this run in a new results folder
# usage:  ./scripts/run_all.sh [text]
# optional argument filters by folder name
# (for example ./scripts/run_all.sh sell  runs the sell tests only)

SUITE="$(cd "$(dirname "$0")/.." && pwd)"
FILTER="$1"
STAMP="$(date +%Y%m%d_%H%M%S)"
RUN="$SUITE/results/run_$STAMP"
mkdir -p "$RUN/details"
SUMMARY="$RUN/summary.txt"
: > "$SUMMARY"

find "$SUITE/tests" -mindepth 2 -maxdepth 2 -type d | sort > "$RUN/test_list.txt"

TOTAL=0
PASSED=0
FAILED=0

while IFS= read -r DIR; do
    if [ -n "$FILTER" ]; then
        case "$DIR" in
            *"$FILTER"*) ;;
            *) continue ;;
        esac
    fi
    NAME="$(basename "$DIR")"
    GROUP="$(basename "$(dirname "$DIR")")"
    if "$SUITE/scripts/run_test.sh" "$DIR" "$RUN/details" > /dev/null; then
        echo "PASS $GROUP $NAME" >> "$SUMMARY"
        PASSED=$((PASSED + 1))
    else
        echo "FAIL $GROUP $NAME" >> "$SUMMARY"
        FAILED=$((FAILED + 1))
    fi
    TOTAL=$((TOTAL + 1))
done < "$RUN/test_list.txt"

rm -f "$RUN/test_list.txt"

{
    echo "Run: run_$STAMP"
    echo "Front End: ${FRONTEND:-./frontend}"
    echo "Total: $TOTAL   Passed: $PASSED   Failed: $FAILED"
    echo ""
    echo "Per group (passed / total):"
    awk '{ total[$2]++; if ($1 == "PASS") pass[$2]++ }
         END { for (g in total) printf "  %-20s %d / %d\n", g, pass[g], total[g] }' "$SUMMARY" | sort
    echo ""
    echo "Failed tests:"
    grep '^FAIL' "$SUMMARY" | awk '{ print "  " $3 }'
} > "$RUN/report.txt"

cat "$RUN/report.txt"

rm -f "$SUITE/results/latest"
ln -s "run_$STAMP" "$SUITE/results/latest"

if [ "$FAILED" -gt 0 ]; then
    exit 1
fi
exit 0
