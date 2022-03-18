// BMP-related data types based on Microsoft's own

#include <stdint.h>

/**
 * Common Data Types
 *
 * The data types in this section are essentially aliases for C/C++
 * primitive data types.
 *
 * Adapted from http://msdn.microsoft.com/en-us/library/cc230309.aspx.
 * See http://en.wikipedia.org/wiki/Stdint.h for more on stdint.h.
 */
typedef uint8_t  BYTE;
typedef uint32_t DWORD;
typedef int32_t  LONG;
typedef uint16_t WORD;

/**
 * BITMAPFILEHEADER
 *
 * The BITMAPFILEHEADER structure contains information about the type, size,
 * and layout of a file that contains a DIB [device-independent bitmap].
 *
 * Adapted from http://msdn.microsoft.com/en-us/library/dd183374(VS.85).aspx.
 */
typedef struct
{
    WORD   bfType;//Сигнатура(уникальная посл битов, которая определяет что это .bmp)
    DWORD  bfSize;//размер заголовка(14 байт)
    WORD   bfReserved1;//пустые биты (их знач = 0)
    WORD   bfReserved2;//пустые биты (их знач = 0)
    DWORD  bfOffBits;//значение через которое нужно переступить чтобы начать работать с изображением(54 байта) 
} __attribute__((__packed__))
BITMAPFILEHEADER;

/**
 * BITMAPINFOHEADER
 *
 * The BITMAPINFOHEADER structure contains information about the
 * dimensions and color format of a DIB [device-independent bitmap].
 *
 * Adapted from http://msdn.microsoft.com/en-us/library/dd183376(VS.85).aspx.
 */
typedef struct
{
    DWORD  biSize;//размер заголовка(40 байт)
    LONG   biWidth;//ширина изобрадения в пикселях
    LONG   biHeight;//высота изображения в пикселях
    WORD   biPlanes;//по умолчанию = 1. Рамка вокруг изображения
    WORD   biBitCount;//количество битов на один пиксель
    DWORD  biCompression;//сжатие (по умолчанию = 1)
    DWORD  biSizeImage;//размер изо в байтах
    LONG   biXPelsPerMeter;//разрешение на метр по Х
    LONG   biYPelsPerMeter;//рарешение на метр по Y
    DWORD  biClrUsed;//количество цветов которое было использовано
    DWORD  biClrImportant;//количество важных цветов (по умолчанию = 0)
} __attribute__((__packed__))
BITMAPINFOHEADER;

/**
 * RGBTRIPLE
 *
 * This structure describes a color consisting of relative intensities of
 * red, green, and blue.
 *
 * Adapted from http://msdn.microsoft.com/en-us/library/aa922590.aspx.
 */
typedef struct
{
    BYTE  rgbtBlue;
    BYTE  rgbtGreen;
    BYTE  rgbtRed;
} __attribute__((__packed__))
RGBTRIPLE;
