#!/bin/bash

TEST_DIR="build/tests"
failures=0
VERBOSE=0
VERBOSE_FAIL=0

# Parse arguments: --verbose / -v and --verbose-fail
for arg in "$@"; do
    case "$arg" in
        --verbose|-v)
            VERBOSE=1
            ;;
        --verbose-fail)
            VERBOSE_FAIL=1
            ;;
        *)
            # ignore unknown
            ;;
    esac
done

echo "Running tests in $TEST_DIR (verbose=$VERBOSE, verbose-fail=$VERBOSE_FAIL)"

# build sorted list of executable test files (human/numeric order)
mapfile -t test_files < <(find "$TEST_DIR" -maxdepth 1 -type f -executable | sort -V)

for test_file in "${test_files[@]}"; do
    if [[ -x "$test_file" && -f "$test_file" ]]; then
        if [[ $VERBOSE -eq 1 ]]; then
            # verbose mode: stream output for all tests, then show marker
            echo -e ">>> Executando $test_file <<<\n"
            "$test_file"
            rc=$?
            if [[ $rc -eq 0 ]]; then
                echo -e "[SUCCESS] $test_file returned 0\n"
            else
                echo -e "[FAIL]    $test_file returned exit code $rc\n"
                failures=$((failures + 1))
            fi

        elif [[ $VERBOSE_FAIL -eq 1 ]]; then
            # verbose-fail: capture output and show only if test fails
            tmp_out=$(mktemp)
            tmp_err=$(mktemp)
            "$test_file" > "$tmp_out" 2> "$tmp_err"
            rc=$?
            if [[ $rc -eq 0 ]]; then
                echo "[SUCCESS]   $test_file"
            else
                echo -e ">>> Executando $test_file <<<\n"
                # show stdout then stderr
                if [[ -s "$tmp_out" ]]; then
                    cat "$tmp_out"
                fi
                if [[ -s "$tmp_err" ]]; then
                    cat "$tmp_err" >&2
                fi
                echo -e "[FAIL]    $test_file returned exit code $rc\n"
                failures=$((failures + 1))
            fi
            rm -f "$tmp_out" "$tmp_err"

        else
            # non-verbose mode: show only OK/FAIL per test, no output
            "$test_file" > /dev/null 2>&1
            rc=$?
            if [[ $rc -eq 0 ]]; then
                echo "[SUCCESS]   $test_file"
            else
                echo "[FAIL] $test_file (exit code $rc)"
                failures=$((failures + 1))
            fi
        fi
    fi
done

if [[ $failures -gt 0 ]]; then
    echo "Summary: $failures test(s) failed."
    if [[ $failures -gt 255 ]]; then
        exit 255
    else
        exit $failures
    fi
else
    echo "Summary: all tests passed."
    exit 0
fi