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
}

// Trabajando para lo demás...

