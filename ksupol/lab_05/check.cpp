#include "check.h"
#include <QString>

int check_point(QString a)
{
    if (a[0] != '-' && (a[0] > '9' || a[0] < '0'))
        return -1;
    int flag = 0;
    for (int i = 1; i < a.length(); i++)
    {
        if (a[i] == '.' && flag == 0)
            flag = 1;
        else if (a[i] == '.' && flag != 0)
            return -1;
        else if (a[i] < '0' || a[i] > '9')
            return -1;

    }
    if (a[a.length() - 1] == '.')
        return -1;
    return 0;
}
