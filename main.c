/* Program to convert RGB to RGBA TXT file */

#include <stdio.h>
#include <stdlib.h>
#include "common.h"

/* Function Declarations */
int getImgFromFile (uint8_t** buf, char* filename, long int* fsize);
int writeToFile (uint8_t* buf, char* filename, long int fsize);
int processArgs (int argc, char *argv[], char **filename);
void printUsage ();


int main (int argc, char **argv)
{
	int ret = 0;
	long int fsize = 0, opsize = 0;
	char* filename = NULL;
	uint8_t* buf = NULL, * opBuf = NULL;

	/* Process CMD Line arguments and get Filename */
	ret = processArgs(argc, argv, &filename);
	if (ret) {
		printf ("Error in CMDLINE arguments\n");
		goto deinit;
	}

	/*get Image Buffers from File */
	ret = getImgFromFile (&buf, filename, &fsize);
	if (ret) {
		printf ("Error in reading File : %s\n", filename);
		goto deinit;
	}

	/* Conversion Logic for RGB to TXT */
	ret = convertRGBToTXT (&buf, &opBuf, fsize);
	if (ret) {
		printf ("Error in RGB Conversion\n");
		goto deinit;
	}

	opsize = (OP_BPP + 1) * (fsize / IP_BPP);
	/* Write buffer to file */
	ret = writeToFile (opBuf, OP_FILE_NAME, opsize);
	if (ret) {
		printf ("Error in Writing File : %s\n", OP_FILE_NAME);
		goto deinit;
	}

deinit:
	printf("\n== DONE ==\n");
	if (!buf)   {free(buf);   buf = NULL;}
	if (!opBuf) {free(opBuf); opBuf = NULL;}

	return ret;
}

int processArgs (int argc, char *argv[], char **filename)
{
	if (argc != 2) {
		printUsage();
		return -1;
	} else {
		*filename = argv[1];
		return 0;
	}
}

void printUsage ()
{
	printf ("Program to convert RGB to RGBA TXT file\n");
	printf ("USAGE: ./rgb2txt <filename>\n");
}

int getImgFromFile (uint8_t** buf, char* filename, long int* fsize)
{
	FILE *fp = NULL;
	int ret = 0;

	fp = fopen (filename, "rb");
	if (fp == NULL) {
		printf ("%s File Open error!\n", __func__);
		ret = -1;
		goto endGetImage;
	}

	fseek (fp, 0, SEEK_END);
	*fsize = ftell(fp);
	rewind (fp);

	printf ("Reading File [%s] : %ld bytes\n", filename, *fsize);

	*buf = (uint8_t*) malloc (sizeof(uint8_t) * (*fsize));
	if (!*buf) {
		printf ("%s malloc Failure!\n", __func__);
		ret = -1;
		goto endGetImage;
	}

	if (fread (*buf, *fsize, 1, fp) != 1) {
		printf ("%s File read error!\n", __func__);
		ret = -1;
		goto endGetImage;
	}

endGetImage:
	if (!fp)   { fclose(fp); fp = NULL; }
	if (!*buf) { free(*buf); *buf = NULL; }
	return ret;
}

int writeToFile (uint8_t* buf, char* filename, long int fsize)
{
	FILE *fp = NULL;
	int ret = 0;

	fp = fopen (filename, "wb");
	if (!fp) {
		printf ("%s File Open error!\n", __func__);
		ret = -1;
		goto endSetImage;
	}

	if (fwrite (buf, 1, fsize, fp) != fsize) {
		printf ("%s File Write error!\n", __func__);
		ret = -1;
		goto endSetImage;
	}


endSetImage:
	if (!fp) { fclose(fp); fp = NULL; }
	return ret;
}
