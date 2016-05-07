#include <test_config.h>

#if TEST_FILEIO == 1

#include <stdio.h>

#include <fileio.h>

int main() {
	string file_data;
	if (!read_file_to_string(&file_data, "blah.txt"))
	{
		printf("Could not read file.\n");
	}

	printf("file_data:\n\n%s\n\n", file_data.data);

	if (!write_string_to_file(file_data, "C:\\Users\\Lucas\\Desktop\\"))
	{
		printf("Failed to write to file.\n");
	}

	getchar();

	return 0;
}

#endif