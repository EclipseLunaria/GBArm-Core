#ifndef ERROR_H
#define ERROR_H

#ifndef ERROR_TRACE
    #define PRINT_ERROR(msg,...) 
#endif
#ifdef ERROR_TRACE
    #define PRINT_ERROR(msg, ...) printf(msg, ##__VA_ARGS__);

#endif

#define CHECK_ERROR(func, msg, ...)                                                                                  \
    int ERROR_VALUE = func;                                                                                          \
    if (ERROR_VALUE < 0) {                                                                                          \ 
        PRINT_ERROR("ERROR: trace level: %d\n\tFile: %s:%d\n\tfunction: %s\n\t", ERROR_VALUE, __FILE__, __LINE__, #func) \
        PRINT_ERROR(msg, ##__VA_ARGS__);                                                                                  \
        PRINT_ERROR("\n");                                                                                                \
        return ERROR_VALUE - 1;                                                                                      \
    }                                                                                                              

#define THROW_ERROR(msg, ...)                        \
    PRINT_ERROR("\nTraceback (most recent call last)\n"); \
    CHECK_ERROR(-1, msg, ##__VA_ARGS__)              \
    return 0;

#define CONCAT(a, b) a##b
#define CONCAT2(a, b) CONCAT(a, b)
#define ERROR_VALUE CONCAT(error_value_, __LINE__)

#endif
