#!/bin/bash
# checks the fixed-width files in the test suite
#   accounts.txt        every line 28 characters
#   games.txt           every line 48 characters
#   expected_daily.txt  line length depends on the transaction code
#                       00/01/02/06 = 31, 03 = 51, 04 = 67, 05 = 44
# skip the intentionally broken fixture folders
# usage:  ./scripts/check_formats.sh

SUITE="$(cd "$(dirname "$0")/.." && pwd)"
BAD=0

check_length() {
    awk -v want="$2" 'length($0) != want { printf "%s line %d has %d characters, expected %d\n", FILENAME, FNR, length($0), want; bad = 1 }
                      END { exit bad }' "$1"
}

while IFS= read -r FILE; do
    case "$FILE" in *corrupt*) continue ;; esac
    check_length "$FILE" 28 || BAD=1
done < <(find "$SUITE/tests" -name accounts.txt | sort)

while IFS= read -r FILE; do
    case "$FILE" in *corrupt*) continue ;; esac
    check_length "$FILE" 48 || BAD=1
done < <(find "$SUITE/tests" -name games.txt | sort)

while IFS= read -r FILE; do
    awk '
        { code = substr($0, 1, 2) }
        code == "00" || code == "01" || code == "02" || code == "06" { want = 31 }
        code == "03" { want = 51 }
        code == "04" { want = 67 }
        code == "05" { want = 44 }
        code !~ /^0[0-6]$/ { printf "%s line %d has an unknown code\n", FILENAME, FNR; bad = 1; next }
        length($0) != want { printf "%s line %d has %d characters, expected %d\n", FILENAME, FNR, length($0), want; bad = 1 }
        END { exit bad }
    ' "$FILE" || BAD=1
    LAST="$(tail -n 1 "$FILE" | cut -c1-2)"
    if [ "$LAST" != "00" ]; then
        echo "$FILE does not end with a 00 line"
        BAD=1
    fi
done < <(find "$SUITE/tests" -name expected_daily.txt | sort)

if [ "$BAD" -eq 0 ]; then
    echo "All test files have the correct line lengths."
    exit 0
fi
echo "Some test files have the wrong format."
exit 1
