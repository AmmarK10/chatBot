#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 500

int Similarity(char *s1, char *s2)
{
    int score = 0;
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] == s2[i])
        {
            score++;
        }
        i++;
    }

    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int diff = abs(len1 - len2);

    score -= diff;

    return score;
}


int searchMemory(char *input, char *response)
{
    FILE *file = fopen("memory.txt", "r");
    if (!file) return 0;

    char line[MAX];
    char bestAnswer[MAX];
    int bestScore = -999999; 

    while (fgets(line, sizeof(line), file))
    {
        char *q = strtok(line, ":");
        char *a = strtok(NULL, "\n");

        if (q && a)
        {
            int score = Similarity(input, q);

            if (score > bestScore)
            {
                bestScore = score;
                strcpy(bestAnswer, a);
            }
        }
    }

    fclose(file);

    if (bestScore > 1)
    {
        strcpy(response, bestAnswer);
        return 1;
    }

    return 0;
}


int saveMemory (char *question, char *answer)
{
    FILE *file = fopen("memory.txt", "a");

    if (file == NULL)
    {
        printf("Error opening file");
        return 0;
    }

    fprintf(file, "%s:%s", question, answer);
    fclose(file);
    return 1;
}

int main () {

    char input[MAX];
    char response[MAX];
    char ques[MAX];
    char ans[MAX];

    printf("Hello im C bot, Your AI Assistant\n");
    printf("cBot: Ask me anything or type exit to quit\n");
    
    while(1)
    {
        printf("\n\nYou: ");
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = 0;

        if ((strcmp(input, "exit") == 0))
        {
            printf("\nGoodBye!!");
            break;
        }

        if (searchMemory(input, response) == 1)
        {
            printf("cBot: %s", response);
        }

        if(searchMemory(input, response) == 0)
        {
            printf("cBot: Looks like i dont know the answer to that, teach it to me below!");
            printf("\nYou: ");
            fgets(response, sizeof(response), stdin);

            saveMemory(input, response);
            printf("\ncBot: Good! Ill remeber that");
        }

    }

    return 0;
}