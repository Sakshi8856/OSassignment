#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10
#define PAGE_REFERENCES 15

void fifo_page_replacement(int pages[], int n, int frames) {
    int page_frame[MAX_FRAMES] = {-1}; // To store the pages in frames
    int page_faults = 0;                // Count of page faults
    int front = 0;                       // Index to keep track of the oldest page

    printf("Page Reference String: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n");

    // Simulating the FIFO page replacement
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0; // Flag to check if page is found in frames

        // Check if the page is already in one of the frames
        for (int j = 0; j < frames; j++) {
            if (page_frame[j] == page) {
                found = 1; // Page is found
                break;
            }
        }

        // If page is not found, it is a page fault
        if (!found) {
            page_faults++;
            // Replace the oldest page using FIFO
            page_frame[front] = page;
            front = (front + 1) % frames; // Move to the next frame in FIFO order

            // Print the current state of the frames
            printf("Page Fault! Frames: ");
            for (int j = 0; j < frames; j++) {
                if (page_frame[j] != -1) {
                    printf("%d ", page_frame[j]);
                }
            }
            printf("\n");
        } else {
            printf("Page Hit: %d\n", page);
        }
    }

    printf("Total Page Faults: %d\n", page_faults);
}

int main() {
    int pages[PAGE_REFERENCES] = {3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6};
    int frames;

    printf("Enter the number of memory frames (n): ");
    scanf("%d", &frames);

    if (frames > MAX_FRAMES) {
        printf("Error: Maximum number of frames is %d.\n", MAX_FRAMES);
        return 1;
    }

    fifo_page_replacement(pages, PAGE_REFERENCES, frames);

    return 0;
}

