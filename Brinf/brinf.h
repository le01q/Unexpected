#ifndef BRINF_H_INCLUDED
#define BRINF_H_INCLUDED

// Browser Information aka Brinf by ne0de

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define REG_PATH "Software\\Microsoft\\Windows\\Shell\\Associations\\UrlAssociations\\http\\UserChoice"

// Browsers
#define EDGE_BROWSER 1
#define MOZILLA_BROWSER 2
#define CHROME_BROWSER 3
#define YANDEX_BRROWSER 4
#define BRAVE_BROWSER 5
#define OPERA_BROWSER 6
#define OPERA_GX_BROWSER 7
#define SAFARI_BROWSER 8

#define _MAX_BROWSERS 5
#define _MAX_BROWSER_PROGID 24
#define _MAX_BROWSER_NAME 1024

typedef struct Browser
{
    unsigned id;
    char name[_MAX_BROWSER_NAME];
    char path[_MAX_PATH];
} Browser;

void Notification(char *Type, char *Message);
unsigned GetBrowserPath(unsigned BrowserId);
unsigned GetWindowsDefaultBrowser(Browser *);

#endif // BRINF_H_INCLUDED
