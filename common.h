#define OP_FILE_NAME "convertedImage.txt"

/* Bytes per Pixel Declaration */
#define IP_BPP 3  //RGB888
#define OP_BPP 8  //RGBA each stored in 2 Byte

#define TXT_PXL_SIZE 9 // including space

struct rgbPixel {
	uint8_t R;
	uint8_t G;
	uint8_t B;
};

int convertRGBToTXT (uint8_t** buf, uint8_t** opBuf, long int fsize);
