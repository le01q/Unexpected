#include "brinf.h"

const char BrowserProgId[_MAX_BROWSER_PROGID][_MAX_FNAME] =
{
    "None",
    "Edge",
    "Firefox",
    "Chrome",
    "Yandex"
}, BrowserName[_MAX_BROWSERS][_MAX_FNAME] =
{
    "None",
    "Microsoft Edge",
    "Mozilla Firefox",
    "Google Chrome",
    "Yandex Browser"
};


/*
MSEdgeHTML
FirefoxURL
ChromeHTML
*/

void Notification(char *Type, char *Message)
{
    printf("[%s] %s\n", Type, Message);
    return;
}

unsigned GetBrowserPath(unsigned BrowserId)
{
    return EXIT_SUCCESS;
}

unsigned GetWindowsDefaultBrowser(Browser *BrowserInfo)
{
    HKEY Key;
    char Data[_MAX_BROWSER_NAME] = {0}, DataPath[_MAX_PATH] = {0};
    DWORD DataSize = 0;
    BrowserInfo->id = -1;

    if (RegOpenKeyEx(HKEY_CURRENT_USER, REG_PATH, 0, KEY_QUERY_VALUE, &Key) != ERROR_SUCCESS)
    {
        Notification("Error", "Can't get the default browser.");
        RegCloseKey(Key);
        return EXIT_FAILURE;
    }

    DataSize = ARRAYSIZE(Data) * sizeof(Data[0]);
    if (RegQueryValueEx(Key, TEXT("Progid"), 0, 0, (LPBYTE)&Data, &DataSize) != ERROR_SUCCESS)
    {
        Notification("Error", "Can't get the program id.");
        RegCloseKey(Key);
        return EXIT_FAILURE;
    }
    RegCloseKey(Key);

    for (size_t i = 0; i < _MAX_BROWSERS; i++)
    {
        if (strstr(Data, BrowserProgId[i]))
        {
            BrowserInfo->id = i;
            strcpy(BrowserInfo->name, BrowserName[i]);
            printf("Detected %s (%d)!", BrowserInfo->name, BrowserInfo->id);
        }
    }

    if(BrowserInfo->id == -1)
        Notification("Error", "Browser not found.");
    
    return EXIT_SUCCESS;
}
