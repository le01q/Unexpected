#ifndef BRINF_H_INCLUDED
#define BRINF_H_INCLUDED

// Browser Information aka Brinf by ne0de

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <sys/stat.h>
#include "utils/sqlite3.h"

#define REG_PATH "Software\\Microsoft\\Windows\\Shell\\Associations\\UrlAssociations\\http\\UserChoice"
#define REG_BROWSER_PATH "SOFTWARE\\"

// Browsers
#define EDGE_BROWSER 1
#define MOZILLA_BROWSER 2
#define CHROME_BROWSER 3
#define YANDEX_BROWSER 4
#define BRAVE_BROWSER 5
#define OPERA_BROWSER 6
#define OPERA_GX_BROWSER 7
#define SAFARI_BROWSER 8

#define _MAX_BROWSERS 5
#define _MAX_BROWSER_PROGID 24
#define _MAX_BROWSER_NAME 1024
#define _MAX_BROWSER_VERSION 16

typedef struct Browser
{
    unsigned id;
    char name[_MAX_BROWSER_NAME];
    char path[_MAX_PATH];
    char version[_MAX_BROWSER_VERSION];
} Browser;

int existf(char *path);
void Notification(char *Type, char *Message);
unsigned GetOption(void);
void DisplayOptions(void);
void DisplayBroswerInfo(Browser);
unsigned GetMostVisitedPages(Browser BrowserInfo);
unsigned GetBrowserPath(unsigned BrowserId, char (*BrowserPath)[_MAX_PATH]);
unsigned GetBrowserVersion(unsigned BrowserId, char (*BrowserVersion)[_MAX_BROWSER_VERSION]);
unsigned GetWindowsDefaultBrowser(Browser *);

#endif // BRINF_H_INCLUDED
