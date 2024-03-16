#pragma once

#define DEBUG(format, ...) printf(format, ##__VA_ARGS__)
#define INFO(format, ...) printf(format, ##__VA_ARGS__)
#define WARN(format, ...) printf(format, ##__VA_ARGS__)
#define FATAL(format, ...) printf(format, ##__VA_ARGS__)
