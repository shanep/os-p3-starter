/*Do NOT modify this file! */
#ifndef LAB_H
#define LAB_H
#include <stdlib.h>
#include <stdbool.h>
#include <lab_export.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Entry point for the main function
     *
     * @param argc The argument count
     * @param argv The argument array
     * @return The exit code
     */
    LAB_EXPORT int go(int argc, char **argv);


#ifdef __cplusplus
} //extern "C"
#endif

#endif
