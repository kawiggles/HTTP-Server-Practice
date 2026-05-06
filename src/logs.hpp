#pragma once

#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cstdarg>

#define DEBUG

#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
    if(!(n)) { \
        printf("%s - Failed\n", #n); \
        printf("At %s ", __TIME__); \
        printf("in file %s ", __FILE__); \
        printf("at line %d\n", __LINE__); \
        exit(1); } 
#endif

inline FILE * LOG_FILE = nullptr;

inline void initLogger() {
    LOG_FILE = fopen("log.txt", "w");
    if (!LOG_FILE) {
        perror("Failed to open log file");
        return;
    }
    time_t Time = time(nullptr);
    fprintf(LOG_FILE, "=== Session Log Starting At: %.24s ===\n", ctime(&Time));
    fflush(LOG_FILE);
}

inline void closeLogger() {
    if (LOG_FILE) {
        fprintf(LOG_FILE, "=== End Session Log ===");
        fclose(LOG_FILE);
        LOG_FILE = nullptr;
    }
}

inline void logMsg(const char * fmt, ...) {
    if (!LOG_FILE) return;
    va_list args;
    va_start(args, fmt);
    vfprintf(LOG_FILE, fmt, args);
    va_end(args);
    fprintf(LOG_FILE, "\n");
    fflush(LOG_FILE);
}
