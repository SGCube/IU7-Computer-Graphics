#include "check.h"

int checkPoint(QString a)
{
    if (a[0] != '-' && (a[0] > '9' || a[0] < '0'))
        return -1;
    int i = 1;
    while (a[i] != '\0')
    {
        if (a[i] > '9' || a[i] < '0')
            return -1;
        i++;
    }
    return 0;
}
