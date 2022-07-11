#!/bin/bash
rm -r coverage/ 2>/dev/null
g++ --coverage $1 -o coverageexe
./coverageexe
mkdir coverage 2>/dev/null
mv *.gcda coverage/ 2>/dev/null
mv *.gcno coverage/ 2>/dev/null
mv *.gcov coverage/ 2>/dev/null
mv *.gch coverage/ 2>/dev/null
lcov --capture --directory coverage --output-file=coverage/coverage.info
genhtml coverage/coverage.info --output-directory=coverage
rm coverageexe
lynx coverage/index.html