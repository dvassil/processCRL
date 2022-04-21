/*
 * Prerequired actions:
 *      curl http://crl.ermis.gov.gr/HPARCASign/LatestCRL.crl --output certificate_list.crl 2>/dev/null
 *      openssl crl -inform DER -noout -text -in certificate_list.crl -out certificate_list.txt
 * Usage:
 *      process < certificate_list.txt > certificate_list.csv
 *
 */

#define _CRT_SECURE_NO_WARNINGS
#define _OPEN_SYS_ITOA_EXT

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>


#include <sys/types.h> /* unistd.h needs this */
#ifndef _WIN32
//#include <sys/time.h>
#include <unistd.h>    /* contains read/write */

//#define INPUT_FILENAME "/tmp/private.crl.txt"

extern char* strptime(const char* __restrict __s, const char* __restrict __fmt, struct tm* __tp);

#else

#include <errno.h>
#include <io.h>

#define R_OK    4       /* Test for read permission.  */
#define W_OK    2       /* Test for write permission.  */
#define X_OK    1       /* execute permission - unsupported in windows*/
#define F_OK    0       /* Test for existence.  */

#define access _access

//#define INPUT_FILENAME "D:\\tmp\\private.crl.txt"

extern char* strptime(const char* __restrict __s, const char* __restrict __fmt, struct tm* __tp);
//extern char* strptime(const char* buf, const char* format, struct tm* tm);

#endif
#include <fcntl.h>

#include "index.h"
#include "ltoa.h"

#include <ctype.h>

#define MAX_LINE_LEN        (1024)
#define SKIP_LINES          (8)
#define SERIAL_NUMBER       "    Serial Number: "
#define REVOCATION_DATE     "        Revocation Date: "
#define SIGNATURE_ALGORITHM "Signature Algorithm:"

bool file_exists(char* filename);

/*
*/

char line[MAX_LINE_LEN << 1] = "\0";
char buffer[MAX_LINE_LEN] = "\0";

int main()
{
    int SERIAL_NUMBER_LEN = (sizeof(SERIAL_NUMBER) - 1);
    int REVOCATION_DATE_LEN = (sizeof(REVOCATION_DATE) - 1);

    char* pch = NULL;
    //char* in_filename = INPUT_FILENAME;

    long read = 0, written = 0;
    //char* pch2 = NULL;

    if (true /* file_exists(in_filename) */)
    {

        FILE* fin = NULL;
        //fin = fopen(in_filename, "r");
        fin = stdin;
        if (true /* fin */)
        {
            read = 0;
            bool isfirst = true;
            //pch = fgets(buffer, MAX_LINE_LEN, fin);

            while (!feof(fin) && (read < SKIP_LINES))
            {
                read++;
                pch = fgets(buffer, MAX_LINE_LEN, fin);
            }

            while (!feof(fin) && strstr(buffer, SIGNATURE_ALGORITHM)==NULL)
            {
                size_t linelen = strlen(pch);

                if (isfirst)
                {
                    written++;
                    WRITE(ltoa(written, line, 10));
                    WRITE(",\"");
                    pch[linelen - 1] = '\0';
                    WRITE(pch + SERIAL_NUMBER_LEN);
                    WRITE("\",");

                    // pch[linelen - 1] = '\0';
                    // sprintf(line, "%ld,\"%s\",", written, pch + SERIAL_NUMBER_LEN);
                    // linelen = strlen(line);
                    // pch2 = line + linelen;
                    // printf("%ld,\"%s\",", written, pch + SERIAL_NUMBER_LEN);
                    //pch2 = line;
                }
                else
                {
                    char* pch3;
                    pch3 = pch + REVOCATION_DATE_LEN;
                    //strncpy(pch2, pch3, linelen - REVOCATION_DATE_LEN);

                    struct tm tmtime;
                    //pch3 = strptime(pch2, "%b %d %T %Y %Z", &tmtime);
                    pch3 = strptime(pch3, "%b %d %T %Y %Z", &tmtime);
                    if (pch3) {
                        // "YYYY-MM-DD HH:MM:SS"
                        // strftime(pch2, 23, "\"%Y-%m-%d %X\"\n\0", &tmtime);
                        strftime(pch3, 23, "\"%Y-%m-%d %X\"\n\0", &tmtime);
                    }

                    // WRITE(line);
                    WRITE(pch3);
                }

                isfirst = !isfirst;

                read++;
                pch = fgets(buffer, MAX_LINE_LEN, fin);
            }

            fclose(fin);
        }
        // else {
        //     // WRITE("Cannot read ");
        //     // WRITELN(in_filename);
        // }
    }
    // else {
    //     // WRITE(in_filename);
    //     // WRITE(" does not exist.\n");
    // }


    /*
        data = getenv("HTTP_X_WDE");
        if (data != NULL)
        {
            WRITE(data);
        }
    */

    return 0;
}

bool file_exists(char* filename)
{
    return (access(filename, F_OK) == 0);
}
