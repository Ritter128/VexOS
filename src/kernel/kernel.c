#include "kernel.h"

/* Add support for numbers greater than 9 */

/* WE NEED */
// User input
// Time
// Check out https://wiki.osdev.org/Main_Page

#define MAKE_INT_TO_STRING_BIND(x, c) case x: return c; break;

struct VgaEntry* vgaBuffer = (struct VgaEntry*) 0xB8000;
size_t currentEntry = 0;

static inline int StringLength(uint8_t* str) {
    size_t length = 0;
    while (str[length] != '\0')
        length++;
    return length;
}

// What. The. Actual. F***.
static inline int8_t* IntToString(int16_t number) {
    switch (number)
    {
        MAKE_INT_TO_STRING_BIND(0x0, "0"); // I
        MAKE_INT_TO_STRING_BIND(0x1, "1");
        MAKE_INT_TO_STRING_BIND(0x2, "2");
        MAKE_INT_TO_STRING_BIND(0x3, "3");
        MAKE_INT_TO_STRING_BIND(0x4, "4"); // want
        MAKE_INT_TO_STRING_BIND(0x5, "5");
        MAKE_INT_TO_STRING_BIND(0x6, "6");
        MAKE_INT_TO_STRING_BIND(0x7, "7");
        MAKE_INT_TO_STRING_BIND(0x8, "8"); // to
        MAKE_INT_TO_STRING_BIND(0x9, "9");
        MAKE_INT_TO_STRING_BIND(0xA, "10");
        MAKE_INT_TO_STRING_BIND(0xB, "11");
        MAKE_INT_TO_STRING_BIND(0xC, "12");
        MAKE_INT_TO_STRING_BIND(0xD, "13");
        MAKE_INT_TO_STRING_BIND(0xE, "14");
        MAKE_INT_TO_STRING_BIND(0xF, "15");  // die
        MAKE_INT_TO_STRING_BIND(0x10, "16");
        MAKE_INT_TO_STRING_BIND(0x11, "17");
        MAKE_INT_TO_STRING_BIND(0x12, "18");
        MAKE_INT_TO_STRING_BIND(0x13, "19");
        MAKE_INT_TO_STRING_BIND(0x14, "20");
        MAKE_INT_TO_STRING_BIND(0x15, "21");
        MAKE_INT_TO_STRING_BIND(0x16, "22");
        MAKE_INT_TO_STRING_BIND(0x17, "23");
        MAKE_INT_TO_STRING_BIND(0x18, "24");
        MAKE_INT_TO_STRING_BIND(0x19, "25"); // very // hard
        MAKE_INT_TO_STRING_BIND(0x1A, "26");
        MAKE_INT_TO_STRING_BIND(0x1B, "27"); // I
        MAKE_INT_TO_STRING_BIND(0x1C, "28");
        MAKE_INT_TO_STRING_BIND(0x1D, "29");
        MAKE_INT_TO_STRING_BIND(0x1E, "30");
        MAKE_INT_TO_STRING_BIND(0x1F, "31"); // want
        MAKE_INT_TO_STRING_BIND(0x20, "32");
        MAKE_INT_TO_STRING_BIND(0x21, "33");
        MAKE_INT_TO_STRING_BIND(0x22, "34");
        MAKE_INT_TO_STRING_BIND(0x23, "35"); // to
        MAKE_INT_TO_STRING_BIND(0x24, "36");
        MAKE_INT_TO_STRING_BIND(0x25, "37");
        MAKE_INT_TO_STRING_BIND(0x26, "38");
        MAKE_INT_TO_STRING_BIND(0x27, "39");
        MAKE_INT_TO_STRING_BIND(0x28, "40");
        MAKE_INT_TO_STRING_BIND(0x29, "41");
        MAKE_INT_TO_STRING_BIND(0x2A, "42");  // die
        MAKE_INT_TO_STRING_BIND(0x2B, "43");
        MAKE_INT_TO_STRING_BIND(0x2C, "44");
        MAKE_INT_TO_STRING_BIND(0x2D, "45");
        MAKE_INT_TO_STRING_BIND(0x2E, "46");
        MAKE_INT_TO_STRING_BIND(0x2F, "47");
        MAKE_INT_TO_STRING_BIND(0x30, "48");
        MAKE_INT_TO_STRING_BIND(0x31, "49");
        MAKE_INT_TO_STRING_BIND(0x32, "50");
        MAKE_INT_TO_STRING_BIND(0x33, "51");
        MAKE_INT_TO_STRING_BIND(0x34, "52"); // now
        MAKE_INT_TO_STRING_BIND(0x35, "53");
    }
}

static inline void VXInsert(uint8_t x, uint8_t y, struct VgaEntry colorChar) {
    vgaBuffer[x + (VGA_WIDTH * y)] = colorChar;
}

static inline void VXClear() {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vgaBuffer[i] = (struct VgaEntry) {'\0', VGA_COLOR_BLACK};
    }
    currentEntry = 0;
}
// BRUH
static inline void VXVariable(int8_t x, int8_t y, int val, struct VgaEntry colorChar) {
    int8_t* valText = IntToString(val);
    VXInsert(x, y, colorChar);
    VXInsert(x + 2, y, (struct VgaEntry){valText[0], VGA_COLOR_WHITE});
    VXInsert(x + 3, y, (struct VgaEntry){valText[1], VGA_COLOR_WHITE});
    if (StringLength(valText) > 2) {
        VXInsert(x + 4, y, (struct VgaEntry){valText[2], VGA_COLOR_WHITE});
    }
}

static inline void VXBoard(uint8_t x, uint8_t y, int a, int b, int c) {
    VXVariable(x, y, a, (struct VgaEntry){'A', VGA_COLOR_GREEN});
    VXVariable(x + VGA_WIDTH, y, b, (struct VgaEntry){'B', VGA_COLOR_RED});
    VXVariable(x + (2*VGA_WIDTH), y, c, (struct VgaEntry){'C', VGA_COLOR_BLUE});   
}

static inline void VXGraph(uint8_t rows, uint8_t columns, uint8_t* rowNomen) {
    // The top bar for our rows
    if (rows > 9 || columns > 9) {
        VXInsert(0, 0, (struct VgaEntry){'E', VGA_COLOR_RED});
        VXInsert(1, 0, (struct VgaEntry){'R', VGA_COLOR_RED});
        VXInsert(2, 0, (struct VgaEntry){'R', VGA_COLOR_RED});
    }
    else 
    {
        for (int numRows = 0; numRows < rows + 1; numRows++) {
            // 123...
            VXInsert(numRows + 1, 0, (struct VgaEntry){*IntToString(numRows+1), VGA_COLOR_WHITE});
        }
        for (int numCols = 0; numCols < columns; numCols++) {
            VXInsert(0, numCols + 1, (struct VgaEntry){*IntToString(numCols+1), VGA_COLOR_WHITE});
            if (numCols > 9) {
                VXInsert(1, numCols, (struct VgaEntry){*(IntToString(numCols+1)+1), VGA_COLOR_WHITE});
            }   
        }
        VXInsert(rows+ 1, 0, (struct VgaEntry){rowNomen[0], VGA_COLOR_RED});
        VXInsert(0, columns + 1, (struct VgaEntry){rowNomen[1], VGA_COLOR_BLUE});
    }
}

// ACTUALLY WORKS!!!!
static inline void VXWrite(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        VXInsert(i + currentEntry, 0, (struct VgaEntry) {data[i], VGA_COLOR_WHITE});
    }
    currentEntry += size;
}

static inline void VXWriteLine(const char* data, size_t size) {
    VXWrite(data, size);
    currentEntry += VGA_WIDTH;
    currentEntry -= size;
}

// Doesn't work idk why
static inline void VXNewLine() {
    currentEntry += VGA_WIDTH;
}

void kernel_main() {
    VXClear();
    VXGraph(6, 6, "AB");
    VXBoard(10, 2, 34, 12, 9);
}