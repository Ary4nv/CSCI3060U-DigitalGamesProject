#!/bin/bash
# run one test and compare the output files
# usage:  ./scripts/run_test.sh <test_directory> <results_directory>
# FRONTEND can point to the built program, otherwise it uses ./frontend

TEST_DIR="$1"
OUT_ROOT="$2"
FRONTEND="${FRONTEND:-./frontend}"

if [ -z "$TEST_DIR" ] || [ -z "$OUT_ROOT" ]; then
    echo "usage: run_test.sh <test_directory> <results_directory>"
    exit 2
fi

case "$FRONTEND" in
    /*) ;;
    *) FRONTEND="$(pwd)/$FRONTEND" ;;
esac

TEST_DIR="$(cd "$TEST_DIR" && pwd)"
mkdir -p "$OUT_ROOT"
OUT_ROOT="$(cd "$OUT_ROOT" && pwd)"
NAME="$(basename "$TEST_DIR")"
RES="$OUT_ROOT/$NAME"
mkdir -p "$RES"
rm -f "$RES"/*

if command -v timeout >/dev/null 2>&1; then
    LIMIT="timeout 10"
elif command -v gtimeout >/dev/null 2>&1; then
    LIMIT="gtimeout 10"
else
    LIMIT=""
fi

cd "$TEST_DIR"
$LIMIT "$FRONTEND" accounts.txt games.txt "$RES/daily.txt" < input.txt > "$RES/terminal.txt" 2> "$RES/stderr.txt"
CODE=$?
echo "$CODE" > "$RES/exit_code.txt"

STATUS=PASS

if [ "$CODE" -ge 124 ]; then
    STATUS=FAIL
    echo "program crashed, was not found, or timed out (exit code $CODE)" > "$RES/note.txt"
fi

if ! diff expected_terminal.txt "$RES/terminal.txt" > "$RES/terminal.diff" 2>&1; then
    STATUS=FAIL
fi

if [ -f expected_daily.txt ]; then
    if ! diff expected_daily.txt "$RES/daily.txt" > "$RES/daily.diff" 2>&1; then
        STATUS=FAIL
    fi
else
    if [ -f "$RES/daily.txt" ]; then
        echo "a daily transaction file was written but none was expected" > "$RES/daily.diff"
        STATUS=FAIL
    fi
fi

echo "$STATUS" > "$RES/status.txt"
echo "$STATUS $NAME"

if [ "$STATUS" = "PASS" ]; then
    exit 0
fi
exit 1
