#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

int main()
{
	boolean Retryagain = TRUE;
	HWND hwnd = FindWindowA(NULL, "osu!");
	while (Retryagain)
	{
		
		if (hwnd == NULL)
		{
			cout << "osu! not open" << endl;
			cout << "Press Q to quit or Any Key to Retry" << endl;
			string rtryOrQuit;
			cin >> rtryOrQuit;
			if (rtryOrQuit == "Q")
			{
				exit(-1);
			}
			hwnd = FindWindowA(NULL, "osu!");
		}
		else
		{
			Retryagain = FALSE;
		}
	}

	
		DWORD procsesIDNumber;
		GetWindowThreadProcessId(hwnd, &procsesIDNumber);
		HANDLE handel = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procsesIDNumber);
		
		if (procsesIDNumber == NULL)
		{
			cout << "CANNOT GET PROCESS ID NUMBER" << endl;
			Sleep(3000);
			exit(-1);
		}
		else
		{
			cout << "Created Handel Succsessfully" << endl;
			Sleep(3000);
			float SongProgressOrTime = 2;
			boolean Continue = TRUE;

			while (Continue)
			{
				ReadProcessMemory(handel, (void*)0x01995934, (void*)&SongProgressOrTime, sizeof(SongProgressOrTime), 0);
				cout << SongProgressOrTime << endl;
				Sleep(200);
			}
			
		}

	


	return(0);
}