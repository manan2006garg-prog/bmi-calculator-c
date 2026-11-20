#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_READINGS 50
#define INPUT_SIZE 128

typedef struct {
    double weight_kg;
    double height_cm;
    double bmi;
    const char *category;
} Reading;

static int read_line(const char *prompt, char *buffer, size_t size) {
    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) == NULL) {
        return 0;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
    return 1;
}

static int parse_double(const char *text, double *value) {
    char *end = NULL;
    errno = 0;
    *value = strtod(text, &end);
    if (text == end || errno == ERANGE) {
        return 0;
    }
    while (isspace((unsigned char)*end)) {
        end++;
    }
    return *end == '\0';
}

static double read_range(const char *prompt, double min, double max) {
    char buffer[INPUT_SIZE];
    double value;
    while (1) {
        if (!read_line(prompt, buffer, sizeof(buffer))) {
            puts("Input ended.");
            exit(EXIT_FAILURE);
        }
        if (parse_double(buffer, &value) && value >= min && value <= max) {
            return value;
        }
        printf("Enter a number from %.1f to %.1f.\n", min, max);
    }
}

static const char *classify(double bmi) {
    if (bmi < 18.5) return "Below range";
    if (bmi < 25.0) return "Typical range";
    if (bmi < 30.0) return "Above range";
    return "High range";
}

int main(void) {
    Reading readings[MAX_READINGS];
    int count = (int)read_range("Number of readings (1-50): ", 1, MAX_READINGS);
    double total = 0.0;
    double lowest = 0.0;
    double highest = 0.0;

    for (int i = 0; i < count; i++) {
        char prompt[80];
        printf("\nReading %d\n", i + 1);
        snprintf(prompt, sizeof(prompt), "Weight in kg (1-500): ");
        readings[i].weight_kg = read_range(prompt, 1.0, 500.0);
        readings[i].height_cm = read_range("Height in cm (50-250): ", 50.0, 250.0);
        double height_m = readings[i].height_cm / 100.0;
        readings[i].bmi = readings[i].weight_kg / (height_m * height_m);
        readings[i].category = classify(readings[i].bmi);
        total += readings[i].bmi;
        if (i == 0 || readings[i].bmi < lowest) lowest = readings[i].bmi;
        if (i == 0 || readings[i].bmi > highest) highest = readings[i].bmi;
        printf("BMI: %.1f (%s)\n", readings[i].bmi, readings[i].category);
    }

    puts("\nSummary");
    printf("Readings: %d\nAverage BMI: %.1f\nLowest BMI: %.1f\nHighest BMI: %.1f\n",
           count, total / count, lowest, highest);
    puts("BMI is a rough screening measure and is not a medical diagnosis.");
    return 0;
}
