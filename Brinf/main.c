#include "brinf.h"

int main(void)
{
    unsigned option = 1;
    Browser Browser;
    if (GetWindowsDefaultBrowser(&Browser) == EXIT_SUCCESS)
    {
        do
        {
            system("cls");
            DisplayBroswerInfo(Browser);
            DisplayOptions();
            option = GetOption();

            if(option == 1)
                GetMostVisitedPages(Browser);
            system("PAUSE");
          
        } while (option > 0 && option < 5);
    }
    return 0;
}
