#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


#define MAX_LINE_LENGTH 4095
#define HELP_MESSAGE "Usage:\n  tail [-n k] file \n -n k - output the last K lines, instead of the last 10\n"
#define ERROR_EXIT(message) fprintf(stderr, message);exit(1);
#define ERROR(message) fprintf(stderr, message);

//checks if string is a number
bool isNumber(char number[])
{
    for (int i = 0; number[i] != 0; i++)
    {
        if (!isdigit(number[i]))
            return false;
    }
    return true;
}

void shiftLines(size_t shiftBy, char lines[][MAX_LINE_LENGTH])
{
    for (size_t i = 0; i < shiftBy; i++)
    {
        memset(lines[i], '\0', sizeof(lines[i]));
        strcpy(lines[i], lines[i+1]);
    }
}

void shortenLine(char lines[][MAX_LINE_LENGTH], char newLine[], size_t linesRead)
{
    
    strncpy(lines[linesRead], newLine, MAX_LINE_LENGTH - 2);
    if (newLine[strlen(newLine) - 1] == '\n')
    {
        lines[linesRead][MAX_LINE_LENGTH - 2] = '\n';
    }
}

int main (int argc, char *argv[]) {
    int numOfLines = 10;
    FILE * file = NULL;

	// get args
    for (size_t i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-n") == 0)
        {
            if (argc > i + 1 && isNumber(argv[i + 1]))
            {
                numOfLines = atoi(argv[i + 1]);
                i++;
            }
            else
            {
                ERROR_EXIT(HELP_MESSAGE)
            }
        }
        else
        {
            if (file == NULL)
            {
                file = fopen(argv[i],"r");
            }
        }
    }

    //if not file provided use STDIN
    if (file == NULL)
    {
        file = stdin;
    }


    


    //read line by line,
    //until lines array is full
    //then with every new line, array
    //shifts by one to the left
    //and new line gets appended to the end 
    char lines[numOfLines][MAX_LINE_LENGTH];
    size_t len;
    size_t read;
    int linesRead = 0;
    bool isLongLineErrorPrinted = false;
    char * line = NULL;
    while ((read = getline(&line, &len, file)) != -1) {
        if (read > MAX_LINE_LENGTH)
        {
            if(!isLongLineErrorPrinted)
            {
            ERROR("Max line length exceeded\n")
            isLongLineErrorPrinted=true;
            }
            if (linesRead < numOfLines)
            {
                memset(lines[linesRead], '\0', sizeof(lines[linesRead]));
                shortenLine(lines,line,linesRead);
                linesRead++;
            }
            else
            {
                shiftLines(numOfLines,lines);
                memset(lines[linesRead - 1], '\0', sizeof(lines[linesRead - 1]));
                shortenLine(lines,line,linesRead - 1);
            }
        }
        else
        {
            if (linesRead < numOfLines)
            {
                memset(lines[linesRead], '\0', sizeof(lines[linesRead]));
                strcpy(lines[linesRead],line);
                linesRead++;
            }
            else
            {
                shiftLines(numOfLines,lines);
                memset(lines[linesRead - 1], '\0', sizeof(lines[linesRead - 1]));
                strcpy(lines[linesRead - 1],line);
            }    
        }
       
    }  

    //print last n lines
    for (size_t i = 0; i < linesRead; i++)
    {
        printf("%s",lines[i]);
    }

    free(line);
    return 0;
}

