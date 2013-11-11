#include <time.h>
#include <stdio.h>
#include <string.h>

#include "sf/log.h"


#define SF_LOG_BUFSIZ 1024


#ifndef NDEBUG
  static sf_log_level_t log_level = SF_LOG_INFO;
#else
  static sf_log_level_t log_level = SF_LOG_WARN;
#endif /* NDEBUG */

static const char *log_labels[] = {
    "PANIC",
    "ERROR",
    "WARNING",
    "DEBUG",
    "INFO",
};

static sf_log_func *log_func = NULL;


sf_result_t sf_log_set_hook(sf_log_func *f) {
    log_func = f;
    return SF_OK;
}

sf_result_t sf_log_set_level(sf_log_level_t level) {
    if (level < 0 || level >= SF_LOG_NLEVELS) {
        return SF_INVAL;
    }

    log_level = level;

    return SF_OK;
}

sf_log_level_t sf_log_get_level(void) {
    return log_level;
}

sf_result_t sf_log(sf_log_level_t level, const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    if (sf_logv(level, fmt, ap) != SF_OK) {
        return SF_ERR;
    }
    va_end(ap);

    return SF_OK;
}

sf_result_t sf_logv(sf_log_level_t level, const char *fmt, va_list ap) {
    time_t      rawtime;
    struct tm  *timeinfo;
    char        buf[SF_LOG_BUFSIZ];
    char       *ptr;
    size_t      len;

    if (level > log_level) {
        return SF_OK;
    }

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    if (strftime(buf, SF_LOG_BUFSIZ, "%Y-%m-%d %H:%M:%S ", timeinfo) == 0) {
        return SF_ERR;
    }

    len = strlen(buf);
    ptr = buf + len;
    if (snprintf(ptr, SF_LOG_BUFSIZ - len, "%s ", log_labels[level]) < 0) {
        return SF_ERR;
    }

    len = strlen(buf);
    ptr = buf + len;
    if (vsnprintf(ptr, SF_LOG_BUFSIZ - len, fmt, ap) < 0) {
        return SF_ERR;
    }

    len = strlen(buf);
    if (buf[len] != '\n') {
        ptr = buf + len;
        snprintf(ptr, SF_LOG_BUFSIZ - len, "\n");
    }

    if (log_func) {
        if (log_func(level, buf) == SF_FALSE) {
            return SF_OK;
        }
    }

    fprintf(stderr, "%s", buf);

    return SF_OK;
}
