#include "brinf.h"

const char BrowserProgId[_MAX_BROWSER_PROGID][_MAX_FNAME] =
    {"None", "Edge", "Firefox", "Chrome", "Yandex"};

const char BrowserName[_MAX_BROWSERS][_MAX_FNAME] =
    {"None", "Microsoft Edge", "Mozilla Firefox", "Google Chrome", "Yandex Browser"};

const char BrowserRegPath[_MAX_BROWSERS][_MAX_PATH] =
    {
        "None",
        "SOFTWARE\\Microsoft\\Edge\\BLBeacon",
        "SOFTWARE\\Mozilla\\Mozilla Firefox",
        "SOFTWARE\\Google\\Chrome\\BLBeacon",
        "SOFTWARE\\Yandex\\YandexBrowser\\BLBeacon"};

const char BrowserLocalPath[_MAX_BROWSERS][_MAX_PATH] =
    {
        "None",
        "",
        "",
        "\\Google\\Chrome\\User Data\\Default",
        "\\Yandex\\YandexBrowser\\User Data\\Default"};

int existf(char *path)
{
    struct stat info;
    return stat(path, &info) != 0;
}

void Notification(char *Type, char *Message)
{
    printf("[%s] %s\n", Type, Message);
    return;
}

unsigned GetOption(void)
{
    unsigned option;
    scanf("%d", &option);
    return option;
}

void DisplayOptions(void)
{
    puts("1. Most visited pages");
}

unsigned GetMostVisitedPages(Browser BrowserInfo)
{
    sqlite3 *database;
    sqlite3_stmt *stmt;
    char file_path[_MAX_PATH];
    char cmd[_MAX_PATH];
    
    snprintf(file_path, sizeof file_path, "%s\\History", getenv("TEMP"));

    if (existf(file_path) != 1)
    {
        printf("> Found history file, removing..\n");
        snprintf(cmd, sizeof cmd, "del %s", file_path);
    }

    printf("> Copying history file into temp..\n");
    snprintf(file_path, sizeof file_path, "%s\\History", BrowserInfo.path);
    snprintf(cmd, sizeof cmd, "copy \"%s\" %s", file_path, getenv("TEMP"));
    system(cmd);
    Sleep(500);

    snprintf(file_path, sizeof file_path, "%s\\History", getenv("TEMP"));

    if (sqlite3_open(file_path, &database))
    {
        sqlite3_close(database);
        Notification("Error", "Can't open the history database.");
        return EXIT_FAILURE;
    }
    if (sqlite3_prepare_v2(database, "SELECT title, visit_count from urls order by visit_count DESC LIMIT 5", -1, &stmt, NULL))
    {
        sqlite3_close(database);
        Notification("Error", "Can't execute select query.");
        return EXIT_FAILURE;
    }

    printf("\nMost visited pages:\n");

    while (sqlite3_step(stmt) != SQLITE_DONE)
    {
        int i, num_cols = sqlite3_column_count(stmt);
        for (i = 0; i < num_cols; i++)
        {
            switch (sqlite3_column_type(stmt, i))
            {
            case (SQLITE3_TEXT):
                printf("> %s", sqlite3_column_text(stmt, i));
                break;
            case (SQLITE_INTEGER):
                printf(" with %d visits\n", sqlite3_column_int(stmt, i));
                break;
            default:
                break;
            }
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(database);
    return EXIT_SUCCESS;
}

void DisplayBroswerInfo(Browser BrowserInfo)
{
    printf("Your current default browser is %s, version %s (%d)\n", BrowserInfo.name, BrowserInfo.version, BrowserInfo.id);
    printf("Location: %s\n", BrowserInfo.path);
    return;
}

unsigned GetBrowserPath(unsigned BrowserId, char (*BrowserPath)[_MAX_PATH])
{
    char path[_MAX_PATH] = {0};
    snprintf(path, sizeof path, "%s%s", getenv("LOCALAPPDATA"), BrowserLocalPath[BrowserId]);
    strcpy(*BrowserPath, path);
    return EXIT_SUCCESS;
}

unsigned GetBrowserVersion(unsigned BrowserId, char (*BrowserVersion)[_MAX_BROWSER_VERSION])
{
    HKEY Key;
    char SubKey[24];
    char Data[_MAX_BROWSER_VERSION] = {0};
    DWORD DataSize = 0;

    if (BrowserId == MOZILLA_BROWSER)
        strcpy(SubKey, "CurrentVersion");
    else
        strcpy(SubKey, "version");

    if (RegOpenKeyEx(HKEY_CURRENT_USER, BrowserRegPath[BrowserId], 0, KEY_QUERY_VALUE, &Key) != ERROR_SUCCESS)
    {
        Notification("Error", "Can't open browser key.");
        RegCloseKey(Key);
        return EXIT_FAILURE;
    }

    DataSize = ARRAYSIZE(Data) * sizeof(Data[0]);
    if (RegQueryValueEx(Key, SubKey, 0, 0, (LPBYTE)&Data, &DataSize) != ERROR_SUCCESS)
    {
        Notification("Error", "Can't get browser version.");
        RegCloseKey(Key);
        return EXIT_FAILURE;
    }
    RegCloseKey(Key);

    strcpy(*BrowserVersion, Data);
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
            GetBrowserVersion(BrowserInfo->id, &(BrowserInfo->version));
            GetBrowserPath(BrowserInfo->id, &(BrowserInfo->path));
        }
    }

    if (BrowserInfo->id == -1)
        Notification("Error", "Browser not found.");

    return EXIT_SUCCESS;
}
