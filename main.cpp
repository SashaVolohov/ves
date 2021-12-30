#include <tchar.h>
#include <windows.h>
#include <commctrl.h>
#include "tab.h"

cTab tab;

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
TCHAR szClassName[] = _T("VECApp");
TC_ITEM tItem;

void MenuInit(HWND hwnd)
{
    HMENU RootMenu = CreateMenu();
    HMENU SubMenuFile = CreateMenu();
    HMENU SubMenuEdit = CreateMenu();
    HMENU SubMenuHelp = CreateMenu();

    AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenuFile, "Файл");
    AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenuEdit, "Правка");
    AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenuHelp, "Справка");

    AppendMenu(SubMenuFile, MF_STRING, 4, "Создать");
    AppendMenu(SubMenuFile, MF_STRING, 5, "Открыть...");
    AppendMenu(SubMenuFile, MF_STRING, 6, "Сохранить");
    AppendMenu(SubMenuFile, MF_STRING, 7, "Сохранить как...");
    AppendMenu(SubMenuFile, MF_SEPARATOR, NULL, NULL);
    AppendMenu(SubMenuFile, MF_STRING, 8, "Выход");

    AppendMenu(SubMenuEdit, MF_STRING, 9, "Отменить");
    AppendMenu(SubMenuEdit, MF_STRING, 10, "Повторить");
    AppendMenu(SubMenuEdit, MF_SEPARATOR, NULL, NULL);
    AppendMenu(SubMenuEdit, MF_STRING, 11, "Изменить параметр...");

    AppendMenu(SubMenuHelp, MF_STRING, 12, "Посмотреть справку");
    AppendMenu(SubMenuHelp, MF_SEPARATOR, NULL, NULL);
    AppendMenu(SubMenuHelp, MF_STRING, 13, "О программе...");

    SetMenu(hwnd, RootMenu);
}

void AddNewUnitToTabControl(char* text, HWND hwnd_tab_control, int id)
{
    tItem.pszText = text;
    SendMessage(hwnd_tab_control, TCM_INSERTITEM, id, LPARAM(&tItem));
}

void InterfaceInit(HWND hwnd, int nCmdShow)
{
    HWND tabControl = CreateWindow(WC_TABCONTROL, "", WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE, 0, 0, 800, 600, hwnd, NULL, NULL, NULL);
    AddNewUnitToTabControl("Статистика", tabControl, 0);
    AddNewUnitToTabControl("Жители", tabControl, 1);
    HWND hGDP = CreateWindow("static", "ВВП: 0$", WS_CHILD | WS_VISIBLE, 5, 25, 200, 15, hwnd, NULL, NULL, NULL);
    HWND hNatInc = CreateWindow("static", "Национальный доход: 0$", WS_CHILD | WS_VISIBLE, 5, 45, 200, 15, hwnd, NULL, NULL, NULL);
    HWND hZP = CreateWindow("static", "Средняя ЗП: 0$", WS_CHILD | WS_VISIBLE, 5, 65, 200, 15, hwnd, NULL, NULL, NULL);
}

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof(WNDCLASSEX);
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

    tItem.mask = TCIF_TEXT;

    if(!RegisterClassEx(&wincl)) return 0;

    hwnd = CreateWindowEx(0, szClassName, _T("Volsash Economy Simulator"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, HWND_DESKTOP, NULL, hThisInstance, NULL);
    ShowWindow(hwnd, nCmdShow);

    MenuInit(hwnd);
    InterfaceInit(hwnd, nCmdShow);

    // test
    int id = tab.newTab("Hello");

    while(GetMessage(&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
    return messages.wParam;
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_DESTROY:
            PostQuitMessage (0);
            break;
        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
            break;
    }
    return 0;
}
