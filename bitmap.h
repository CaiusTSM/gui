#pragma once

#include <fileio.h>

struct bitmap
{
	unsigned char *memory;
	int bytes_per_pixel;
	int width;
	int height;
};

bitmap *create_bitmap(int width, int height, int bytes_per_pixel)
{
	bitmap *bmp = new bitmap();

	bmp->memory = new unsigned char[width * height * bytes_per_pixel];
	bmp->bytes_per_pixel = bytes_per_pixel;
	bmp->width = width;
	bmp->height = height;

	return bmp;
}

void free_bitmap(bitmap *bmp)
{
	if (bmp)
	{
		if (bmp->memory)
			delete[] bmp->memory;
		delete bmp;
		bmp = 0;
	}
}

bool load_bitmap_data(bitmap *bmp, const char *file_path)
{
	char *file_data = 0;
	int length = 0;

	if (!read_file_to_string(file_path, false, &file_data, &length))
		return false;

	if (length < 54)
		return false;

	if (bmp->memory)
		delete[] bmp->memory;

	int offset_to_image = *(int *)(&file_data[10]);

	int width = *(int *)(&file_data[18]);
	int height = *(int *)(&file_data[22]);

	bmp->width = width;
	bmp->height = height;

	int num_bytes = bmp->width * bmp->height * bmp->bytes_per_pixel;

	bmp->memory = new unsigned char[num_bytes];

	int row_length = width * 3;
	// zero padding at end of row in 24 bit color bmps
	while (row_length % 4 != 0)
		row_length++;

	int c = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width * 3; j += 3)
		{
			bmp->memory[c] = file_data[offset_to_image + i * row_length + j];
			bmp->memory[c + 1] = file_data[offset_to_image + i * row_length + j + 1];
			bmp->memory[c + 2] = file_data[offset_to_image + i * row_length + j + 2];
			bmp->memory[c + 3] = 0;
			c += bmp->bytes_per_pixel;
		}
	}

	return true;
}