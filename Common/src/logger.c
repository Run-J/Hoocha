#include "../inc/logger.h"


// Get the current timestamp [YYYY-MM-DD HH:MM:SS].
void getCurrentTimestamp(char *buffer, int bufferSize)
{
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, bufferSize, "%Y-%m-%d %H:%M:%S", t);
}


// Generic logging functions
void LogEvent(const char *logFilePath, const char *format, ...)
{
    FILE *logFile = fopen(logFilePath, "a");
    if (logFile)
    {
        char timestamp[20];
        getCurrentTimestamp(timestamp, sizeof(timestamp));

        va_list args;
        va_start(args, format);
        fprintf(logFile, "[%s] : ", timestamp);
        vfprintf(logFile, format, args);
        fprintf(logFile, "\n");
        va_end(args);

        fclose(logFile);
    }
    else
    {
        perror("Error opening log file");
    }
}


// logger functions for DX program
void LogDXEvent(const char *format, ...)
{
    FILE *logFile = fopen(LOG_DX_PATH, "a");
    if (logFile)
    {
        char timestamp[20];
        getCurrentTimestamp(timestamp, sizeof(timestamp));

        va_list args;
        va_start(args, format);
        fprintf(logFile, "[%s] : ", timestamp);
        vfprintf(logFile, format, args);
        fprintf(logFile, "\n");
        va_end(args);

        fclose(logFile);
    }
    else
    {
        perror("Error opening DX log file");
    }
}


// logger functions for DR program
void LogDREvent(int dcIndex, pid_t dcPID, int statusCode, const char *statusText)
{
    LogEvent(LOG_DR_PATH, "DC-%02d [%d] updated in the master list – MSG RECEIVED – Status %d (%s)",
             dcIndex, dcPID, statusCode, statusText);
}


// logger functions for DC program
void LogDCEvent(pid_t dcPID, int statusCode, const char *statusText)
{
    LogEvent(LOG_DC_PATH, "DC [%d] – MSG SENT – Status %d (%s)",
             dcPID, statusCode, statusText);
}

