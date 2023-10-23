#include "screenshot.h"

int main() {
    // Capture a screenshot
    Screenshot xscrn = takeScreenshot();

    // Check if the screenshot was successfully captured
    if (xscrn.data) {
        // Send the `xscrn.data`, `xscrn.width`, and `xscrn.height` to the server.
        // You can use a network communication library or method to send this data.

        // Clean up the screenshot data when done.
        free(xscrn.data);
    } else {
        // Handle the case where the screenshot could not be captured
    }

    return 0;
}
