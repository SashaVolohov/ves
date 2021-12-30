#include "tab.h"
#include <windows.h>
#include <iostream>

int cTab::newTab(char *name)
{
    for(int i = 0; i < 256; i++)
    {
        if(tab.Tabs[i].occupied == FALSE)
        {
            tab.Tabs[i].occupied = true;
            sprintf(tab.Tabs[i].name, "%s", name);
            return i;
        }
    }
    return -1;
}
