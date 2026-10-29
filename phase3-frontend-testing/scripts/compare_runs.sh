#!/bin/bash
# compare_runs.sh
#
# Compares the summary.txt of two runs so it is easy to see what a change fixed
# or broke. This is what we used to fill in the "run" columns of the failure log.
# usage:  ./scripts/compare_runs.sh results/run_01 results/run_02

OLD="$1"
NEW="$2"

if [ ! -f "$OLD/summary.txt" ] || [ ! -f "$NEW/summary.txt" ]; then
    echo "usage: compare_runs.sh <old_run_directory> <new_run_directory>"
    exit 2
fi

awk '
    NR == FNR { old[$2] = $1; next }
    {
        before = old[$2]
        if (before == "") before = "MISSING"
        if (before != $1) {
            label = "CHANGED"
            if (before == "PASS" && $1 == "FAIL") label = "REGRESSION"
            if (before == "FAIL" && $1 == "PASS") label = "FIXED"
            if (before == "MISSING") label = "NEW TEST"
            printf "%-11s %s   (%s -> %s)\n", label, $2, before, $1
            changed++
        }
    }
    END { if (changed == 0) print "No differences between the two runs." }
' "$OLD/summary.txt" "$NEW/summary.txt"

echo ""
echo "Old: $(grep -c '^PASS' "$OLD/summary.txt") passed, $(grep -c '^FAIL' "$OLD/summary.txt") failed"
echo "New: $(grep -c '^PASS' "$NEW/summary.txt") passed, $(grep -c '^FAIL' "$NEW/summary.txt") failed"
