#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

const uint8_t alpha = 0xFF;

int convertRGBToTXT (uint8_t** buf, uint8_t** opBuf, long int fsize)
{
	int ret = 0, i = 0;
	long int opsize_max = 0;
	uint8_t str[TXT_PXL_SIZE] = {0};
	struct rgbPixel *pix = NULL;

	opsize_max = (OP_BPP + 1) * (fsize / IP_BPP);	
	*opBuf = (uint8_t*) malloc (sizeof(uint8_t) * (opsize_max));
	if (!*opBuf) {
		printf ("%s malloc Failure!\n", __func__);
		ret = -1;
		goto endR2T;
	}

	/* reusing variable */
	opsize_max = (fsize / IP_BPP);
	pix = (struct rgbPixel*)*buf;

	/* If input Image is RGBA change Pixel struct and alpha with pix->alpha */
	for (i = 0; i < opsize_max; i++, pix++) {
		sprintf ((char*)str, "%02x%02x%02x%02x ", pix->R, pix->G, pix->B, alpha); /* Slower than my Grand mother */
		memcpy ((*opBuf + (i * TXT_PXL_SIZE)), str, TXT_PXL_SIZE);
	}

endR2T:
	if (!*opBuf) { free(*opBuf); *opBuf = NULL; }
	return ret;
}
