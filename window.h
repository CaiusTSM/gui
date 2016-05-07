#pragma once

#ifndef UNICODE
#define UNICODE
#endif

// if on windows: windows specific code
// however function/struct names, args and return values are the same on all OS's
// they just work differently internally
#ifdef _WIN32

// for cursors
#define OEMRESOURCE

#include <windows.h>

enum cursor_type
{
	NORMAL,
	INTERACT,
	LOADING,
	TEXT,
	CROSS,
	SIZING_NS,
	SIZING_WE,
	SIZING_NESW,
	SIZING_NWSE
};

struct window {
	// win32 api specific
	HINSTANCE hinstance;
	HWND window_handle;
	BITMAPINFO bmi;

	bool is_open;

	void *bitmap_memory;
	int bitmap_width;
	int	bitmap_height;

	void(*on_resize)(window *window, int argc, void **args);
	int resize_argc;
	void **resize_args;

	int cursor_x;
	int cursor_y;
	bool mouse_state[3];

	cursor_type cursor_type;

	unsigned char *keyboard_state;
	int num_keys;
};

static window *current_window;

static void resize_dib_section(int width, int height)
{
	if (current_window->bitmap_memory)
		VirtualFree(current_window->bitmap_memory, 0, MEM_RELEASE);

	current_window->bitmap_width = width;
	current_window->bitmap_height = height;

	current_window->bmi.bmiHeader.biSize = sizeof(current_window->bmi.bmiHeader);
	current_window->bmi.bmiHeader.biWidth = width;
	current_window->bmi.bmiHeader.biHeight = height;
	current_window->bmi.bmiHeader.biPlanes = 1;
	current_window->bmi.bmiHeader.biBitCount = 32;
	current_window->bmi.bmiHeader.biCompression = BI_RGB;

	int bytes_per_pixel = 4;
	int buffer_size = width * height * bytes_per_pixel;

	current_window->bitmap_memory = VirtualAlloc(0, buffer_size, MEM_COMMIT, PAGE_READWRITE);
}

static void paint_dib_section(HDC hdc, int dest_x, int dest_y, int dest_width, int dest_height)
{
	StretchDIBits(
		hdc,
		dest_x,
		dest_y,
		dest_width,
		dest_height,
		0,
		0,
		current_window->bitmap_width,
		current_window->bitmap_height,
		current_window->bitmap_memory,
		&current_window->bmi,
		DIB_RGB_COLORS,
		SRCCOPY
	);
}

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	case WM_CLOSE:
	{
		DestroyWindow(hwnd);

		if (current_window != 0)
			current_window->is_open = false;
		break;
	}
	case WM_SIZE:
	{
		RECT rect = {};

		GetClientRect(hwnd, &rect);

		resize_dib_section(rect.right - rect.left, rect.bottom - rect.top);
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		current_window->on_resize(current_window, current_window->resize_argc, current_window->resize_args);

		paint_dib_section(hdc, ps.rcPaint.left, ps.rcPaint.top, ps.rcPaint.right - ps.rcPaint.left, ps.rcPaint.bottom - ps.rcPaint.top);

		EndPaint(hwnd, &ps);
		break;
	}
	case WM_MOUSEMOVE:
	{
		current_window->cursor_x = LOWORD(lParam);
		current_window->cursor_y = HIWORD(lParam);
		/*
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(current_window->window_handle, &p);
		current_window->cursor_x = p.x;
		current_window->cursor_y = p.y;
		*/
		break;
	}
	case WM_SETCURSOR:
	{
		HCURSOR hcursor = 0;

		switch (current_window->cursor_type)
		{
		case NORMAL:
		{
			hcursor = LoadCursor(0, IDC_ARROW);
			break;
		}
		case INTERACT:
		{
			hcursor = LoadCursor(0, IDC_HAND);
			break;
		}
		case LOADING:
		{
			hcursor = LoadCursor(0, IDC_APPSTARTING);
			break;
		}
		case CROSS:
		{
			hcursor = LoadCursor(0, IDC_CROSS);
			break;
		}
		case SIZING_NS:
		{
			hcursor = LoadCursor(0, IDC_SIZENS);
			break;
		}
		case SIZING_WE:
		{
			hcursor = LoadCursor(0, IDC_SIZEWE);
			break;
		}
		case SIZING_NESW:
		{
			hcursor = LoadCursor(0, IDC_SIZENESW);
			break;
		}
		case SIZING_NWSE:
		{
			hcursor = LoadCursor(0, IDC_SIZENWSE);
			break;
		}
		}

		SetCursor(hcursor);
		break;
	}
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

/*
set x, y, width, height to -1 for default values
returns a pointer to the window
argc and args is the count and arguments passed to on_resize when window resizes
*/
window *create_window(
	const wchar_t *title,
	int x,
	int y,
	int width,
	int height,
	void(*on_resize)(window *window, int argc, void **args),
	int argc,
	void **args
)
{
	const wchar_t class_name[] = L"Omega Window Class";

	HINSTANCE hInstance = GetModuleHandle(0);

	LPWNDCLASSEX lpwcx = {};
	int is_registered = GetClassInfoEx(
		hInstance,
		class_name,
		lpwcx
	);

	if (!is_registered)
	{
		WNDCLASS wc = {};

		wc.lpfnWndProc = WindowProc;
		wc.hInstance = hInstance;
		wc.lpszClassName = class_name;
		wc.hCursor = LoadCursor(0, IDC_ARROW);

		RegisterClass(&wc);
	}

	HWND hwnd;

	if (x == -1 && y == -1 && width > -1 && height > -1)
	{
		hwnd = CreateWindowEx(
			0,
			class_name,
			title,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			width,
			height,
			0,
			0,
			hInstance,
			0
		);
	}
	else if (x > -1 && y > -1 && width == -1 && height == -1)
	{
		hwnd = CreateWindowEx(
			0,
			class_name,
			title,
			WS_OVERLAPPEDWINDOW,
			x,
			y,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			0,
			0,
			hInstance,
			0
		);
	}
	else
	{
		hwnd = CreateWindowEx(
			0,
			class_name,
			title,
			WS_OVERLAPPEDWINDOW,
			x,
			y,
			width,
			height,
			0,
			0,
			hInstance,
			0
		);
	}

	window *win = new window;

	win->hinstance = hInstance;
	win->window_handle = hwnd;
	win->bmi = {};

	win->is_open = true;

	win->bitmap_memory = 0;

	win->on_resize = on_resize;
	win->resize_argc = argc;
	win->resize_args = args;

	win->keyboard_state = new unsigned char[256];
	win->num_keys = 256;
	for (int i = 0; i < 256; i++)
		win->keyboard_state[i] = 0;

	RECT rect = {};

	GetClientRect(hwnd, &rect);

	current_window = win;
	resize_dib_section(rect.right - rect.left, rect.bottom - rect.top);

	ShowWindow(win->window_handle, SW_SHOW);

	return win;
}

// frees the window
void free_window(window *window)
{
	delete[] window->keyboard_state;
	delete window;
}

void update_window(window *window)
{
	current_window = window;

	if (GetAsyncKeyState(VK_LBUTTON))
		current_window->mouse_state[0] = true;
	else
		current_window->mouse_state[0] = false;

	if (GetAsyncKeyState(VK_MBUTTON))
		current_window->mouse_state[1] = true;
	else
		current_window->mouse_state[1] = false;

	if (GetAsyncKeyState(VK_RBUTTON))
		current_window->mouse_state[2] = true;
	else
		current_window->mouse_state[2] = false;

	GetKeyboardState(current_window->keyboard_state);
	for (int i = 0; i < current_window->num_keys; i++)
		current_window->keyboard_state[i] &= 0x80;

	HDC hdc = GetDC(window->window_handle);
	RECT rect = {};
	GetClientRect(window->window_handle, &rect);
	paint_dib_section(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
	ReleaseDC(window->window_handle, hdc);

	UpdateWindow(window->window_handle);

	MSG msg = {};
	while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

// closes  the window
void close_window(window *window)
{
	current_window = window;
	PostMessage(window->window_handle, WM_CLOSE, 0, 0);
}

#endif