#include <windows.h>

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

#include <windows.h>
#include <mmsystem.h>

// Callback function for audio capture
void CALLBACK waveInProc(HWAVEIN hwi, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2) {
    // Handle audio capture events
}

void CaptureAudio() {
    HWAVEIN hWaveIn;
    WAVEFORMATEX waveFormat;
    WAVEHDR waveHeader;
    char buffer[1024];

    // Define wave format
    waveFormat.wFormatTag = WAVE_FORMAT_PCM;
    waveFormat.nChannels = 2;
    waveFormat.nSamplesPerSec = 44100;
    waveFormat.nAvgBytesPerSec = 44100 * 2 * 2;
    waveFormat.nBlockAlign = 2 * 2;
    waveFormat.wBitsPerSample = 16;
    waveFormat.cbSize = 0;

    // Open audio input device
    waveInOpen(&hWaveIn, WAVE_MAPPER, &waveFormat, (DWORD_PTR)waveInProc, 0, CALLBACK_FUNCTION);

    // Prepare wave header
    waveHeader.lpData = buffer;
    waveHeader.dwBufferLength = sizeof(buffer);
    waveHeader.dwFlags = 0;
    waveHeader.dwLoops = 0;
    waveInPrepareHeader(hWaveIn, &waveHeader, sizeof(WAVEHDR));

    // Add buffer and start capturing
    waveInAddBuffer(hWaveIn, &waveHeader, sizeof(WAVEHDR));
    waveInStart(hWaveIn);

    // Capture for a duration or until stopped
    Sleep(10000); // Capture for 10 seconds

    // Clean up
    waveInStop(hWaveIn);
    waveInUnprepareHeader(hWaveIn, &waveHeader, sizeof(WAVEHDR));
    waveInClose(hWaveIn);
}