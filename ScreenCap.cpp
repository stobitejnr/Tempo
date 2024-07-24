#include <windows.h>

using namespace std;

// Capture a screen and save to a bitmap file
void CaptureScreen(const char* filename) {
    // Get device context of the screen
    HDC hScreenDC = GetDC(NULL);
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);

    // Get the screen resolution
    int width = GetDeviceCaps(hScreenDC, HORZRES);
    int height = GetDeviceCaps(hScreenDC, VERTRES);

    // Create a compatible bitmap and select it into the memory DC
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
    SelectObject(hMemoryDC, hBitmap);

    // BitBlt screen to memory DC
    BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY);

    // Save the bitmap to file
    BITMAPFILEHEADER bfHeader;
    BITMAPINFOHEADER biHeader;
    BITMAP bitmap;

    GetObject(hBitmap, sizeof(BITMAP), &bitmap);
    DWORD dwBmpSize = ((bitmap.bmWidth * bitmap.bmBitsPixel + 31) / 32) * 4 * bitmap.bmHeight;

    HANDLE hDIB = GlobalAlloc(GHND, dwBmpSize + sizeof(BITMAPINFOHEADER));
    char* lpbitmap = (char*)GlobalLock(hDIB);

    GetDIBits(hScreenDC, hBitmap, 0, (UINT)bitmap.bmHeight, lpbitmap + sizeof(BITMAPINFOHEADER), (BITMAPINFO*)&biHeader, DIB_RGB_COLORS);

    HANDLE hFile = CreateFile(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    DWORD dwSizeofDIB = dwBmpSize + sizeof(BITMAPINFOHEADER);
    bfHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    bfHeader.bfSize = dwSizeofDIB + sizeof(BITMAPFILEHEADER);
    bfHeader.bfType = 0x4D42; //BM

    DWORD dwBytesWritten;
    WriteFile(hFile, (LPSTR)&bfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
    WriteFile(hFile, (LPSTR)&biHeader, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
    WriteFile(hFile, lpbitmap + sizeof(BITMAPINFOHEADER), dwBmpSize, &dwBytesWritten, NULL);

    GlobalUnlock(hDIB);
    GlobalFree(hDIB);
    CloseHandle(hFile);

    // Clean up
    DeleteObject(hBitmap);
    DeleteDC(hMemoryDC);
    ReleaseDC(NULL, hScreenDC);
}