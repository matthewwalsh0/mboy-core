#ifndef LOG_H
#define LOG_H

#ifdef MBOY_DEBUG

#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"

#define MBOY_TRACE(...) spdlog::trace(__VA_ARGS__)
#define MBOY_INFO(...) spdlog::info(__VA_ARGS__)
#define MBOY_WARN(...) spdlog::warn(__VA_ARGS__)
#define MBOY_ERROR(...) spdlog::error(__VA_ARGS__)

inline static void initLogging() {
    spdlog::cfg::load_env_levels();
}

#else

#define MBOY_TRACE(...)
#define MBOY_INFO(...)
#define MBOY_WARN(...)
#define MBOY_ERROR(...)

inline static void initLogging() {}

#endif

#endif