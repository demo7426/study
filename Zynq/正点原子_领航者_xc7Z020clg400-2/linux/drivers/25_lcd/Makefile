APP_NAME := drm_test.c
APP_ELF := drm_test.elf

.PHONY:all clean

all:
	$(CC) ${APP_NAME} -o ${APP_ELF} -I/usr/include/drm -lpthread -ldrm

clean:
	${RM} -rf ${APP_ELF}
