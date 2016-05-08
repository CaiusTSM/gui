#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <str.h>

#ifdef _WIN32

#include <windows.h>

bool read_file_to_string(const char *file_path, bool binary, char **file_data, int *length)
{
	if (file_data == 0)
		return false;

	HANDLE file_handle = CreateFileA(
		file_path,
		GENERIC_READ,
		0,
		0,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		0
	);

	if (file_handle == INVALID_HANDLE_VALUE)
	{
		CloseHandle(file_handle);

		return false;
	}

	DWORD file_size_lower_32 = GetFileSize(file_handle, 0);

	DWORD number_bytes_read;
	LPVOID buffer = new char[file_size_lower_32 + 1];
	((char *)buffer)[file_size_lower_32] = '\0';
	BOOL result = ReadFile(
		file_handle,
		buffer,
		file_size_lower_32,
		&number_bytes_read,
		0
	);

	if (result == 0)
	{
		delete[] (char *)buffer;
		CloseHandle(file_handle);

		return false;
	}

	delete (*file_data);
	(*file_data) = (char *)buffer;
	(*length) = number_bytes_read;

	CloseHandle(file_handle);

	return true;
}

bool write_string_to_file(const char *file_data, int length, const char *file_path, bool binary)
{
	HANDLE file_handle = CreateFileA(
		file_path,
		GENERIC_WRITE,
		0,
		0,
		CREATE_NEW,
		FILE_ATTRIBUTE_NORMAL,
		0
	);

	if (file_handle == INVALID_HANDLE_VALUE)
	{
		CloseHandle(file_handle);
		return false;
	}

	if (WriteFile(file_handle, file_data, length, 0, 0) == 0)
	{
		CloseHandle(file_handle);
		return false;
	}

	CloseHandle(file_handle);

	return true;
}

#endif