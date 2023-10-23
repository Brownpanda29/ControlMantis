#ifndef SCREENSHOT_H
#define SCREENSHOT_H

typedef struct {
    unsigned char* data;
    int width;
    int height;
} Screenshot;

Screenshot takeScreenshot();
void saveScreenshotAsJpg(const Screenshot* screenshot, const char* filename, int quality);

#endif // SCREENSHOT_H
