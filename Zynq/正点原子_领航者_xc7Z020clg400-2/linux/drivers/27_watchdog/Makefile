APP_NAME := watchdog_app.cpp
APP_ELF := watchdog_app.elf

.PHONY:all clean

all:
	$(CXX) ${APP_NAME} -o ${APP_ELF} -lpthread

clean:
	${RM} -rf ${APP_ELF}

