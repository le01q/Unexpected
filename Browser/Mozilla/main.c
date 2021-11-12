#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/sqlite3.h"

#define _MAX_BUFFER 256
#define OUTPUT_FILE "webs.csv"
#define MOZ_PROFILE_PATH "\\Mozilla\\Firefox\\Profiles\\"
#define MOZ_PROFILE_TOKEN "default-release"
#define MOZ_WEB_VISITS_FILE "places.sqlite"

int main()
{
    sqlite3 *database;
    sqlite3_stmt *stmt;
    char query[256];
    char path[_MAX_PATH], tmp_path[_MAX_PATH], cmd[_MAX_PATH], buffer[_MAX_BUFFER], profile_folder[_MAX_FNAME];

    snprintf(tmp_path, sizeof tmp_path, "%s", getenv("TEMP"));
    snprintf(path, sizeof path, "%s%s", getenv("APPDATA"), MOZ_PROFILE_PATH);
    snprintf(cmd, sizeof cmd, "dir /d /b %s", path);

    FILE *output = popen(cmd, "r");
    while (fgets(buffer, sizeof buffer, output) != 0)
    {
        if (strstr(buffer, MOZ_PROFILE_TOKEN))
        {
            size_t i = 0;
            while (buffer[i++] != '\0')
                if (buffer[i] == '\n')
                    buffer[i] = 0;
            strcpy(profile_folder, buffer);
        }
    }
    fclose(output);

    snprintf(path, sizeof path, "%s%s%s\\%s", getenv("APPDATA"), MOZ_PROFILE_PATH, profile_folder, MOZ_WEB_VISITS_FILE);
    snprintf(cmd, sizeof cmd, "copy %s %s", path, tmp_path);
    snprintf(path, sizeof path, "%s\\%s", tmp_path, MOZ_WEB_VISITS_FILE);
    system(cmd);

    if (sqlite3_open(path, &database))
    {
        sqlite3_close(database);
        return EXIT_FAILURE;
    }

    if (sqlite3_prepare_v2(database, "SELECT url, visit_count from moz_places", -1, &stmt, NULL))
    {
        sqlite3_close(database);
        return EXIT_FAILURE;
    }

    while (sqlite3_step(stmt) != SQLITE_DONE)
    {
        int i, num_cols = sqlite3_column_count(stmt);
        FILE *out = fopen(OUTPUT_FILE, "a+");
        if (out)
        {
            for (i = 0; i < num_cols; i++)
            {
                switch (sqlite3_column_type(stmt, i))
                {
                case (SQLITE3_TEXT):
                    fprintf(out, "%s,", sqlite3_column_text(stmt, i));
                    break;
                case (SQLITE_INTEGER):
                    fprintf(out, "%d\n", sqlite3_column_int(stmt, i));
                    break;
                default:
                    break;
                }
            }
            fclose(out);
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(database);
    return 0;
}
