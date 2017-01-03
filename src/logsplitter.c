#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define generatedFileSize 15

FILE *generatedFiles[generatedFileSize] = {0};

char* integertoascii(int val, int base){

	static char buf[32] = {0};

	int i = 30;

	for(; val && i ; --i, val /= base)

		buf[i] = "0123456789abcdef"[val % base];

	return &buf[i+1];
}

char *generateFilename(char* basename, int num) {
	char *fileextension = integertoascii(num, 10);

	const char *delim = ".";

	char *token;
	char *tempname = malloc(strlen(basename));
	strcpy(tempname, basename);
	token = strtok(tempname, delim);

	char *out = calloc(100, sizeof(char));
	char *tokentmp;
	strcat(out, token);
	strcat(out, delim);
	int count = 0;
	while(token != NULL)
 	{
		tokentmp = token;
    token = strtok(NULL, delim);
		if (count > 1) {
			if (token != NULL) {
				strcat(out, delim);
			}
		}
		if (count > 0) {
			if (token != NULL) {
				strcat(out, tokentmp);
			}
		}

		count++;
 	}
	strcat(out, fileextension);
	strcat(out, delim);
	strcat(out, tokentmp);
	free(tempname);

	return out;
}

void split(char *filename) {
	int maxSize = 119000;
	int cnt = 1;
	int pos = 0;
	int prevPos = 0;
	int seeker = 0;

	FILE *fp = fopen(filename, "rb");
	fseek(fp, 0, SEEK_END);
	int filesize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	while(filesize >= pos + seeker + 1) {
		fseek(fp, maxSize + pos, SEEK_CUR);
		for (int i = 0; i < maxSize; i++) {
			if (fgetc(fp) == '\n') {
				seeker = i;
				pos = ftell(fp);
				break;
			}
			fseek(fp, -2, SEEK_CUR);
		}

		char *fileinput = malloc(maxSize + 1);
		fseek(fp, prevPos, SEEK_SET);
		int size = fread(fileinput, 1, pos - prevPos, fp);
		fileinput[size] = '\0';

		char *tmp = generateFilename(filename, cnt);
		FILE *splittedfile = fopen(tmp, "w+");
		fprintf(splittedfile, "%s", fileinput);
		generatedFiles[cnt - 1] = splittedfile;
		free(tmp);
		free(fileinput);

		prevPos = pos;
		cnt++;
	}
}

void addClose() {
	int generateMarker = 0;
	for (int i = 0; i < generatedFileSize; i++) {
		if (generatedFiles[i] != 0) {
			char *lookstring1 = "[CODE]";
			char *lookstring2 = "[/CODE]";
			char *fileinput = calloc(120010, 1);
			fseek(generatedFiles[i], 0, SEEK_SET);
			int size = fread(fileinput, 1, 120000, generatedFiles[i]);
			fileinput[size] = '\0';
			if (generateMarker == 1) {
				char *tmpinput = malloc(120010);
				strcpy(tmpinput, fileinput);
				strcpy(fileinput, lookstring1);
				strcat(fileinput, tmpinput);
				generateMarker = 0;
				free(tmpinput);
			}

			char *code = fileinput;
			char *buf1 = 0;
			while (code = strstr(code + 1, lookstring1)) {
				buf1 = code;
			}

			char *codeclose = fileinput;
			char *buf2 = 0;
			while (codeclose = strstr(codeclose + 1, lookstring2)) {
				buf2 = codeclose;
			}

			if (buf2 < buf1) {
				strcat(fileinput, lookstring2);
				generateMarker = 1;
			}
			rewind(generatedFiles[i]);
			fprintf(generatedFiles[i], "%s", fileinput);

			free (fileinput);
			fclose(generatedFiles[i]);
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Only provide 1 file as argument\r\n");
		return 1;
	}

	FILE *fp;
	fp = fopen(argv[1], "r");

	if (fp == 0) {
		printf("Error opening file\r\n");
		return 1;
	}

	split(argv[1]);
	addClose();

	return 0;
}
