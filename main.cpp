#include "logger.h"

int main()
{
    Logger logger("D://testA");

    logger.info("this is a %s %d\n", "info", 1);
    logger.info("this is a %s %d\n", "info", 2);
    logger.info("this is a %s %d\n", "info", 3);
    logger.info("this is a %s %d\n", "info", 4);

    logger.warn("this is a %s %d\n", "warn", 1);
    logger.warn("this is a %s %d\n", "warn", 2);
    logger.warn("this is a %s %d\n", "warn", 3);
    logger.warn("this is a %s %d\n", "warn", 4);

    logger.err("this is a %s %d\n", "err", 1);
    logger.err("this is a %s %d\n", "err", 2);
    logger.err("this is a %s %d\n", "err", 3);
    logger.err("this is a %s %d\n", "err", 4);

    logger.setLogPath("D://testB");

    logger.info("this is a %s %d\n", "info", 1);
    logger.info("this is a %s %d\n", "info", 2);
    logger.info("this is a %s %d\n", "info", 3);
    logger.info("this is a %s %d\n", "info", 4);

    logger.warn("this is a %s %d\n", "warn", 1);
    logger.warn("this is a %s %d\n", "warn", 2);
    logger.warn("this is a %s %d\n", "warn", 3);
    logger.warn("this is a %s %d\n", "warn", 4);

    logger.err("this is a %s %d\n", "err", 1);
    logger.err("this is a %s %d\n", "err", 2);
    logger.err("this is a %s %d\n", "err", 3);
    logger.err("this is a %s %d\n", "err", 4);

    return 0;
}
