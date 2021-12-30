#ifndef TABS_H_INCLUDED
#define TABS_H_INCLUDED

typedef struct {
    char name[256];
    int occupied;
} STab;

class cTab
{
STab Tabs[256];
public:
    int newTab(char* name);
};

extern cTab tab;

#endif // TABS_H_INCLUDED
