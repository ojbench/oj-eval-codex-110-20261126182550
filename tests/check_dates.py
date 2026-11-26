"""Compare the unchanged assignment driver with Python's Gregorian calendar."""
import datetime as dt
from pathlib import Path
import random
import subprocess


ROOT = Path(__file__).resolve().parents[1]


def formatted(day):
    return f"{day.year}-{day.month}-{day.day}"


def check(year, month, day):
    try:
        date = dt.date(year, month, day)
    except ValueError:
        date = dt.date(1900, 1, 1)
    expected = ["1900-1-1", "2000-2-29", "1900-1-1"]
    offsets = list(range(1, 6)) + list(range(5, 10))
    offsets += list(range(10, 5, -1)) + [4, 3, 3]
    expected += [formatted(date + dt.timedelta(days=n)) for n in offsets]
    expected += [formatted(date + dt.timedelta(days=100))]
    expected += [formatted(date - dt.timedelta(days=1000))]
    expected += [str(int(date < dt.date(2020, 12, 21)))]
    expected += [str(abs((date - dt.date(1912, 6, 23)).days))]
    data = "0\n" + f"{year} {month} {day}\n" * 4
    actual = subprocess.check_output([str(ROOT / "code")], input=data, text=True)
    assert actual.splitlines() == expected, (year, month, day, actual, expected)


readme = (ROOT / "README.md").read_text()
sample_input = readme.split("**Input:**\n```\n", 1)[1].split("```", 1)[0]
sample_output = readme.split("**Output:**\n```\n", 1)[1].split("```", 1)[0]
assert subprocess.check_output(
    [str(ROOT / "code")], input=sample_input, text=True
) == sample_output

count = 0
for year in (1900, 1904, 1999, 2000, 2001, 2020, 2030):
    for month in range(0, 14):
        for day in (0, 1, 27, 28, 29, 30, 31, 32):
            check(year, month, day)
            count += 1

rng = random.Random(1073)
for _ in range(500):
    date = dt.date(1900, 1, 1) + dt.timedelta(days=rng.randrange(47847))
    check(date.year, date.month, date.day)
    count += 1
print(f"Passed README sample and {count} calendar comparisons.")
