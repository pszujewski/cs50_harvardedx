// this is just an example and is not for compiling

// create a variable called 'file' of data type FILE (native to C), also use star operator
// because fopen returns the memory address of the file.
// open up the file in write mode.
#define STUDENTS 3

FILE *file = fopen("students.csv", "w");
// The star above must dereference the pointer, otherwise we wouldn't be able to do the following operations.
if (file != NULL)
{
    for (int i = 0; i < STUDENTS; i++)
    {
        fprintf(file, "%s,%s", students[i].name, students[i].dorm);
    }
    fclose(file);
}