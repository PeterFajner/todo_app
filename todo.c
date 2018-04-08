/**
 * This is a simple todo app.
 *
 * File format, each line
 * 	LEN ID DATA
 * 	^   ^  ^
 * 	|   |  |
 * 	|   |   -- string, stored message
 * 	|    ----- int, ID of the message
 * 	 --------- int, length of the message
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include PLATFORM

#define FNAME "db.txt"
#define MAXLEN 100000 // maximum allowed length of a line

#define ADD "add"
#define LIST "list"
#define DEL "del"

/**
 * Print the command options.
 */
void print_usage(const char *fname);

/**
 * Add a new entry to the todo list.
 * Input text: the text to add
 * Return: ID of the new entry
 */
int add_entry(const char *text);

/**
 * Calculates, and returns the length of the longest entry
 * Return: the length of the longest entry
 */
int calc_maxlen();

/**
 * Return: the number of entries in the list
 */
int get_num_entries();

/**
 * List the entries in the todo list.
 * Input entries: list to store the entries in
 */
void list_entries(char **entries);

/**
 * Input id: ID of the entry to delete
 * Return: 0 if the entry is successfully deleted
 *         1 if the entry does not exist
 */
int del_entry(const int id);

int main(int argc, char **argv)
{
	// handle arguments
	if (argc == 1) print_usage(argv[0]);
	else {
		char *command = argv[1];
		if (strcmp(command, ADD) == 0) {
			char *text = argv[2];
			if (strlen(text) >= MAXLEN) {
				printf("Entry too long! Maximum length %s characters.\n", MAXLEN-1);
			int id = add_entry(text);
			printf("Stored entry, ID %d\n", id);
		}
		else if (strcmp(command, LIST) == 0) {
			int num_entries = get_num_entries();
			char entries[num_entries][calc_maxlen()];
			list_entries((char **) entries);
			for (int i = 0; i < num_entries; i++) {
				puts(entries[i]);
			}
		}
		else if (strcmp(command, DEL) == 0) {
			int id = atoi(argv[2]);
			int err = del_entry(id);
			if (!err) printf("Entry %d deleted\n", id);
		}
	}

}

void print_usage(const char *fname)
{
	printf("Usage: \n");
	printf("%s "ADD" <line>     -- add a new todo item\n", fname);
	printf("%s "LIST"           -- list todo items\n", fname);
	printf("%s "DEL" <id>       -- delete a todo item\n", fname);
}

int add_entry(const char *text)
{
	FILE *fp;
	fp = fopen(FNAME, "a+");

	// get ID to insert
	char tmp[100] = {0,};
	while (fgets(tmp, 100, fp) != NULL) {} // skip to last line
	int id;
	sscanf(tmp, "%*d %d", &id);
	id++; // id is now the correct ID to insert

	fprintf(fp, "%d %d %s", strlen(text), id, text);

	fclose(fp);

	return id;
}

int calc_maxlen()
{
	FILE *fp;
	fp = fopen(FNAME, "a+");

	int maxlen = 0;
	char tmp[MAXLEN] = {0,};
	while (fgets(tmp, MAXLEN, fp) != NULL) {
		int len;
		sscanf(tmp, "%d", &len);
		if (len > maxlen) maxlen = len;
	}

	fclose(fp);
	return maxlen;
}

int get_num_entries()
{
	FILE *fp;
	fp = fopen(FNAME, "a+");

	int num_entries = 0;
	char tmp[MAXLEN] = {0,};
	while (fgets(tmp, MAXLEN, fp) != NULL) {
		int len;
		sscanf(tmp, "%d", &len);
		if (len > maxlen) maxlen = len;
	}
}

