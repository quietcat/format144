#define PROGRAM_ID "Format144 1.11"
#define PROGRAM_DATE "Oct 27, 2004"
#define COPYRIGHT "2004 Denis Petrov"
/*
Format144 - Version 1.11

MIT License

Copyright (c) 2004 Denis Petrov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winioctl.h>
#include <stdio.h>
#include <malloc.h>
#include <conio.h>

void print_error(DWORD error)
{
  LPVOID lpMsgBuf;

  FormatMessage(
      FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
      NULL,
      error,
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
      (LPTSTR) &lpMsgBuf,
      0,
      NULL
  );

  printf( "Error %d: %s\n", error, lpMsgBuf );

  LocalFree( lpMsgBuf );

}

/* 512/0x200 bytes boot sector */

char boot_sect[] =
{
0xEB,0x3C,0x90,0x4D,0x53,0x44,0x4F,0x53,0x35,0x2E,0x30,0x00,0x02,0x01,0x01,0x00,
0x02,0xE0,0x00,0x40,0x0B,0xF0,0x09,0x00,0x12,0x00,0x02,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x29,0x14,0x08,0x9E,0x20,0x4E,0x4F,0x20,0x4E,0x41,
0x4D,0x45,0x20,0x20,0x20,0x20,0x46,0x41,0x54,0x31,0x32,0x20,0x20,0x20,0x33,0xC9,
0x8E,0xD1,0xBC,0xF0,0x7B,0x8E,0xD9,0xB8,0x00,0x20,0x8E,0xC0,0xFC,0xBD,0x00,0x7C,
0x38,0x4E,0x24,0x7D,0x24,0x8B,0xC1,0x99,0xE8,0x3C,0x01,0x72,0x1C,0x83,0xEB,0x3A,
0x66,0xA1,0x1C,0x7C,0x26,0x66,0x3B,0x07,0x26,0x8A,0x57,0xFC,0x75,0x06,0x80,0xCA,
0x02,0x88,0x56,0x02,0x80,0xC3,0x10,0x73,0xEB,0x33,0xC9,0x8A,0x46,0x10,0x98,0xF7,
0x66,0x16,0x03,0x46,0x1C,0x13,0x56,0x1E,0x03,0x46,0x0E,0x13,0xD1,0x8B,0x76,0x11,
0x60,0x89,0x46,0xFC,0x89,0x56,0xFE,0xB8,0x20,0x00,0xF7,0xE6,0x8B,0x5E,0x0B,0x03,
0xC3,0x48,0xF7,0xF3,0x01,0x46,0xFC,0x11,0x4E,0xFE,0x61,0xBF,0x00,0x00,0xE8,0xE6,
0x00,0x72,0x39,0x26,0x38,0x2D,0x74,0x17,0x60,0xB1,0x0B,0xBE,0xA1,0x7D,0xF3,0xA6,
0x61,0x74,0x32,0x4E,0x74,0x09,0x83,0xC7,0x20,0x3B,0xFB,0x72,0xE6,0xEB,0xDC,0xA0,
0xFB,0x7D,0xB4,0x7D,0x8B,0xF0,0xAC,0x98,0x40,0x74,0x0C,0x48,0x74,0x13,0xB4,0x0E,
0xBB,0x07,0x00,0xCD,0x10,0xEB,0xEF,0xA0,0xFD,0x7D,0xEB,0xE6,0xA0,0xFC,0x7D,0xEB,
0xE1,0xCD,0x16,0xCD,0x19,0x26,0x8B,0x55,0x1A,0x52,0xB0,0x01,0xBB,0x00,0x00,0xE8,
0x3B,0x00,0x72,0xE8,0x5B,0x8A,0x56,0x24,0xBE,0x0B,0x7C,0x8B,0xFC,0xC7,0x46,0xF0,
0x3D,0x7D,0xC7,0x46,0xF4,0x29,0x7D,0x8C,0xD9,0x89,0x4E,0xF2,0x89,0x4E,0xF6,0xC6,
0x06,0x96,0x7D,0xCB,0xEA,0x03,0x00,0x00,0x20,0x0F,0xB6,0xC8,0x66,0x8B,0x46,0xF8,
0x66,0x03,0x46,0x1C,0x66,0x8B,0xD0,0x66,0xC1,0xEA,0x10,0xEB,0x5E,0x0F,0xB6,0xC8,
0x4A,0x4A,0x8A,0x46,0x0D,0x32,0xE4,0xF7,0xE2,0x03,0x46,0xFC,0x13,0x56,0xFE,0xEB,
0x4A,0x52,0x50,0x06,0x53,0x6A,0x01,0x6A,0x10,0x91,0x8B,0x46,0x18,0x96,0x92,0x33,
0xD2,0xF7,0xF6,0x91,0xF7,0xF6,0x42,0x87,0xCA,0xF7,0x76,0x1A,0x8A,0xF2,0x8A,0xE8,
0xC0,0xCC,0x02,0x0A,0xCC,0xB8,0x01,0x02,0x80,0x7E,0x02,0x0E,0x75,0x04,0xB4,0x42,
0x8B,0xF4,0x8A,0x56,0x24,0xCD,0x13,0x61,0x61,0x72,0x0B,0x40,0x75,0x01,0x42,0x03,
0x5E,0x0B,0x49,0x75,0x06,0xF8,0xC3,0x41,0xBB,0x00,0x00,0x60,0x66,0x6A,0x00,0xEB,
0xB0,0x4E,0x54,0x4C,0x44,0x52,0x20,0x20,0x20,0x20,0x20,0x20,0x0D,0x0A,0x52,0x65,
0x6D,0x6F,0x76,0x65,0x20,0x64,0x69,0x73,0x6B,0x73,0x20,0x6F,0x72,0x20,0x6F,0x74,
0x68,0x65,0x72,0x20,0x6D,0x65,0x64,0x69,0x61,0x2E,0xFF,0x0D,0x0A,0x44,0x69,0x73,
0x6B,0x20,0x65,0x72,0x72,0x6F,0x72,0xFF,0x0D,0x0A,0x50,0x72,0x65,0x73,0x73,0x20,
0x61,0x6E,0x79,0x20,0x6B,0x65,0x79,0x20,0x74,0x6F,0x20,0x72,0x65,0x73,0x74,0x61,
0x72,0x74,0x0D,0x0A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xAC,0xCB,0xD8,0x55,0xAA
}
;

char * buf;

#define BUF_SIZE 0x4000

int total_tracks = 80;

int main(void)
{
  char c;


  int with_errors;
  HANDLE hFloppy;
  DWORD outBytes;
  FORMAT_PARAMETERS format_parameters;
  PARTITION_INFORMATION part_info;
  DRIVE_LAYOUT_INFORMATION drive_info;
  VERIFY_INFORMATION verify_info;
  /* volume serial number as two words at boot sector pos 0x27 and 0x29 */
  WORD serial_lo, serial_hi;
  SYSTEMTIME st;

  printf(PROGRAM_ID "  " PROGRAM_DATE "  Copyright(c) " COPYRIGHT "\n");

  buf = malloc(BUF_SIZE);
  if ( !buf )
  {
    printf("Out of Memory\n");
    return 1;
  }

  /* Initialize buffer with zeros and add FAT signatures */

  {
    int i;
    for ( i = 0; i < BUF_SIZE/sizeof(DWORD); i++ )
    {
      ((DWORD*)buf)[i] = 0;
    }

    buf[0] = 0xf0; buf[1] = 0xff; buf[2] = 0xff;
    buf[0x1200] = 0xf8; buf[0x1201] = 0xff; buf[0x1202] = 0xff;
  }


  format_parameters.MediaType = F3_1Pt44_512;
  format_parameters.StartCylinderNumber = 0;
  format_parameters.EndCylinderNumber = 79;
  format_parameters.StartHeadNumber = 0;
  format_parameters.EndHeadNumber = 1;

  printf( "Formatting diskette in floppy drive A:\n"
          "WARNING: All data on the floppy disk in drive A: will be erased!\n"
          "Press Esc to exit now or any other key to continue...\n");


  do { c = getch(); } while (kbhit());
  if ( c != 0x1B ) /* No Escape */
  {

       do
       {

               with_errors = 0; /* Reset error flag */

               printf("Opening floppy drive A:...\n");

               hFloppy = CreateFile
               (
                 "\\\\.\\A:",
                 GENERIC_READ | GENERIC_WRITE,
                 FILE_SHARE_WRITE,
                 NULL,
                 OPEN_EXISTING,
                 FILE_ATTRIBUTE_NORMAL,
                 NULL
               );

               if ( hFloppy != INVALID_HANDLE_VALUE )
               {

                 do /* a fake loop so we can use 'break' */
                 {

                       int itrack;

                       /*
                          low-level floppy format
                          will write 0xF6 in all bytes
                       */

                       printf("Formatting A: 1.44M...\n");


                       /*
                         Attention - inner loop here, breaking out of it will not
                         break from the fake loop above
                       */
                       for ( itrack = 0; itrack < total_tracks; itrack++ )
                       {
                           printf("Track %d of %d\r",itrack+1,total_tracks);

                           format_parameters.StartCylinderNumber = itrack;
                           format_parameters.EndCylinderNumber = itrack;

                           if( !  DeviceIoControl
                                  (
                                    hFloppy,
                                    IOCTL_DISK_FORMAT_TRACKS,
                                    &format_parameters,
                                    sizeof(format_parameters),
                                    NULL,
                                    0,
                                    &outBytes,
                                    NULL
                                  ) )
                           {
                             print_error(GetLastError());
                             with_errors = 1;
                             break;
                           }
                       }

                       /*
                          We broke out of the inner loop above,
                          need to break from the fake loop
                       */
                       if ( with_errors ) break;

                       /* create filesystem */

                       printf("Writing boot sector...\n");

                       /* create a volume serial number per
                          http://www.faqs.org/faqs/assembly-language/x86/general/part3/section-3.html
                       */
                       GetSystemTime(&st);

                       serial_lo = st.wMonth * 0x100 + st.wDay +
                                   st.wSecond * 0x100 + st.wMilliseconds;;

                       serial_hi = st.wHour * 0x100 + st.wMinute +
                                   st.wYear;

                       *((WORD*)(&(boot_sect[0x27]))) = serial_lo;
                       *((WORD*)(&(boot_sect[0x29]))) = serial_hi;

                       printf("Volume Serial Number: %04X-%04X\n",serial_hi,serial_lo);

                       if( !  WriteFile
                              (
                                hFloppy,
                                boot_sect,
                                512,
                                &outBytes,
                                NULL
                              ) )
                       {
                         print_error(GetLastError());
                         with_errors = 1;
                         break;
                       }

                       printf("Writing file allocation tables and cleaning root directory...\n");

                       if( !  WriteFile
                              (
                                hFloppy,
                                buf,
                                BUF_SIZE,
                                &outBytes,
                                NULL
                              ) )
                       {
                         print_error(GetLastError());
                         with_errors = 1;
                         break;
                       }


                 } while (0);

                 printf("Closing floppy drive A:...\n");

                 CloseHandle(hFloppy);

                 printf("Done%s.\n", with_errors ? " with errors" : "");

               }
               else
               {
                 print_error(GetLastError());
               }

               printf("Press 'a' to format another diskette\n"
                      "WARNING: format will start immediately!\n"
                      "Press any other key to finish\n");

               {
                 char c = getch();
                 if ( c != 'a' && c != 'A' ) break;
               }
       }
       while (1);
  }

  free(buf);

  return 0;
}
