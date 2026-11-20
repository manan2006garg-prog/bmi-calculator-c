# BMI Tracker

Record several height and weight readings in one run, calculate each BMI, and compare the lowest, highest, and average results.

## Build and run

Compile with a C11 compiler:

    gcc -std=c11 -Wall -Wextra -pedantic main.c -o bmi-tracker
    ./bmi-tracker

On Windows, run `bmi-tracker.exe` after compiling.

## Features

- Accepts 1 to 50 readings and validates the numeric ranges.
- Calculates BMI from kilograms and centimetres.
- Shows a simple category for each reading and an overall summary.
- Uses functions and a structure array to organize the data.

## Learning goals

Practice input validation, structures, arrays, functions, loops, and summary calculations in C. BMI categories are general screening ranges, not medical advice.
