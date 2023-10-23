#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include "screenshot.h"

Screenshot takeScreenshot() {
    Screenshot result;

    // Take a screenshot of the entire screen
    HDC hdc = GetDC(NULL);
    int screen_width = GetDeviceCaps(hdc, HORZRES);
    int screen_height = GetDeviceCaps(hdc, VERTRES);
    HDC hdcMem = CreateCompatibleDC(hdc);
    HBITMAP hBitmap = CreateCompatibleBitmap(hdc, screen_width, screen_height);
    SelectObject(hdcMem, hBitmap);
    BitBlt(hdcMem, 0, 0, screen_width, screen_height, hdc, 0, 0, SRCCOPY);

    // Get the bitmap data
    hBitmap = (HBITMAP)GetCurrentObject(hdcMem, OBJ_BITMAP);
    BITMAP bmp;
    GetObject(hBitmap, sizeof(BITMAP), &bmp);

    result.width = bmp.bmWidth;
    result.height = bmp.bmHeight;
    result.data = (unsigned char*)malloc(bmp.bmWidth * bmp.bmHeight * 4);

    if (result.data) {
        GetDIBits(hdc, hBitmap, 0, bmp.bmHeight, result.data, (BITMAPINFOHEADER*)&bmp, DIB_RGB_COLORS);
    }

    // Clean up resources
    DeleteObject(hBitmap);
    DeleteDC(hdcMem);
    ReleaseDC(NULL, hdc);

    return result;
}

void saveScreenshotAsJpg(const Screenshot* screenshot, const char* filename, int quality) {
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE* outfile;
    JSAMPROW row_pointer[1];

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    if ((outfile = fopen(filename, "wb")) == NULL) {
        fprintf(stderr, "Can't open %s for writing.\n", filename);
        return;
    }

    jpeg_stdio_dest(&cinfo, outfile);

    cinfo.image_width = screenshot->width;
    cinfo.image_height = screenshot->height;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;
    jpeg_set_defaults(&cinfo);

    jpeg_set_quality(&cinfo, quality, TRUE);
    jpeg_start_compress(&cinfo, TRUE);

    while (cinfo.next_scanline < cinfo.image_height) {
        row_pointer[0] = &screenshot->data[cinfo.next_scanline * screenshot->width * 3];
        (void)jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    fclose(outfile);
    jpeg_destroy_compress(&cinfo);
}
