#include <stdio.h>
#include <stdlib.h>

void bresenham_line(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int steep = dy > dx;

    if (steep) {
        int temp = x0;
        x0 = y0;
        y0 = temp;
        temp = x1;
        x1 = y1;
        y1 = temp;
    }

    if (x0 > x1) {
        int temp = x0;
        x0 = x1;
        x1 = temp;
        temp = y0;
        y0 = y1;
        y1 = temp;
    }

    int dx1 = x1 - x0;
    int dy1 = abs(y1 - y0);
    int error = dx1 / 2;
    int ystep = (y0 < y1) ? 1 : -1;
    int y = y0;

    for (int x = x0; x <= x1; x++) {
        if (steep) {
            printf("(%d, %d)\n", y, x);
        } else {
            printf("(%d, %d)\n", x, y);
        }

        error -= dy1;
        if (error < 0) {
            y += ystep;
            error += dx1;
        }
    }
}

int main() {
    int x0 = 1, y0 = 1;
    int x1 = 8, y1 = 5;

    printf("Pontos da linha:\n");
    bresenham_line(x0, y0, x1, y1);

    return 0;
}
