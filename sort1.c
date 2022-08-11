#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>


int Amount (FILE *, int *);
void brain_sort (void (*pr) (char *, char *, int *), char * [], int, int *);
void traid12 (char *, char *, int *);
void record (FILE *, char * [], int);

int i, j;

int main () {

  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);

  FILE * fp;

  if ((fp = fopen ("sort.txt", "r")) == NULL) {

    puts ("Problem opening file");
    exit (EXIT_FAILURE);

  }

  puts ("File opened!");

  char ch;
  int len = 0;
  int amount = Amount (fp, &len);

  void ( * pr) (char *, char *, int *);
  pr = traid12;

  int j = 0;
  unsigned long long lim = 0;
  char str[amount][len];
  char * pt[amount];

  for (i = 0; i < amount; i++) {

    j = 0;
    fseek (fp, lim, SEEK_SET);

    while ((ch = getc (fp)) != EOF) {

      * (* (str + i) + j) = ch;
      pt[i] = * (str + i);

      if (ch == '\n') {

        * (* (str + i) + j) = '\0';
        break;

      }

      j++;
      lim++;

    }

    lim += 2;

  }

  brain_sort (pr, pt, amount, &len);

  fclose (fp);

  FILE * rec;
  if ((rec = fopen ("recordSort.txt", "a")) == NULL) {

    puts ("File for record not found!");
    exit (EXIT_FAILURE);

  }

  record (rec, pt, amount);
  fclose (rec);

  puts ("Input SORT in console: ");
  putchar ('\n');

  for (i = 0; i < amount; i++)
    puts (str[i]);

  return 0;

}

void traid12 (char * str1, char * str2, int * len) {

  char str3[*len];
  strcpy (str3, str1);
  strcpy (str1, str2);
  strcpy (str2, str3);

}

int Amount (FILE * fp, int * maxLength) {

  char ch;
  int amount = 0, max = -1, i = 0;

  while ((ch = getc(fp)) != EOF) {

    i++;

    if (ch == '\n') {

      amount++;

      if (i >= max)
        max = i;

      i = 0;

    }

  }


  * maxLength = max;

  return amount;

}

void brain_sort (void (*fp)(char *, char *, int *), char * str[], int amount, int * len) {

  int i = 0, j = 0;

  for (i = 0; i < amount; i++) {

    for (j = 0; j < amount; j++) {

      if (str[i] == "\0" || str[j] == "\0")
        continue;

      if (strcmp(str[i], str[j]) == -1)
        traid12 (str[i], str[j], len);

    }

  }

}

void record (FILE * fp, char * str[], int amount) {

  for (i = 0; i < amount; i++) {

    fwrite (str[i], sizeof (char), strlen (str[i]), fp);
    putc ('\n', fp);

  }

}