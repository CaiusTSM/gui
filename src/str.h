#pragma once

struct string
{
	string()
	{
		reserved_size = 1;
		length = 0;
		data = new char[reserved_size];
	}

	string(string &other)
	{
		reserved_size = other.reserved_size;

		data = new char[reserved_size];
		for (int i = 0; i < other.length + 1; i++)
			data[i] = other.data[i];
		length = other.length;
	}

	string(const char *arr)
	{
		int arr_length = 0;
		while (arr[arr_length] != '\0')
			arr_length++;
		arr_length++;

		reserved_size = arr_length;

		data = new char[reserved_size];
		for (int i = 0; i < arr_length; i++)
			data[i] = arr[i];
		length = arr_length - 1;
	}

	virtual ~string()
	{
		delete[] data;
	}

	char *data;
	int reserved_size;
	int length;

	void reserve(int n)
	{
		reserved_size += n;

		char *temp = new char[reserved_size];
		for (int i = 0; i < length; i++)
			temp[i] = data[i];

		delete[] data;
		data = new char[reserved_size];
		for (int i = 0; i < length; i++)
			data[i] = temp[i];
	}

	string &operator=(const char *arr)
	{
		int arr_length = 0;
		while (arr[arr_length] != '\0')
			arr_length++;
		arr_length++;

		if (reserved_size < arr_length)
		{
			reserved_size = arr_length;

			delete[] data;
			data = new char[reserved_size];
			for (int i = 0; i < arr_length; i++)
				data[i] = arr[i];
			length = arr_length - 1;
		}
		else
		{
			for (int i = 0; i < arr_length; i++)
				data[i] = arr[i];
			length = arr_length - 1;
		}

		return *this;
	}

	string &operator=(string &other)
	{
		if (reserved_size < other.reserved_size)
		{
			reserved_size = other.reserved_size;

			delete[] data;
			data = new char[reserved_size];
			for (int i = 0; i < other.length + 1; i++)
				data[i] = other.data[i];
			length = other.length;
		}
		else
		{
			for (int i = 0; i < other.length + 1; i++)
				data[i] = other.data[i];
			length = other.length;
		}

		return *this;
	}

	string &operator+=(const char *arr)
	{
		int arr_length = 0;
		while (arr[arr_length] != '\0')
			arr_length++;
		arr_length++;

		char *temp = new char[length];
		for (int i = 0; i < length; i++)
			temp[i] = data[i];

		delete[] data;
		if (reserved_size < length + arr_length)
			reserved_size = length + arr_length;
		data = new char[reserved_size];

		for (int i = 0; i < length; i++)
			data[i] = temp[i];
		delete[] temp;

		for (int i = 0; i < arr_length; i++)
			data[length + i] = arr[i];
		length += arr_length - 1;

		return *this;
	}

	string &operator+=(string &other)
	{
		char *temp = new char[length];
		for (int i = 0; i < length; i++)
			temp[i] = data[i];

		delete[] data;
		if (reserved_size < length + other.reserved_size)
			reserved_size = length + other.reserved_size;
		data = new char[reserved_size];

		for (int i = 0; i < length; i++)
			data[i] = temp[i];
		delete[] temp;

		for (int i = 0; i < other.length + 1; i++)
			data[length + i] = other.data[i];
		length += other.length;

		return *this;
	}

	char &operator[](int index)
	{
		return data[index];
	}
};