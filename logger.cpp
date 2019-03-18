#include "logger.h"

Logger::Logger(const char *logPath)
{
    setLogPath(logPath);
}

Logger::~Logger()
{
    closeAllOS();
}

void Logger::info(const char *format, ...)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    std::string dateStr, timeStr;
    curDateTimeStr(dateStr, timeStr);
    checkDateAndInitOS(dateStr, INFO_LOG_NAME_PREFIFX, m_osInfo);

    char logBuff[MAX_LOG_BUFF_SZIE];
    va_list args;
    va_start(args, format);
    vsprintf(logBuff, format, args);
    va_end(args);
    logImp(timeStr.c_str(), logBuff, m_osInfo);
}

void Logger::warn(const char *format, ...)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    std::string dateStr, timeStr;
    curDateTimeStr(dateStr, timeStr);
    checkDateAndInitOS(dateStr, WARN_LOG_NAME_PREFIFX, m_osWarn);

    char logBuff[MAX_LOG_BUFF_SZIE];
    va_list args;
    va_start(args, format);
    vsprintf(logBuff, format, args);
    va_end(args);
    logImp(timeStr.c_str(), logBuff, m_osWarn);
}

void Logger::err(const char *format, ...)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    std::string dateStr, timeStr;
    curDateTimeStr(dateStr, timeStr);
    checkDateAndInitOS(dateStr, ERR_LOG_NAME_PREFIFX, m_osErr);

    char logBuff[MAX_LOG_BUFF_SZIE];
    va_list args;
    va_start(args, format);
    vsprintf(logBuff, format, args);
    va_end(args);
    logImp(timeStr.c_str(), logBuff, m_osErr);
}

void Logger::logImp(const char *prifix, const char *logBuff, std::ofstream &os)
{
    os << prifix << " " << logBuff;
    os.flush();
}

void Logger::checkDateAndInitOS(const std::string &curDate, const char *logName, std::ofstream &os)
{
    static std::string lastDate;
    static std::string lastLogPath;
    if(lastDate == curDate && lastLogPath == m_logPath)
    {
        if(os.is_open())
            return;
    }
    else
    {
        lastDate = curDate;
        lastLogPath = m_logPath;
        os.close();
    }

    //日志绝对路径
    std::string logPath = m_logPath + "/" + logName + "_" + curDate + ".log";
    os.open(logPath, std::ios::app);
}

void Logger::closeAllOS()
{
    if(m_osInfo.is_open())
        m_osInfo.close();

    if(m_osWarn.is_open())
        m_osWarn.close();

    if(m_osErr.is_open())
        m_osErr.close();
}

void Logger::curDateTimeStr(std::string &dateStr, std::string &timeStr)
{
    struct timeb tb;
    ftime(&tb);
    tm *t = localtime(&tb.time);

    char tmp[20];
    sprintf(tmp, "%04d%02d%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
    dateStr = tmp;

    sprintf(tmp, "%02d:%02d:%02d.%03d", t->tm_hour, t->tm_min, t->tm_sec, tb.millitm);
    timeStr = tmp;
}

void Logger::setLogPath(const char *logPath)
{
    m_logPath = logPath;
    closeAllOS();
}
