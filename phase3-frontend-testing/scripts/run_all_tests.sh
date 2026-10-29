#!/bin/bash
# run_all_tests.sh
#
# Does the whole test process with one command:
#   1. builds the Front End (make, so the newest source is always tested)
#   2. runs every test            (run_tests.sh)
#   3. checks the daily files     (compare_daily.sh)
#   4. checks the terminal output (compare_terminal.sh)
#   5. writes a summary of this run
# Every run gets its own folder in results/ (run_01, run_02, ...) so the old
# runs stay there and can be used in the failure log.
#
# usage:  ./scripts/run_all_tests.sh [label]
#   label is optional text added to the folder name, for example "after_fix"
# exit code is 0 when every test passed and 1 when something failed

SUITE="$(cd "$(dirname "$0")/.." && pwd)"
LABEL="$1"

# always run make first so the tests never use an old build of the program
# (make does nothing if the source files did not change)
# if FRONTEND is set to some other program, that one is tested and make is skipped
if [ -z "$FRONTEND" ]; then
    FRONTEND="$SUITE/distribution-system"
    echo "building the Front End"
    make -C "$SUITE" > /dev/null || exit 2
fi
export FRONTEND

# work out the number of this run from the run folders that already exist
PREVIOUS=$(ls -d "$SUITE"/results/run_[0-9][0-9]* 2>/dev/null | wc -l)
NUMBER=$(printf "%02d" $((PREVIOUS + 1)))
RUN="$SUITE/results/run_$NUMBER"
if [ -n "$LABEL" ]; then
    RUN="${RUN}_$LABEL"
fi
OUT="$RUN/outputs"
mkdir -p "$OUT"

echo "=== run $NUMBER ==="
"$SUITE/scripts/run_tests.sh" "$OUT" > "$RUN/run_tests.log"
"$SUITE/scripts/compare_daily.sh" "$OUT" > "$RUN/daily_check.txt"
"$SUITE/scripts/compare_terminal.sh" "$OUT" > "$RUN/terminal_check.txt"

# build summary.txt, one line per test:  PASS name group   or   FAIL name group <what failed>
SUMMARY="$RUN/summary.txt"
: > "$SUMMARY"
TOTAL=0
PASSED=0
FAILED=0

for FILE in "$OUT"/*.code; do
    NAME="$(basename "$FILE" .code)"
    GROUP="$(cat "$OUT/$NAME.group")"
    WHY=""
    if grep -q "^FAIL $NAME\$" "$RUN/daily_check.txt"; then
        WHY="$WHY daily"
    fi
    if grep -q "^FAIL $NAME\$" "$RUN/terminal_check.txt"; then
        WHY="$WHY terminal"
    fi
    # 124 is a timeout, 126 and up means the program was not found or crashed
    CODE="$(cat "$FILE")"
    if [ "$CODE" -ge 124 ]; then
        WHY="$WHY crash(exit_$CODE)"
    fi
    TOTAL=$((TOTAL + 1))
    if [ -z "$WHY" ]; then
        echo "PASS $NAME $GROUP" >> "$SUMMARY"
        PASSED=$((PASSED + 1))
    else
        echo "FAIL $NAME $GROUP$WHY" >> "$SUMMARY"
        FAILED=$((FAILED + 1))
    fi
done

{
    echo "Run: $(basename "$RUN")"
    echo "Date: $(date '+%Y-%m-%d %H:%M')"
    echo "Machine: $(uname -s) $(uname -m)"
    echo "Front End: $(basename "$FRONTEND")"
    echo "Total: $TOTAL   Passed: $PASSED   Failed: $FAILED"
    echo ""
    echo "Per group (passed / total):"
    awk '{ total[$3]++; if ($1 == "PASS") pass[$3]++ }
         END { for (g in total) printf "  %-14s %d / %d\n", g, pass[g], total[g] }' "$SUMMARY" | sort
    echo ""
    echo "Failed tests (and which check failed):"
    grep '^FAIL' "$SUMMARY" | awk '{ printf "  %s  (failed:", $2; for (i = 4; i <= NF; i++) printf " %s", $i; print ")" }'
} > "$RUN/report.txt"

cat "$RUN/report.txt"

# results/latest always points at the newest run
rm -f "$SUITE/results/latest"
ln -s "$(basename "$RUN")" "$SUITE/results/latest"

if [ "$FAILED" -gt 0 ]; then
    exit 1
fi
exit 0
