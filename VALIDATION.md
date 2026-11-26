# Solution and validation

The Date class validates dates before assigning fields, uses Gregorian leap-year
rules, and implements all required operators. The supplied Test and main
functions are preserved. Date shifts normalize across months; subtraction of
two dates uses Gregorian ordinal values and returns the absolute difference.
Shifts take O(1 + abs(days) / 28) time and O(1) space; comparison, date difference,
and single-day increments take O(1) time and space.

Local validation:

- Both the initial CMake build and the final C++11 Makefile build passed.
- A fresh Git checkout built successfully with make.
- The README sample and 1,284 Python datetime comparisons passed.
- The advertised /workspace/data/110/data_test directory was unavailable.

## Judge attempts

| Attempt | Submission ID | Build / transport | Result | Score |
| --- | --- | --- | --- | --- |
| 1 | 879595 | CMake / HTTPS | Compile Error | 0 |
| 2 | 879598 | CMake / SSH port 443 | Compile Error | 0 |
| 3 | 879600 | Makefile / HTTPS | Compile Error | 0 |
| 4 | 879603 | Makefile / standard SSH | Compile Error | 0 |
| 5 | 879604 | Makefile / HTTPS | Compile Error | 0 |

The fourth submit request timed out after the server created the submission.
Its ID was recovered from the submission listing and its final status was
checked using acmoj_client.py. All five attempts completed; none were aborted.
The API supplied only "compile error", without compiler diagnostics or test
results, so the cause remains unresolved. The submission limit is exhausted.
No repository edits or pushes occurred while a submission was being judged.
