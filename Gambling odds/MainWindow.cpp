#include <windows.h>


//LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

int WINAPI mainwindow(HINSTANCE hInst, HINSTANCE hPrevInstance,LPSTR args,int ncmdshow) {

	WNDCLASSW wc = { 0 };
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = L"myWindowClass";
	//wc.lpfnWndProc = WindowProcedure;

	if (!RegisterClassW(&wc))
		return-1;
	CreateWindowW(L"myWindowClass", L"GAMBA", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 400, 400, NULL, NULL, NULL, NULL);
	return 0;
}

//LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
		

//}
