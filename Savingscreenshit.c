#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assuming you have received `xscrn.data`, `xscrn.width`, and `xscrn.height` from the client
unsigned char* xscrn_data = /* received xscrn.data */;
int xscrn_width = /* received xscrn.width */;
int xscrn_height = /* received xscrn.height */;

// Create and write the received data to "screenshot.jpg"
FILE* outfile = fopen("screenshot.jpg", "wb");
if (outfile) {
    fwrite(xscrn_data, 1, xscrn_width * xscrn_height * 3, outfile);
    fclose(outfile);
}

// Now "screenshot.jpg" contains the screenshot data received from the client.
