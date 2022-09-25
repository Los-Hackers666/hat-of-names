//
// Created by llth on 9/24/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_SIZE 255

typedef struct student
{
    char name[MAX_LINE_SIZE];
} student;

char **create_pool(const char *path, int student_count)
{
    FILE *file = NULL;
    file = fopen("../polla.txt"/*path*/, "r");
    char **pool = malloc(sizeof(char *) * student_count);

    if(file == NULL)
    {
        printf("Cannot open file %s", path);
        return NULL;
    }

    char buffer[MAX_LINE_SIZE];
    int index = 0;

    while(fgets(buffer,MAX_LINE_SIZE,file) != NULL)
    {
        student *s = malloc(sizeof(student));
        strcpy(s->name, buffer);

        *(pool + index) = s->name;

        index++;

    }

    return pool;
}


int count_students(const char *path)
{
    FILE *file = NULL;
    file = fopen("../polla.txt", "r");

    char buffer[MAX_LINE_SIZE];
    int student_count = 0;

    while(fgets(buffer,MAX_LINE_SIZE,file) != NULL)
    {
        student_count++;
    }

    fclose(file);

    return student_count;
}


student *pick_student(char **pool)
{
    int size= count_students("../polla.txt");

    if(size > 0)
    {
        srand(time(NULL));
        int line = rand() % size;

        while(*(pool + line) == NULL)
        {
            line= rand() % size;
        }

        student *victim = (student *) *(pool + line);
        *(pool + line) = NULL;

        return victim;
    }
    return NULL;
}

int main(int argc, char **argv)
{
    //FILE *descriptor = NULL;
    int size = count_students("../polla.txt"/*argv[1]*/);
    printf("%d\n", size);

    if(argc != 2) printf("Usage: hofn <file>");
    else
    {
        printf("Using file %s\n", argv[1]);
        char **pool = create_pool("../polla.txt"/*argv[1]*/, size);

        int command = 0;
        int count=0;
        while((command = fgetc(stdin))  != EOF){

            if(command == 'p')
            {
                if(count == size)
                {
                    printf("Ya no hay usuarios para mostrar padrino\n");
                    fflush(stdin);
                    break;
                }

                student *student_rand = pick_student(pool);
                count++;

                printf("Pulled: %s\n", student_rand->name);
                free(student_rand);
            }
            else
            {
                printf("Saquese pa, not a command");
                break;

            }
            fflush(stdin);
        }

    }

    return 0;
}
