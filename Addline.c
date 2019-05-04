#include <ElementType.h>
#include <stdio.h>
#include <dirent.h>
#include <Status.h>
#include <stdbool.h>
#include <string.h>
char *getsuffix(char *s)
{
    int i = 0;
    int dot = 0;
    for (i = 0, dot = 0; s[i] != '\0'; i++)
    {
        if (s[i] == '.')
            dot = i;
    }
    return s + dot;
}
#define maxsuffixnum 10
static int suffixesnum = 0;
static char *suffixes[maxsuffixnum];
void readoption()
{
    printf("which type of sources do you want to count?(end input with an extra 'Y')\n");
    char *s;
    while (scanf("%s", s) != 0)
    {
        if (strcmp(s, "Y") == 0)
            break;
        if (suffixesnum == maxsuffixnum)
        {
            printf("you had inputed max num allowed\n");
            break;
        }
        suffixes[suffixesnum]=MALLOC(sizeof(char),strlen(s),"");
        strcpy(suffixes[suffixesnum],s);
        suffixesnum++;
    }
    printf("we will count these types of sources:");
    for(int i=0;i<suffixesnum;i++)
    printf("\t%s",suffixes[i]);
    printf("\n");
}
bool checki(char *suffix, int i, bool *rights, int *rightnum)
{
    for (int j = 0; j < suffixesnum; j++)
    {
        if (rights[j] == true)
        {
            continue;
        }
        else
        {
            if ((suffixes[j][i] != suffix[i]) || (suffix[i] != '\0' && suffixes[j][i] == '\0'))
            {
                (*rightnum)--;
                rights[j] = true;
                if (*rightnum == 0)
                {
                    return false;
                }
            }
        }
    }
    return true;
}
bool checksuffix(char *s)
{
    char *suffix = getsuffix(s);
    bool *rights = MALLOC(sizeof(bool), suffixesnum, "");
    int rightnum = suffixesnum;
    for (int i = 0; i < suffixesnum; i++)
        rights[i] = false;
    int i = 0;
    for (i = 0; suffix[i] != '\0'; i++)
    {
        if (!checki(suffix, i, rights, &rightnum))
            return false;
    }
    return checki(suffix, i, rights, &rightnum);
}

int countline(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f)
        EXIT(ERROR, "open file failed");
    int sum = 1;
    char c;
    while ((c = fgetc(f)) != EOF)
    {
        /* code */
        if (c == '\n')
            sum++;
    }
    fclose(f);
    printf("%s\t\t\t\t%d\n", filename, sum);
    return sum;
}
char *connectname(char *name, char *name1, char *name2)
{
    name[0] = '\0';
    strcpy(name, name1);
    strcat(name, "/");
    strcat(name, name2);
}
int countdir(char *foldername)
{

    DIR *mydir = opendir(foldername);
    if (!mydir)
        EXIT(ERROR, "open folder failed");
    struct dirent *di;
    int sum = 0;
    char *name = MALLOC(sizeof(char), 255, "");
    while ((di = readdir(mydir)) != NULL)
    {
        /* code */
        switch (di->d_type)
        {
        case DT_REG:
            /* code */
            if (checksuffix(di->d_name))
            {
                sum += countline(connectname(name, foldername, di->d_name));
            }
            break;
        case DT_DIR:
            /* code */
            if (strcmp(di->d_name, ".") != 0 && strcmp(di->d_name, "..") != 0)
            {
                sum += countdir(connectname(name, foldername, di->d_name));
            }
            break;
        default:
            break;
        }
    }
    return sum;
}
int main(void)
{
    printf("WELCOME TO COUNT YOUR CODE\n");
    readoption();
    printf("push enter to start counting\n");
    fflush(stdin);
    getchar();
    char *foldername = "./";
    int sum = countdir(foldername);
    printf("\nHI GUY, YOU HAD TOTALLY WRITEN  %d  LINES OF CODE", sum);
    getchar();
}