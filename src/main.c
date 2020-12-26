#include <stdint.h>

// Platform bit size.
#if INTPTR_MAX == INT64_MAX
    #define BIT_64
#elif INTPTR_MAX == INT32_MAX
    #define BIT_32
#else
    #error Unsupported platform or missing size macros.
#endif

#if defined(_WIN32)
    #define _CRT_SECURE_NO_WARNINGS // Disable annoying 'unsafe' warnings (we know what we're doing and we're not handling sensitive data).
#elif defined(__unix__)
    #if defined(BIT_64)
        #define _FILE_OFFSET_BITS 64 // Make off_t be 64-bit.

        #include <sys/types.h>
    #endif
#endif

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// The file size type, either 32-bit or 64-bit (__int64, off_t, or int64_t).
#if defined(BIT_32)
    #define SIZE_TYPE long int
#else
    #if defined(_WIN32)
        #define SIZE_TYPE __int64
    #elif defined(__UNIX__)
        #define SIZE_TYPE off_t
    #else
        #define SIZE_TYPE int64_t
    #endif
#endif

#define BUFFER_SIZE            4096 // The buffer used to overwrite the file.
#define FORMATTING_BUFFER_SIZE 32   // The buffer used for formatting the size.

// Various IO errors.
#define MSG_ERROR_OPEN      "cannot open file (doesn't exist or too large -- try using zero64)"
#define MSG_ERROR_SEEK      "cannot seek in file"
#define MSG_ERROR_SEEK_BACK "cannot seek back in file"
#define MSG_ERROR_SIZE      "cannot get file size"
#define MSG_ERROR_SIZE32    "cannot get file size (may be too large -- try using zero64)"
#define MSG_ERROR_CONFIRM   "cannot read confirmation"

// Shows an IO error.
void io_error(const char* msg) {
    fprintf(stderr, "IO error: %s\n", msg);
}

// Adds the thousands separator for the file size.
void format_size(SIZE_TYPE size, char* dest);

int main(int argc, char** argv) {
    FILE* file;
    int confirm;
    int argIndex;

    bool force = false;

    char buffer[BUFFER_SIZE];               // For the zeros.
    char fmtBuffer[FORMATTING_BUFFER_SIZE]; // For the formatted file size.

    SIZE_TYPE size;
    SIZE_TYPE passes;

    if(argc < 2) {
        fprintf(stderr, "Usage: %s [-f, --force] <FILE>\n", argv[0]);
        return 1;
    }

    // Leave room for future arguments.
    for(argIndex = 1; argIndex < argc; ++argIndex) {
        if(strcmp(argv[argIndex], "-f") == 0 || strcmp(argv[argIndex], "--force") == 0)
            force = true;
        else break;
    }

    file = fopen(argv[argIndex], "rb+");

    if(!file) {
        io_error(MSG_ERROR_OPEN);
        return 1;
    }

    // 32-bit: standard way.
    #if defined(BIT_32)
        if(0 != fseek(file, 0, SEEK_END)) {
            io_error(MSG_ERROR_SEEK);
            goto _error;
        }

        if(-1 == (size = ftell(file))) {
            io_error(MSG_ERROR_SIZE32);
            goto _error;
        }

        if(0 != fseek(file, 0, SEEK_SET)) {
            io_error(MSG_ERROR_SEEK_BACK);
            goto _error;
        }
    #else // 64-bit: platform-specific way.
        #if defined(_WIN32)
            if(0 != _fseeki64(file, 0, SEEK_END)) {
                io_error(MSG_ERROR_SEEK);
                goto _error;
            }

            if(-1 == (size = _ftelli64(file))) {
                io_error(MSG_ERROR_SIZE);
                goto _error;
            }

            if(0 != _fseeki64(file, 0, SEEK_SET)) {
                io_error(MSG_ERROR_SEEK_BACK);
                goto _error;
            }
        #elif defined(__unix__)
            if(0 != fseeko(file, 0, SEEK_END)) {
                io_error(MSG_ERROR_SEEK);
                goto _error;
            }

            if(-1 == (size = ftello(file))) {
                io_error(MSG_ERROR_SIZE);
                goto _error;
            }

            if(0 != fseeko(file, 0, SEEK_SET)) {
                io_error(MSG_ERROR_SEEK_BACK);
                goto _error;
            }
        #endif
    #endif

    if(!force) {
        format_size(size, fmtBuffer);

        printf("File size is %s bytes\n", fmtBuffer);

        printf("Are you sure? (Y/N) ");

        if(EOF == (confirm = getchar())) {
            io_error(MSG_ERROR_CONFIRM);
            return 1;
        }

        if(confirm != 'y' && confirm != 'Y') {
            fclose(file);
            goto _end;
        }

        printf("Confirmed -- overwriting with zeros...");
        fflush(stdout);
    }

    memset(buffer, 0, BUFFER_SIZE);

    passes = size / BUFFER_SIZE;

    // Write zeros.
    while(passes > 0) {
        if(BUFFER_SIZE != fwrite(buffer, sizeof(char), BUFFER_SIZE, file)) {
            fprintf(stderr, "IO error\n");
            return 1;
        }

        --passes;
    }

    // If the size is not a multiple of the buffer size, write the final incomplete block.
    if(size % BUFFER_SIZE > 0) {
        if(size % BUFFER_SIZE != fwrite(buffer, sizeof(char), size % BUFFER_SIZE, file)) {
            fprintf(stderr, "IO error\n");
            return 1;
        }
    }

    fclose(file);

    if(0 != remove(argv[argIndex])) {
        fprintf(stderr, "Cannot delete file\n");
        return 1;
    }

    if(!force) {
        printf("done\n");
    }

_end:
    return 0;

_error:
    fclose(file);
    return 1;
}

void format_size(SIZE_TYPE size, char* dest) {
    char destIndex = 0;
    char counter = 0;

    char* start;
    char* end;

    // Format the size (the buffer will end up reversed).
    do {
        if(counter == 3) {
            dest[destIndex++] = ',';
            counter = 0;
        }

        dest[destIndex++] = size % 10 + '0';
        ++counter;

        size /= 10;
    } while(size > 0);

    dest[destIndex] = '\0';

    // Reverse the buffer so that it looks normal.
    start = dest;
    end = dest + destIndex - 1;

    while(start < end) {
        char tmp = *start;
        *start = *end;
        *end = tmp;

        ++start;
        --end;
    }
}