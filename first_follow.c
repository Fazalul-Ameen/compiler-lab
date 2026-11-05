#include <stdio.h>
#include <string.h>

#define MAX 20
#define LEN 20

char lhs[MAX];
char rhs[MAX][LEN];
int n;

int first[26][128];
int follow[26][128];

int add(int set[26][128], char nt, char symbol)
{
    int x = nt - 'A';
    unsigned char s = (unsigned char)symbol;

    if (!set[x][s])
    {
        set[x][s] = 1;
        return 1;
    }

    return 0;
}

int isNonTerminal(char c)
{
    return c >= 'A' && c <= 'Z';
}

void calculateFirst(void)
{
    int changed;

    do
    {
        changed = 0;

        for (int p = 0; p < n; p++)
        {
            char A = lhs[p];
            char *r = rhs[p];
            int nullable = 1;

            if (strcmp(r, "#") == 0)
            {
                changed |= add(first, A, '#');
                continue;
            }

            for (int i = 0; r[i] != '\0'; i++)
            {
                char X = r[i];

                if (!isNonTerminal(X))
                {
                    changed |= add(first, A, X);
                    nullable = 0;
                    break;
                }

                for (int c = 0; c < 128; c++)
                {
                    if (c != '#' && first[X - 'A'][c])
                    {
                        changed |= add(first, A, (char)c);
                    }
                }

                if (!first[X - 'A']['#'])
                {
                    nullable = 0;
                    break;
                }
            }

            if (nullable)
            {
                changed |= add(first, A, '#');
            }
        }

    } while (changed);
}

void calculateFollow(char start)
{
    int changed;

    add(follow, start, '$');

    do
    {
        changed = 0;

        for (int p = 0; p < n; p++)
        {
            char A = lhs[p];
            char *r = rhs[p];

            for (int i = 0; r[i] != '\0'; i++)
            {
                char B = r[i];

                if (!isNonTerminal(B))
                {
                    continue;
                }

                int nullable = 1;

                for (int j = i + 1; r[j] != '\0'; j++)
                {
                    char X = r[j];

                    if (!isNonTerminal(X))
                    {
                        changed |= add(follow, B, X);
                        nullable = 0;
                        break;
                    }

                    for (int c = 0; c < 128; c++)
                    {
                        if (c != '#' && first[X - 'A'][c])
                        {
                            changed |= add(follow, B, (char)c);
                        }
                    }

                    if (!first[X - 'A']['#'])
                    {
                        nullable = 0;
                        break;
                    }
                }

                if (nullable)
                {
                    for (int c = 0; c < 128; c++)
                    {
                        if (follow[A - 'A'][c])
                        {
                            changed |= add(follow, B, (char)c);
                        }
                    }
                }
            }
        }

    } while (changed);
}

void printSet(const char *name, int set[26][128], char nt)
{
    printf("%s(%c) = { ", name, nt);

    for (int c = 0; c < 128; c++)
    {
        if (set[nt - 'A'][c])
        {
            printf("%c ", c);
        }
    }

    printf("}\n");
}

int main(void)
{
    char start;

    printf("Enter number of productions: ");

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX)
    {
        printf("Invalid number of productions.\n");
        return 1;
    }

    printf("Enter each production as: LHS RHS\n");
    printf("Use # for epsilon. Example: A #\n");

    for (int i = 0; i < n; i++)
    {
        printf("Production %d: ", i + 1);
        fflush(stdout);

        if (scanf(" %c %19s", &lhs[i], rhs[i]) != 2 ||
            !isNonTerminal(lhs[i]))
        {
            printf("Invalid production.\n");
            return 1;
        }
    }

    start = lhs[0];

    calculateFirst();
    calculateFollow(start);

    printf("\nFIRST sets:\n");

    for (int i = 0; i < n; i++)
    {
        int alreadyPrinted = 0;

        for (int j = 0; j < i; j++)
        {
            if (lhs[i] == lhs[j])
            {
                alreadyPrinted = 1;
                break;
            }
        }

        if (!alreadyPrinted)
        {
            printSet("FIRST", first, lhs[i]);
        }
    }

    printf("\nFOLLOW sets:\n");

    for (int i = 0; i < n; i++)
    {
        int alreadyPrinted = 0;

        for (int j = 0; j < i; j++)
        {
            if (lhs[i] == lhs[j])
            {
                alreadyPrinted = 1;
                break;
            }
        }

        if (!alreadyPrinted)
        {
            printSet("FOLLOW", follow, lhs[i]);
        }
    }

    return 0;
}