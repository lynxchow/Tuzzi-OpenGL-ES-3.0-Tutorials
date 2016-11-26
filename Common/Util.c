//
//  Util.cpp
//  Common
//
//  Created by Pocoyo Chow on 24/11/2016.
//  Copyright © 2016 pocoyo. All rights reserved.
//

#include "Util.h"
#include <stdlib.h>

void utilLog(const char *formatStr, ...)
{
    va_list params;
    char buf[BUFSIZ];
    
    va_start(params, formatStr);
    vsprintf(buf, formatStr, params);
    
#ifdef ANDROID
    __android_log_print(ANDROID_LOG_INFO, "esUtil" , "%s", buf);
#else
    printf("%s", buf);
#endif
    va_end (params);
}

const char *fileOpen(const char *fileName)
{
    return getBundleFileName(fileName);
}

unsigned char *loadTGA(const char *fileName, int *width, int *height)
{
    unsigned char *buffer;
    File *fp;
    TGA_HEADER Header;
    unsigned long bytesRead;
    int bytePerSize;
    long imageSize;
    
    // Open the file for reading
    fp = fopen(fileName, "rb");
    
    if (fp == NULL)
    {
        // Log error as 'error in opening the input file from apk'
        utilLog("loadTGA FAILED to load : { %s }\n", fileName);
        return NULL;
    }
    
    bytesRead = fread(&Header, sizeof(TGA_HEADER), 1, fp);
    
    *width = Header.Width;
    *height = Header.Height;
    
    bytePerSize = Header.ColorDepth / 8;
    imageSize = Header.Width * Header.Height * bytePerSize;
    
    if (Header.ColorDepth == 8 || Header.ColorDepth == 24 || Header.ColorDepth == 32)
    {
        int bytesToRead = sizeof(char) * (*width) * (*height) * Header.ColorDepth / 8;
        
        // Allocate the image data buffer
        buffer = (unsigned char *) malloc(bytesToRead);
        
        if (buffer)
        {
            bytesRead = fread(buffer, bytesToRead, 1, fp);
            fclose(fp);
    
            for (int i = 0; i < imageSize; i+= bytePerSize)
            {
                unsigned char tmp = buffer[i];
                buffer[i] = buffer[i + 2];
                buffer[i + 2] = tmp;
            }
            return buffer;
        }
    }
    
    
    
    
    return NULL;
}
