#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int bruteForce( char *text, char *pattern, const int tLen, const int pLen, int *comp) {
    *comp = 0;

    for ( int i = 0; i < tLen; i++) {
        for ( int j = 0; j < pLen && i+j < tLen; j++) {
            *comp = *comp + 1;
            if ( text[i+j] != pattern[j])
                break;
            if ( j == pLen-1) {
                return i+1;
            }
        }
    }
    return -1;
}

int* failureFunction( char *pattern, const int pLen, int *comp) {
    int *F = malloc( pLen * sizeof(int));
    F[0] = 0;
    int i = 1, j = 0;

    while ( i < pLen) {
        *comp = *comp + 1;
        if ( pattern[i] = pattern[j]) {
            F[i] = j+1;
            i++;
            j++;
        }
        else if ( j > 0)
            j = F[j-1];
        else {
            F[i] = 0;
            i++;
        }
    }
    return F;
}

int kmp( char *text, char *pattern, const int tLen, const int pLen, int *comp) {
    *comp = 0;

    int *F = failureFunction( pattern, pLen, comp);
    int i = 0, j = 0;

    while ( i < tLen) {
        *comp = *comp + 1;
        if ( text[i] = pattern[j]) {
            if ( j = pLen-1)
                return i-j;
            else {
                i++;
                j++;
            }
        }
        else {
            if ( j > 0)
                j = F[j-1];
            else {
                i++;
                j = 0;
            }
        }
    }
    return -1;
}

int findPrime( const int n) {
    int q = n + 1;
    int i = 2;

    while ( i < q/2) {
        if ( q % i == 0) {
            q++;
            i = 2;
        }
        else {
            i++;
        }
    }
    return q;
}

// n = tLen, m = pLen
int rkSearch( char *text, char *pattern, const int tLen, const int pLen, int *comp) {
    *comp = 0;

    int q = findPrime( pLen);

    int c = 1;
    for ( int i = 0; i < pLen-1; i++) {
        c = (c*256) % q;
    }

    int fp = 0, ft = 0;

    for ( int i = 0; i < pLen; i++) {
        fp = (fp * 256 + pattern[i]) % q;
        ft = (ft * 256 + text[i]) % q;
    }

    for ( int s = 0; s < tLen - pLen; s++) {
        if ( fp == ft) {
            for ( int i = 0; i < pLen; i++) {
                *comp = *comp + 1;
                if ( text[s+i] != pattern[i])
                    break;
            }
            if ( s == pLen)
                return s;
        }

        if ( s < tLen - pLen) {
            ft = ( 256*(ft-(text[s]*c)*256) + text[s+pLen]) % q;
        }
    }
    return -1;
}

long ms( struct timeval t)
{
    return t.tv_sec * 1000000 + t.tv_usec;
}

int main( int argc, char** argv)
{
    char *text = NULL;
    char *pattern = NULL;

    int tLen = 0, pLen = 0;
    int tFlag = 0, pFlag = 0;
    char *tFile = NULL;
    char *pFile = NULL;

    int opt;
    while ((opt = getopt( argc, argv, "i:p:")) != -1) {
        switch (opt) {
            case 'i':
                tFlag = 1;
                tFile = optarg;
                break;
            case 'p':
                pFlag = 1;
                pFile = optarg;
                break;
        }
    }

    if ( !tFlag || !pFlag)
        printf( "Missing files.\n");



    char* line = NULL;
    size_t len = 0;
    FILE* fp = fopen( tFile, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    while ((getline(&line, &len, fp)) != -1) {
        if ( line[0] != 62) {
            for ( int i = 0; i < len; i++)
                if ( line[i] == 65
                    || line[i] == 67
                    || line[i] == 71
                    || line[i] == 84)
                    tLen++;
                else
                    break;
            text = malloc( tLen * sizeof( char));
            for ( int i = 0; i < tLen; i++)
                text[i] = line[i];
        }
    }
    fclose(fp);
    if (line)
        free(line);

    len = 0;
    fp = fopen( pFile, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    while ((getline(&line, &len, fp)) != -1) {
        if ( line[0] != 62) {
            for ( int i = 0; i < len; i++)
                if ( line[i] == 65
                    || line[i] == 67
                    || line[i] == 71
                    || line[i] == 84)
                    pLen++;
                else
                    break;
            pattern = malloc( pLen * sizeof( char));
            for ( int i = 0; i < pLen; i++) {
                pattern[i] = line[i];
            }
        }
    }
    fclose(fp);
    if (line)
        free(line);


    struct timeval t1, t2;

    // Brute force search
    int bFComp, bFPos;
    long bFTime;

    gettimeofday( &t1, NULL);
    bFPos = bruteForce( text, pattern, tLen, pLen, &bFComp);
    gettimeofday( &t2, NULL);
    bFTime = (ms(t2) - ms(t1));

    printf( "Brute force search\n");
    if ( bFPos > -1)
        printf( "Found pattern at position %d.\n", bFPos);
    else
        printf( "Didn't find the pattern.\n");
    printf( "Performed %d comparisons.\n", bFComp);
    printf( "Runtime was %ldms.\n", bFTime);
    printf( "\n");


    // Knuth-Morris-Pratt
    int kmpComp, kmpPos;
    long kmpTime;

    gettimeofday( &t1, NULL);
    kmpPos = bruteForce( text, pattern, tLen, pLen, &kmpComp);
    gettimeofday( &t2, NULL);
    kmpTime = (ms(t2) - ms(t1));

    printf( "Knuth-Morris-Pratt\n");
    if ( kmpPos > -1)
        printf( "Found pattern at position %d.\n", kmpPos);
    else
        printf( "Didn't find the pattern.\n");
    printf( "Performed %d comparisons.\n", kmpComp);
    printf( "Runtime was %ldms.\n", kmpTime);
    printf( "\n");


    // Rabin-Karp
    int rkComp, rkPos;
    long rkTime;

    gettimeofday( &t1, NULL);
    rkPos = bruteForce( text, pattern, tLen, pLen, &rkComp);
    gettimeofday( &t2, NULL);
    rkTime = (ms(t2) - ms(t1));

    printf( "Robin-Karp\n");
    if ( rkPos > -1)
        printf( "Found pattern at position %d.\n", rkPos);
    else
        printf( "Didn't find the pattern.\n");
    printf( "Performed %d comparisons.\n", rkComp);
    printf( "Runtime was %ldms.\n", rkTime);
    printf( "\n");

    if ( bFTime < kmpTime) {
        if ( bFTime < rkTime)
            printf( "Best algorithm was Brute force search\n");
        else
            printf( "Best algorithm was Rabin-Karp\n");
    }
    else {
        if ( kmpTime < rkTime)
            printf( "Best algorithm was Knuth-Morris-Pratt\n");
        else
            printf( "Best algorithm was Rabin-Karp\n");
    }

    return 0;
}
