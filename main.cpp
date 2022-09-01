#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <ctime>
#include <random>

#define ID_WARTOSC 501
#define ID_PRZYCISK1 502
#define ID_WYKRES 503
#define ID_CHECKBOX1 504
#define ID_CHECKBOX2 505
#define ID_LICZBAKLAS 506

LPSTR NazwaKlasy = (LPSTR) "Klasa Okienka";
MSG Komunikat;

HWND wyborFunkcji;
HWND hCombo;
HWND pomiar, checkbox, checkbox2;
HWND wartosc, wartoscBledu, liczbaKlas,wartoscSredniaTekst, wartoscOdchylenieTekst;
HWND dodajPomiarPrzycisk, dodajWykresPrzycisk, checkboxPrzycisk, checkboxPrzycisk2;
HWND oddzielenie, oddzielenie2;
HWND kodowanieTekst;
HWND hListBox, hListBox2;

int licz = 0;
int historia[10000];


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    // WYPEŁNIANIE STRUKTURY

    WNDCLASSEX wc;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = NazwaKlasy;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    // REJESTROWANIE KLASY OKNA

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Nie udalo się zarejestrować okna", "Blad",
                   MB_ICONEXCLAMATION | MB_OK);
        return 1;
    }

    // TWORZENIE OKNA

    HWND hwnd;

    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, NazwaKlasy, "ESCORT-179", WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT, 590, 520, NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, "Nie udało się utworzyć okna", "Błąd", MB_ICONEXCLAMATION);
        return 1;
    }


    srand(time(NULL));

    //Wybór funkcji pomiarowej

    wyborFunkcji = CreateWindowEx(0, "STATIC", "Wybierz funkcje i zakres pomiaru", WS_CHILD | WS_VISIBLE |
                                                                                   SS_CENTER, 20, 10, 150, 40, hwnd, NULL, hInstance, NULL);

    hCombo = CreateWindowEx(WS_EX_CLIENTEDGE, "COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
                                                                CBS_DROPDOWNLIST, 20, 50, 150, 450, hwnd, NULL,
                            hInstance, NULL);

    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "DC do 999.9 mV"); //0
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "DC do 9.999 V");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "DC do 99.99 V");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "DC do 999.9 V");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "DC do 400.0 uA");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "DC do 4.000 mA");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "DC do 40.00 mA");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "DC do 400.0 mA");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "DC do 4.000 A");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "DC do 10.00 A");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "AC do 999.9 mV"); //10
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "AC do 9.999 V");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "AC do 99.99 V");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "AC do 999.9 V");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "AC do 400.0 uA");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "AC do 4.000 mA");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "AC do 40.00 mA");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "AC do 400.0 mA");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "AC do 4.000 A");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "AC do 10.00 A");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "do 400.0 Ohm"); //20
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "do 4.000 kOhm");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "do 40.00 kOhm");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "do 400.0 kOhm");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "do 4.000 MOhm");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "do 40.00 MOhm");

    // Wpisywanie pomiaru

    pomiar = CreateWindowEx(0, "STATIC", "Wpisz wartosc \n(5 cyfr bez ,)", WS_CHILD | WS_VISIBLE |
                                                                           SS_CENTER, 20, 90, 150, 50, hwnd, NULL, hInstance, NULL);

    wartosc = CreateWindowEx(0, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 20, 130, 150, 20,
                             hwnd, (HMENU) ID_WARTOSC, hInstance, NULL);

    checkboxPrzycisk = CreateWindowEx(0, "BUTTON", "Dodaj blad pomiaru", WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
                                      20, 160, 150, 20, hwnd, (HMENU) ID_CHECKBOX1, hInstance, NULL);

    checkbox = CreateWindowEx(0, "STATIC", "Wpisz odchylenie standardowe", WS_CHILD | WS_VISIBLE |
                                                                           SS_CENTER, 20, 200, 150, 40, hwnd, NULL, hInstance, NULL);

    wartoscBledu = CreateWindowEx(0, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 20, 240, 150, 20,
                                  hwnd, (HMENU) ID_WARTOSC, hInstance, NULL);

    dodajPomiarPrzycisk = CreateWindowEx(0, "BUTTON", "Dodaj pomiar", WS_CHILD | WS_VISIBLE,
                                         20, 270, 150, 30, hwnd, (HMENU) ID_PRZYCISK1, hInstance, NULL);

    checkboxPrzycisk2 = CreateWindowEx(0, "BUTTON", "Wlasna liczba klas", WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
                                       20, 320, 150, 20, hwnd, (HMENU) ID_CHECKBOX2, hInstance, NULL);

    checkbox2 = CreateWindowEx(0, "STATIC", "Liczba klas", WS_CHILD | WS_VISIBLE |
                                                           SS_CENTER, 20, 350, 150, 20, hwnd, NULL, hInstance, NULL);

    liczbaKlas = CreateWindowEx(0, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 20, 370, 150, 20,
                                hwnd, (HMENU) ID_LICZBAKLAS, hInstance, NULL);

    dodajWykresPrzycisk = CreateWindowEx(0, "BUTTON", "Zapisz dane \ni wyswietl histogram", WS_CHILD | WS_VISIBLE | BS_MULTILINE,
                                         20, 400, 150, 60, hwnd, (HMENU) ID_WYKRES, hInstance, NULL);

    //Część druga
    oddzielenie = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                                                    SS_LEFT, 185, 0, 10, 480, hwnd, NULL, hInstance, NULL);

    kodowanieTekst = CreateWindowEx(0, "STATIC", "Informacja jaka dostaje komputer", WS_CHILD | WS_VISIBLE |
                                                                                     SS_CENTER, 210, 10, 350, 25, hwnd, NULL, hInstance, NULL);


    hListBox = CreateWindowEx(WS_EX_CLIENTEDGE, "LISTBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL,
                              210, 50, 350, 250, hwnd, NULL, hInstance, NULL);

    wartoscSredniaTekst = CreateWindowEx(0, "STATIC", "Wykonaj 2 pomiary aby policzyc srednia", WS_CHILD | WS_VISIBLE |
                                                                                                SS_CENTER, 210, 320, 350, 30, hwnd, NULL, hInstance, NULL);

    wartoscOdchylenieTekst = CreateWindowEx(0, "STATIC", "Wykonaj 2 pomiary aby policzyc odchylenie standardowe", WS_CHILD | WS_VISIBLE |
                                                                                                                  SS_CENTER, 210, 370, 350, 30, hwnd, NULL, hInstance, NULL);


    // Pokaż okno

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Pętla komunikatów

    while (GetMessage(&Komunikat, NULL, 0, 0)) {
        TranslateMessage(&Komunikat);
        DispatchMessage(&Komunikat);
    }
    return Komunikat.wParam;
}

// OBSŁUGA ZDARZEŃ

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {

        case WM_COMMAND:
            switch (wParam) {
                case ID_WYKRES: {

                    int min = 99999, max = 0;
                    double logarytm = pow(licz, 0.5);
                    int k = int(logarytm);
                    int start, koniec;

                    DWORD dlugosc = GetWindowTextLength(wartosc);
                    BOOL bChecked = (IsDlgButtonChecked(hwnd, ID_CHECKBOX2) == BST_CHECKED);

                    if (bChecked) {
                        LPSTR buforKlasy = (LPSTR) GlobalAlloc(GPTR, dlugosc + 1);
                        GetWindowText(liczbaKlas, buforKlasy, dlugosc + 1);
                        k = atoi(buforKlasy);
                    }


                    for (int i = 0; i < licz; i++) {
                        if (historia[i] < min)min = historia[i];
                        if (historia[i] > max)max = historia[i];
                    }

                    int c = (max - min) / k;

                    char bufor[10];
                    itoa(c, bufor, 10);
                    char *przedzial = (char *) malloc(32);
                    char *przedzialy[100];

                    int funkcja = SendMessage((HWND) hCombo, (UINT) CB_GETCURSEL, (WPARAM) 0, (LPARAM) 0);

                    for (int i = 0; i < 100; i++)przedzialy[i] = (char *) malloc(32);

                    int licznosc[100];
                    int liczbaZnakow = 11;

                    for (int i = 0; i < 100; i++)licznosc[i] = 0;

                    koniec = min - 1;
                    for (int i = 0; i < k; i++) {
                        start = koniec + 1;
                        koniec = start + c;

                        if (koniec>max)i = k - 1;


                        for (int j = 0; j < licz; j++) {
                            if ((historia[j] >= start) && (historia[j] <= koniec))licznosc[i]++;
                        }

                        int start2, koniec2;
                        start2 = start % (int) pow(10, 5) / pow(10, 4);
                        itoa(start2, bufor, 10);
                        strcpy(przedzial, bufor);

                        for (int j = 3; j >= 0; j--) {
                            if ((funkcja == 1) || (funkcja == 5) || (funkcja == 8) || (funkcja == 11) ||
                                (funkcja == 15) || (funkcja == 18) || (funkcja == 21) || (funkcja == 24)) {
                                if (j == 3)strcat(przedzial, ".");
                            }
                            if ((funkcja == 2) || (funkcja == 6) || (funkcja == 9) || (funkcja == 12) ||
                                (funkcja == 16) || (funkcja == 19) || (funkcja == 22) || (funkcja == 25)) {
                                if (j == 2)strcat(przedzial, ".");
                            }
                            if ((funkcja == 0) || (funkcja == 3) || (funkcja == 4) || (funkcja == 7) || (funkcja == 10) ||
                                (funkcja == 13) || (funkcja == 14) || (funkcja == 17) || (funkcja == 20) ||
                                (funkcja == 23)) {
                                if (j == 1)strcat(przedzial, ".");
                            }
                            start2 = start % (int) pow(10, j + 1) / pow(10, j);
                            itoa(start2, bufor, 10);

                            strcat(przedzial, bufor);
                        }


                        if ((funkcja == 0) || (funkcja == 10)) {
                            strcat(przedzial, "mV");
                            liczbaZnakow = 17;
                        }
                        if ((funkcja == 1) || (funkcja == 2) || (funkcja == 3) || (funkcja == 11) || (funkcja == 12) ||
                            (funkcja == 13)) {
                            strcat(przedzial, "V");
                            liczbaZnakow = 15;
                        }
                        if ((funkcja == 4) || (funkcja == 14)) {
                            strcat(przedzial, "uA");
                            liczbaZnakow = 17;
                        }
                        if ((funkcja == 5) || (funkcja == 6) || (funkcja == 7) || (funkcja == 15) || (funkcja == 16) ||
                            (funkcja == 17)) {
                            strcat(przedzial, "mA");
                            liczbaZnakow = 17;
                        }
                        if ((funkcja == 8) || (funkcja == 9) || (funkcja == 18) || (funkcja == 19)) {
                            strcat(przedzial, "A");
                            liczbaZnakow = 15;
                        }
                        if ((funkcja == 20)) {
                            strcat(przedzial, "Ohm");
                            liczbaZnakow = 19;
                        }
                        if ((funkcja == 21) || (funkcja == 22) || (funkcja == 23)) {
                            strcat(przedzial, "kOhm");
                            liczbaZnakow = 21;
                        }
                        if ((funkcja == 24) || (funkcja == 25)) {
                            strcat(przedzial, "MOhm");
                            liczbaZnakow = 21;
                        }

                        strcat(przedzial, "-");

                        for (int j = 4; j >= 0; j--) {
                            if ((funkcja == 1) || (funkcja == 5) || (funkcja == 8) || (funkcja == 11) ||
                                (funkcja == 15) || (funkcja == 18) || (funkcja == 21) || (funkcja == 24)) {
                                if (j == 3)strcat(przedzial, ".");
                            }
                            if ((funkcja == 2) || (funkcja == 6) || (funkcja == 9) || (funkcja == 12) ||
                                (funkcja == 16) || (funkcja == 19) || (funkcja == 22) || (funkcja == 25)) {
                                if (j == 2)strcat(przedzial, ".");
                            }
                            if ((funkcja == 0) || (funkcja == 3) || (funkcja == 4) || (funkcja == 7) || (funkcja == 10) ||
                                (funkcja == 13) || (funkcja == 14) || (funkcja == 17) || (funkcja == 20) ||
                                (funkcja == 23)) {
                                if (j == 1)strcat(przedzial, ".");
                            }
                            koniec2 = koniec % (int) pow(10, j + 1) / pow(10, j);
                            itoa(koniec2, bufor, 10);
                            strcat(przedzial, bufor);
                        }

                        if ((funkcja == 0) || (funkcja == 10)) {
                            strcat(przedzial, "mV");
                            liczbaZnakow = 17;
                        }
                        if ((funkcja == 1) || (funkcja == 2) || (funkcja == 3) || (funkcja == 11) || (funkcja == 12) ||
                            (funkcja == 13)) {
                            strcat(przedzial, "V");
                            liczbaZnakow = 15;
                        }
                        if ((funkcja == 4) || (funkcja == 14)) {
                            strcat(przedzial, "uA");
                            liczbaZnakow = 17;
                        }
                        if ((funkcja == 5) || (funkcja == 6) || (funkcja == 7) || (funkcja == 15) || (funkcja == 16) ||
                            (funkcja == 17)) {
                            strcat(przedzial, "mA");
                            liczbaZnakow = 17;
                        }
                        if ((funkcja == 8) || (funkcja == 9) || (funkcja == 18) || (funkcja == 19)) {
                            strcat(przedzial, "A");
                            liczbaZnakow = 15;
                        }
                        if ((funkcja == 20)) {
                            strcat(przedzial, "Ohm");
                            liczbaZnakow = 19;
                        }
                        if ((funkcja == 21) || (funkcja == 22) || (funkcja == 23)) {
                            strcat(przedzial, "kOhm");
                            liczbaZnakow = 21;
                        }
                        if ((funkcja == 24) || (funkcja == 25)) {
                            strcat(przedzial, "MOhm");
                            liczbaZnakow = 21;
                        }


                        strcpy(przedzialy[i], przedzial);
                    }


                    DWORD dwZapisane;
                    HANDLE hPlik;

                    hPlik = CreateFile("pomiary.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
                    if (hPlik == INVALID_HANDLE_VALUE) {
                        MessageBox(NULL, "Nie mozna otworzyc pliku.", "Blad!", MB_ICONEXCLAMATION);
                        PostQuitMessage(0); // Zakończ program
                    }

                    SYSTEMTIME st;
                    GetSystemTime(&st);
                    int day=st.wDay;
                    int month=st.wMonth;
                    int year=st.wYear;
                    int hour=st.wHour;
                    int minutes=st.wMinute;
                    int seconds=st.wSecond;

                    WriteFile(hPlik, "# Utworzono ", 12, &dwZapisane, NULL);
                    itoa(day, bufor, 10);
                    if(day<10) {
                        WriteFile(hPlik, "0", 1, &dwZapisane, NULL);
                        WriteFile(hPlik, bufor, 1, &dwZapisane, NULL);
                    }
                    else WriteFile(hPlik, bufor, 2, &dwZapisane, NULL);
                    WriteFile(hPlik, ".", 1, &dwZapisane, NULL);

                    itoa(month, bufor, 10);
                    if(month<10)
                    {
                        WriteFile(hPlik, "0", 1, &dwZapisane, NULL);
                        WriteFile(hPlik, bufor, 1, &dwZapisane, NULL);
                    }
                    else WriteFile(hPlik, bufor, 2, &dwZapisane, NULL);
                    WriteFile(hPlik, ".", 1, &dwZapisane, NULL);

                    itoa(year, bufor, 10);
                    WriteFile(hPlik, bufor, 4, &dwZapisane, NULL);

                    WriteFile(hPlik, " ", 1, &dwZapisane, NULL);

                    itoa(hour, bufor, 10);
                    if(hour<10)
                    {
                        WriteFile(hPlik, "0", 1, &dwZapisane, NULL);
                        WriteFile(hPlik, bufor, 1, &dwZapisane, NULL);
                    }
                    else WriteFile(hPlik, bufor, 2, &dwZapisane, NULL);
                    WriteFile(hPlik, ":", 1, &dwZapisane, NULL);

                    itoa(minutes, bufor, 10);
                    if(minutes<10)
                    {
                        WriteFile(hPlik, "0", 1, &dwZapisane, NULL);
                        WriteFile(hPlik, bufor, 1, &dwZapisane, NULL);
                    }
                    else WriteFile(hPlik, bufor, 2, &dwZapisane, NULL);
                    WriteFile(hPlik, ":", 1, &dwZapisane, NULL);

                    itoa(seconds, bufor, 10);
                    if(seconds<10)
                    {
                        WriteFile(hPlik, "0", 1, &dwZapisane, NULL);
                        WriteFile(hPlik, bufor, 1, &dwZapisane, NULL);
                    }
                    else WriteFile(hPlik, bufor, 2, &dwZapisane, NULL);

                    WriteFile(hPlik, "\r\n", 2, &dwZapisane, NULL);

                    WriteFile(hPlik, "Przedzialy licznosc", 19, &dwZapisane, NULL);
                    WriteFile(hPlik, "\r\n", 2, &dwZapisane, NULL);


                    for (int i = 0; i < k; i++) {
                        WriteFile(hPlik, przedzialy[i], liczbaZnakow, &dwZapisane, NULL);
                        WriteFile(hPlik, "\t", 1, &dwZapisane, NULL);
                        itoa(licznosc[i], bufor, 10);
                        if (licznosc[i] < 10) WriteFile(hPlik, bufor, 1, &dwZapisane, NULL);
                        if ((licznosc[i] >= 10)&&(licznosc[i] < 100)) WriteFile(hPlik, bufor, 2, &dwZapisane, NULL);
                        if ((licznosc[i] >= 100)) WriteFile(hPlik, bufor, 3, &dwZapisane, NULL);
                        WriteFile(hPlik, "\r\n", 2, &dwZapisane, NULL);
                    }

                    CloseHandle(hPlik);


                    char buforPlik [40];

                    HANDLE hPlik2;
                    hPlik2 = CreateFile("wygenerowanepomiary.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
                    if (hPlik2 == INVALID_HANDLE_VALUE) {
                        MessageBox(NULL, "Nie mozna otworzyc pliku.", "Blad!", MB_ICONEXCLAMATION);
                        PostQuitMessage(0); // Zakończ program
                    }

                    WriteFile(hPlik2, "# Utworzono ", 12, &dwZapisane, NULL);
                    itoa(day, bufor, 10);
                    if(day<10) {
                        WriteFile(hPlik2, "0", 1, &dwZapisane, NULL);
                        WriteFile(hPlik2, bufor, 1, &dwZapisane, NULL);
                    }
                    else WriteFile(hPlik2, bufor, 2, &dwZapisane, NULL);
                    WriteFile(hPlik2, ".", 1, &dwZapisane, NULL);

                    itoa(month, bufor, 10);
                    if(month<10)
                    {
                        WriteFile(hPlik2, "0", 1, &dwZapisane, NULL);
                        WriteFile(hPlik2, bufor, 1, &dwZapisane, NULL);
                    }
                    else WriteFile(hPlik2, bufor, 2, &dwZapisane, NULL);
                    WriteFile(hPlik2, ".", 1, &dwZapisane, NULL);

                    itoa(year, bufor, 10);
                    WriteFile(hPlik2, bufor, 4, &dwZapisane, NULL);

                    WriteFile(hPlik2, " ", 1, &dwZapisane, NULL);

                    itoa(hour, bufor, 10);
                    if(hour<10)
                    {
                        WriteFile(hPlik2, "0", 1, &dwZapisane, NULL);
                        WriteFile(hPlik2, bufor, 1, &dwZapisane, NULL);
                    }
                    else WriteFile(hPlik2, bufor, 2, &dwZapisane, NULL);
                    WriteFile(hPlik2, ":", 1, &dwZapisane, NULL);

                    itoa(minutes, bufor, 10);
                    if(minutes<10)
                    {
                        WriteFile(hPlik2, "0", 1, &dwZapisane, NULL);
                        WriteFile(hPlik2, bufor, 1, &dwZapisane, NULL);
                    }
                    else WriteFile(hPlik2, bufor, 2, &dwZapisane, NULL);
                    WriteFile(hPlik2, ":", 1, &dwZapisane, NULL);

                    itoa(seconds, bufor, 10);
                    if(seconds<10)
                    {
                        WriteFile(hPlik2, "0", 1, &dwZapisane, NULL);
                        WriteFile(hPlik, bufor, 1, &dwZapisane, NULL);
                    }
                    else WriteFile(hPlik2, bufor, 2, &dwZapisane, NULL);
                    WriteFile(hPlik2, "\r\n", 2, &dwZapisane, NULL);

                    for(int i=0;i<licz;i++)
                    {
                        SendMessage((HWND) hListBox, (UINT) LB_GETTEXT, (WPARAM) i, (LPARAM) buforPlik);
                        WriteFile(hPlik2, buforPlik, 32, &dwZapisane, NULL);
                        WriteFile(hPlik2, "\r\n", 2, &dwZapisane, NULL);
                    }
                    CloseHandle(hPlik2);

                    ShellExecuteA(NULL, NULL, "wgnuplot", "-p file.gp", NULL, SW_SHOWNORMAL);

                    break;
                }

                case ID_PRZYCISK1: {

                    char *pomiar = (char *) malloc(64);

                    strcpy(pomiar, "1F");

                    int funkcja = SendMessage((HWND) hListBox, (UINT) CB_GETCURSEL, (WPARAM) 0, (LPARAM) 0);

                    switch (funkcja) {
                        case 0 :
                            strcat(pomiar, " 20 20");
                            break;
                        case 1 :
                            strcat(pomiar, " 20 21");
                            break;
                        case 2 :
                            strcat(pomiar, " 20 22");
                            break;
                        case 3 :
                            strcat(pomiar, " 20 23");
                            break;
                        case 4 :
                            strcat(pomiar, " 21 20");
                            break;
                        case 5 :
                            strcat(pomiar, " 21 21");
                            break;
                        case 6 :
                            strcat(pomiar, " 22 20");
                            break;
                        case 7 :
                            strcat(pomiar, " 22 21");
                            break;
                        case 8 :
                            strcat(pomiar, " 23 20");
                            break;
                        case 9 :
                            strcat(pomiar, " 23 21");
                            break;
                        case 10 :
                            strcat(pomiar, " 28 20");
                            break;
                        case 11 :
                            strcat(pomiar, " 28 21");
                            break;
                        case 12 :
                            strcat(pomiar, " 28 22");
                            break;
                        case 13 :
                            strcat(pomiar, " 28 23");
                            break;
                        case 14 :
                            strcat(pomiar, " 29 20");
                            break;
                        case 15 :
                            strcat(pomiar, " 29 21");
                            break;
                        case 16 :
                            strcat(pomiar, " 30 20");
                            break;
                        case 17 :
                            strcat(pomiar, " 30 21");
                            break;
                        case 18 :
                            strcat(pomiar, " 31 20");
                            break;
                        case 19 :
                            strcat(pomiar, " 31 21");
                            break;
                        case 20 :
                            strcat(pomiar, " 26 20");
                            break;
                        case 21 :
                            strcat(pomiar, " 26 21");
                            break;
                        case 22 :
                            strcat(pomiar, " 26 22");
                            break;
                        case 23 :
                            strcat(pomiar, " 26 23");
                            break;
                        case 24 :
                            strcat(pomiar, " 26 24");
                            break;
                        case 25 :
                            strcat(pomiar, " 26 25");
                            break;
                    }

                    strcat(pomiar, " 26");

                    DWORD dlugosc = GetWindowTextLength(wartosc);
                    LPSTR bufor = (char *) malloc(32); //(LPSTR) GlobalAlloc(GPTR, dlugosc + 1);
                    GetWindowText(wartosc, bufor, dlugosc + 1);

                    int liczba = atoi(bufor);

                    BOOL bChecked = (IsDlgButtonChecked(hwnd, ID_CHECKBOX1) == BST_CHECKED);

                    if (bChecked) {


                        LPSTR buforWartosc = (char *) malloc(32); //(LPSTR) GlobalAlloc(GPTR, dlugosc + 1);
                        GetWindowText(wartoscBledu, buforWartosc, dlugosc + 1);
                        int blad = atoi(buforWartosc);


                        std::default_random_engine generator;
                        std::normal_distribution<double> distribution(liczba, blad);

                        int p[10000] = {};
                        for (int i = 0; i < 10000; i++) {
                            double number = distribution(generator);
                            p[i] = int(number);
                        }
                        int wylosowana_liczba = int(std::rand() % 10000);
                        liczba = p[wylosowana_liczba];


                        if (liczba > 99999)liczba = 99999;
                        if (liczba < 00000)liczba = 00000;
                    }

                    int liczba2;
                    char bufor2[10];

                    for (int i = 4; i >= 0; i--) {
                        liczba2 = liczba % (int) pow(10, i + 1) / pow(10, i);
                        itoa(liczba2, bufor2, 10);
                        strcat(pomiar, " 2");
                        strcat(pomiar, bufor2);
                    }

                    historia[licz] = liczba;
                    licz++;

                    strcat(pomiar, " 22 1E    ");

                    for (int i = 4; i >= 0; i--) {
                        if ((funkcja == 1) || (funkcja == 5) || (funkcja == 8) || (funkcja == 11) ||
                            (funkcja == 15) || (funkcja == 18) || (funkcja == 21) || (funkcja == 24)) {
                            if (i == 3)strcat(pomiar, ".");
                        }
                        if ((funkcja == 2) || (funkcja == 6) || (funkcja == 9) || (funkcja == 12) ||
                            (funkcja == 16) || (funkcja == 19) || (funkcja == 22) || (funkcja == 25)) {
                            if (i == 2)strcat(pomiar, ".");
                        }
                        if ((funkcja == 0) || (funkcja == 3) || (funkcja == 4) || (funkcja == 7) || (funkcja == 10) ||
                            (funkcja == 13) || (funkcja == 14) || (funkcja == 17) || (funkcja == 20) ||
                            (funkcja == 23)) {
                            if (i == 1)strcat(pomiar, ".");
                        }
                        liczba2 = liczba % (int) pow(10, i + 1) / pow(10, i);

                        itoa(liczba2, bufor, 10);
                        strcat(pomiar, bufor);

                    }

                    if ((funkcja == 0) || (funkcja == 10)) {
                        strcat(pomiar, "mV");
                    }
                    if ((funkcja == 1) || (funkcja == 2) || (funkcja == 3) || (funkcja == 11) || (funkcja == 12) ||
                        (funkcja == 13)) {
                        strcat(pomiar, "V");
                    }
                    if ((funkcja == 4) || (funkcja == 14)) {
                        strcat(pomiar, "uA");
                    }
                    if ((funkcja == 5) || (funkcja == 6) || (funkcja == 7) || (funkcja == 15) || (funkcja == 16) ||
                        (funkcja == 17)) {
                        strcat(pomiar, "mA");
                    }
                    if ((funkcja == 8) || (funkcja == 9) || (funkcja == 18) || (funkcja == 19)) {
                        strcat(pomiar, "A");
                    }
                    if ((funkcja == 20)) {
                        strcat(pomiar, "Ohm");
                    }
                    if ((funkcja == 21) || (funkcja == 22) || (funkcja == 23)) {
                        strcat(pomiar, "kOhm");
                    }
                    if ((funkcja == 24) || (funkcja == 25)) {
                        strcat(pomiar, "MOhm");
                    }

                    SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM) pomiar);


                    if(licz>1)
                    {
                        int sredniaLiczba=0, odchylenieLiczba=0;
                        double srednia=0, odchylenie=0;
                        for(int i=0;i<licz;i++)
                        {
                            srednia=srednia+historia[i];
                        }
                        srednia=srednia/licz;


                        strcpy(pomiar, "Wartosc srednia wynosi ");


                        ////////////////////////////////////////
                        for (int i = 4; i >= 0; i--) {
                            if ((funkcja == 1) || (funkcja == 5) || (funkcja == 8) || (funkcja == 11) ||
                                (funkcja == 15) || (funkcja == 18) || (funkcja == 21) || (funkcja == 24)) {
                                if (i == 3)strcat(pomiar, ".");
                            }
                            if ((funkcja == 2) || (funkcja == 6) || (funkcja == 9) || (funkcja == 12) ||
                                (funkcja == 16) || (funkcja == 19) || (funkcja == 22) || (funkcja == 25)) {
                                if (i == 2)strcat(pomiar, ".");
                            }
                            if ((funkcja == 0) || (funkcja == 3) || (funkcja == 4) || (funkcja == 7) || (funkcja == 10) ||
                                (funkcja == 13) || (funkcja == 14) || (funkcja == 17) || (funkcja == 20) ||
                                (funkcja == 23)) {
                                if (i == 1)strcat(pomiar, ".");
                            }
                            sredniaLiczba = (int) srednia % (int) pow(10, i + 1) / pow(10, i);
                            itoa(sredniaLiczba, bufor, 10);
                            strcat(pomiar, bufor);
                        }

                        if ((funkcja == 0) || (funkcja == 10)) {
                            strcat(pomiar, "mV");
                        }
                        if ((funkcja == 1) || (funkcja == 2) || (funkcja == 3) || (funkcja == 11) || (funkcja == 12) ||
                            (funkcja == 13)) {
                            strcat(pomiar, "V");
                        }
                        if ((funkcja == 4) || (funkcja == 14)) {
                            strcat(pomiar, "uA");
                        }
                        if ((funkcja == 5) || (funkcja == 6) || (funkcja == 7) || (funkcja == 15) || (funkcja == 16) ||
                            (funkcja == 17)) {
                            strcat(pomiar, "mA");
                        }
                        if ((funkcja == 8) || (funkcja == 9) || (funkcja == 18) || (funkcja == 19)) {
                            strcat(pomiar, "A");
                        }
                        if ((funkcja == 20)) {
                            strcat(pomiar, "Ohm");
                        }
                        if ((funkcja == 21) || (funkcja == 22) || (funkcja == 23)) {
                            strcat(pomiar, "kOhm");
                        }
                        if ((funkcja == 24) || (funkcja == 25)) {
                            strcat(pomiar, "MOhm");
                        }
                        ///////////////////////////////////////

                        SetWindowText(wartoscSredniaTekst, pomiar);

                        for(int i=0;i<licz;i++)
                        {
                            odchylenie=odchylenie+pow((historia[i]-srednia),2);
                        }
                        odchylenie=pow((odchylenie/licz),0.5);


                        //itoa(odchylenie, bufor, 10);
                        strcpy(pomiar, "Odchylenie standardowe wynosi ");
                        //strcat(pomiar, bufor);

                        ///////////////////////////
                        for (int i = 4; i >= 0; i--) {
                            if ((funkcja == 1) || (funkcja == 5) || (funkcja == 8) || (funkcja == 11) ||
                                (funkcja == 15) || (funkcja == 18) || (funkcja == 21) || (funkcja == 24)) {
                                if (i == 3)strcat(pomiar, ".");
                            }
                            if ((funkcja == 2) || (funkcja == 6) || (funkcja == 9) || (funkcja == 12) ||
                                (funkcja == 16) || (funkcja == 19) || (funkcja == 22) || (funkcja == 25)) {
                                if (i == 2)strcat(pomiar, ".");
                            }
                            if ((funkcja == 0) || (funkcja == 3) || (funkcja == 4) || (funkcja == 7) || (funkcja == 10) ||
                                (funkcja == 13) || (funkcja == 14) || (funkcja == 17) || (funkcja == 20) ||
                                (funkcja == 23)) {
                                if (i == 1)strcat(pomiar, ".");
                            }
                            odchylenieLiczba = (int) odchylenie % (int) pow(10, i + 1) / pow(10, i);
                            itoa(odchylenieLiczba, bufor, 10);
                            strcat(pomiar, bufor);
                        }

                        if ((funkcja == 0) || (funkcja == 10)) {
                            strcat(pomiar, "mV");
                        }
                        if ((funkcja == 1) || (funkcja == 2) || (funkcja == 3) || (funkcja == 11) || (funkcja == 12) ||
                            (funkcja == 13)) {
                            strcat(pomiar, "V");
                        }
                        if ((funkcja == 4) || (funkcja == 14)) {
                            strcat(pomiar, "uA");
                        }
                        if ((funkcja == 5) || (funkcja == 6) || (funkcja == 7) || (funkcja == 15) || (funkcja == 16) ||
                            (funkcja == 17)) {
                            strcat(pomiar, "mA");
                        }
                        if ((funkcja == 8) || (funkcja == 9) || (funkcja == 18) || (funkcja == 19)) {
                            strcat(pomiar, "A");
                        }
                        if ((funkcja == 20)) {
                            strcat(pomiar, "Ohm");
                        }
                        if ((funkcja == 21) || (funkcja == 22) || (funkcja == 23)) {
                            strcat(pomiar, "kOhm");
                        }
                        if ((funkcja == 24) || (funkcja == 25)) {
                            strcat(pomiar, "MOhm");
                        }
                        ///////////////////////////

                        SetWindowText(wartoscOdchylenieTekst, pomiar);

                    }

                    break;
                }

                case ID_CHECKBOX1: {
                    BOOL bChecked = (IsDlgButtonChecked(hwnd, ID_CHECKBOX1) == BST_CHECKED);
                    if (bChecked) {
                        CheckDlgButton(hwnd, ID_CHECKBOX1, BST_UNCHECKED);
                    } else {
                        CheckDlgButton(hwnd, ID_CHECKBOX1, BST_CHECKED);
                    }
                    break;
                }

                case ID_CHECKBOX2: {
                    BOOL bChecked = (IsDlgButtonChecked(hwnd, ID_CHECKBOX2) == BST_CHECKED);
                    if (bChecked) {
                        CheckDlgButton(hwnd, ID_CHECKBOX2, BST_UNCHECKED);
                    } else {
                        CheckDlgButton(hwnd, ID_CHECKBOX2, BST_CHECKED);
                    }
                    break;
                }

            }
            break;

        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
            break;
    }

    return 0;
}