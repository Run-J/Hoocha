#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

#define LOG_DX_PATH "/tmp/dataCorruptor.log"
#define LOG_DR_PATH "/tmp/dataMonitor.log"
#define LOG_DC_PATH "/tmp/dataCreator.log"

void logEvent(const char *message);
void LogDXEvent(const char *format, ...);
void LogDREvent(int dcIndex, pid_t dcPID, int statusCode, const char *statusText);
void LogDCEvent(pid_t dcPID, int statusCode, const char *statusText);
