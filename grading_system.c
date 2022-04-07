/* Program for grading marks obtained by a student
 * using conditional statements.
 */

# include <stdio.h>

int main()
{
    int student_marks = 0;

    printf ("Enter marks (out of 100): ");
    scanf ("%d", &student_marks);

    if (student_marks < 0) {
        printf ("error: marks entered subceeds 0\n");
        return 0;
    } else if (student_marks > 100) {
        printf ("error: marks entered exceeds 100\n");
        return 0;
    }

    printf ("Grade: ");
    if (student_marks <= 40) {
        printf ("F\n");
    } else if (student_marks > 40 && student_marks <= 55) {
        printf ("E\n");
    } else if (student_marks > 55 && student_marks <= 70) {
        printf ("D\n");
    } else if (student_marks > 70 && student_marks <= 85) {
        printf ("C\n");
    } else if (student_marks > 85 && student_marks <= 95) {
        printf ("B\n");
    } else if (student_marks > 95 && student_marks <= 100) {
        printf ("A\n");
    }
    return 0;
}
