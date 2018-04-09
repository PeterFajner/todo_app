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
 *
 * All files are opened in a+ mode so that they are created if they
 * don't exist.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include PLATFORM

#define FNAME "db.txt"
#define TMP_FNAME "db.txt.tmp"
#define MAXLEN 1000 // maximum allowed length of a line
#define PADDING "5" // number of spaces to pad the ID when listing entries

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
 * Input entries: pointer to an array to store the entries in
 * Input maxlen: maximum length of an individual entry
 */
void list_entries(char *entries, const int maxlen);

/**
 * Input id: ID of the entry to delete
 * Return: 0 if the entry is successfully deleted
 *        -1 if the entry does not exist
 */
int del_entry(const int id);

int main(int argc, char **argv)
{
	// handle arguments
	if (argc == 1) print_usage(argv[0]);
	else {
		char *command = argv[1];
		if (strcmp(command, ADD) == 0) {
			char text[MAXLEN];
			strcpy(text, argv[2]);
			for (int i = 3; i < argc; i++) {
				strcat(text, " ");
				strcat(text, argv[i]);
			}
			if (strlen(text) >= MAXLEN) {
				printf("Entry too long! Maximum length %d characters.\n", MAXLEN-1);
			}
			int id = add_entry(text);
			printf("Stored entry, ID %d\n", id);
		}
		else if (strcmp(command, LIST) == 0) {
			int num_entries = get_num_entries();
			int maxlen = MAXLEN; //calc_maxlen();
			char *entries = malloc(num_entries*maxlen);
			list_entries(entries, maxlen);
			printf("%"PADDING"s Entry\n", "ID");
			for (int i = 0; i < num_entries; i++) {
				int id;
				char *str = entries+i*maxlen;
				char str_without_id[strlen(str)+1];
				sscanf(str, "%d %[^\n]", &id, str_without_id);
				printf("%"PADDING"d %s\n", id, str_without_id);
			}
			free(entries);
		}
		else if (strcmp(command, DEL) == 0) {
			if (argc != 3) {
				print_usage(argv[0]);
				return EXIT_FAILURE;
			}
			int id = atoi(argv[2]);
			int err = del_entry(id);
			if (!err) printf("Entry %d deleted\n", id);
			else printf("Could not delete entry %d, does it exist?\n", id);
		}
		else print_usage(argv[0]);
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
	int success = sscanf(tmp, "%*d %d", &id);
	if (success == 0 || success == EOF) id = 0;
	id++; // id is now the correct ID to insert

	fprintf(fp, "%lu %d %s\n", strlen(text), id, text);

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
	char tmp[MAXLEN];
	while (fgets(tmp, MAXLEN, fp) != NULL) {
		num_entries++;
	}
	return num_entries;
	fclose(fp);
}

void list_entries(char *entries, const int maxlen)
{
	FILE *fp;
	fp = fopen(FNAME, "a+");

	int entry_num = 0;
	char tmp_str[MAXLEN];
	char tmp_str_formatted[MAXLEN]; // with string length removed
	while (fgets(tmp_str, maxlen, fp) != NULL) {
		sscanf(tmp_str, "%*d %[^\n]", tmp_str_formatted); // remove string length
		strcpy(entries + entry_num*maxlen, tmp_str_formatted);
		entry_num++;
	}

	fclose(fp);
}

int del_entry(const int id)
{
	FILE *fp;
	FILE *tmpfp;
	fp = fopen(FNAME, "a+");
	tmpfp = fopen(TMP_FNAME, "w");

	int return_code = -1;

	char tmp[MAXLEN] = {0,};
	while (fgets(tmp, MAXLEN, fp) != NULL) {
		int this_id;
		sscanf(tmp, "%*d %d", &this_id);
		if (this_id != id) fputs(tmp, tmpfp);
		else return_code = 0;
	}

	fclose(fp);
	fclose(tmpfp);
	remove(FNAME);
	rename(TMP_FNAME, FNAME);

	return return_code;
}

