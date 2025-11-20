/***************************************************************
文件名    : drm_test.c
作者      : David Rheinsberg
版本      : V1.0
描述      : LCD应用层测试程序
其他      : 无
论坛      : www.openedv.com
日志      : 初版V1.0 2021/12/8 创建
***************************************************************/

#define _GNU_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>
#include <xf86drm.h>
#include <xf86drmMode.h>

int fd = -1;
struct modeset_dev;
static int modeset_find_crtc(int fd, drmModeRes *res, drmModeConnector *conn,
			     struct modeset_dev *dev);
static int modeset_create_fb(int fd, struct modeset_dev *dev);
static int modeset_setup_dev(int fd, drmModeRes *res, drmModeConnector *conn,
			     struct modeset_dev *dev);
static int modeset_open(int *out, const char *node);
static int modeset_prepare(int fd);
static void modeset_draw(void);
static void modeset_cleanup(int fd);

static void sig_handler(int sig)
{
    modeset_cleanup(fd);    
	close(fd);
    exit(0);
}

//drm驱动加载成功后，会创建一个名为/dev/dri/cardX的设备, X的范围为0~64.
//调用libdrm提供的open API函数打开设备后，可以对设备进行操作.
static int modeset_open(int *out, const char *node)
{
	int fd, ret;
	uint64_t has_dumb;

	fd = open(node, O_RDWR | O_CLOEXEC);
	if (fd < 0) {
		ret = -errno;
		fprintf(stderr, "cannot open '%s': %m\n", node);
		return ret;
	}

	if (drmGetCap(fd, DRM_CAP_DUMB_BUFFER, &has_dumb) < 0 ||
	    !has_dumb) {
		fprintf(stderr, "drm device '%s' does not support dumb buffers\n",
			node);
		close(fd);
		return -EOPNOTSUPP;
	}

	*out = fd;
	return 0;
}
//定义一个变量，用来存放显示设置的相关信息
struct modeset_dev {
	struct modeset_dev *next;	//指向下一个modeset_dev

	uint32_t width;				//buffer的宽度
	uint32_t height;			//buffer的高度
	uint32_t stride;			//buffer的步长，行分辨率*一个像素字节数
	uint32_t size;				//buffer的总字节数大小
	uint32_t handle;			//buffer的DRM句柄
	uint8_t *map;				//指向buffer内存映射后的地址

	drmModeModeInfo mode;		//存放程序中要设置的显示模式
	uint32_t fb;				//帧缓冲区句柄
	uint32_t conn;				//和buffer匹配的connector ID
	uint32_t crtc;				//和connector匹配的crtc ID
	drmModeCrtc *saved_crtc;	//crtc未修改之前的配置信息
};

static struct modeset_dev *modeset_list = NULL;

static int modeset_prepare(int fd)
{
	drmModeRes *res;
	drmModeConnector *conn;
	unsigned int i;
	struct modeset_dev *dev;
	int ret;

	/* retrieve resources */
	res = drmModeGetResources(fd);
	if (!res) {
		fprintf(stderr, "cannot retrieve DRM resources (%d): %m\n",
			errno);
		return -errno;
	}

	/* iterate all connectors */
	for (i = 0; i < res->count_connectors; ++i) {
		/* get information for each connector */
		conn = drmModeGetConnector(fd, res->connectors[i]);
		if (!conn) {
			fprintf(stderr, "cannot retrieve DRM connector %u:%u (%d): %m\n",
				i, res->connectors[i], errno);
			continue;
		}

		/* create a device structure */
		dev = malloc(sizeof(*dev));
		memset(dev, 0, sizeof(*dev));
		dev->conn = conn->connector_id;

		/* call helper function to prepare this connector */
		ret = modeset_setup_dev(fd, res, conn, dev);
		if (ret) {
			if (ret != -ENOENT) {
				errno = -ret;
				fprintf(stderr, "cannot setup device for connector %u:%u (%d): %m\n",
					i, res->connectors[i], errno);
			}
			free(dev);
			drmModeFreeConnector(conn);
			continue;
		}

		/* free connector data and link device into global list */
		drmModeFreeConnector(conn);
		dev->next = modeset_list;
		modeset_list = dev;
	}

	/* free resources again */
	drmModeFreeResources(res);
	return 0;
}

static int modeset_setup_dev(int fd, drmModeRes *res, drmModeConnector *conn,
			     struct modeset_dev *dev)
{
	int ret;

	/* check if a monitor is connected */
	if (conn->connection != DRM_MODE_CONNECTED) {
		fprintf(stderr, "ignoring unused connector %u\n",
			conn->connector_id);
		return -ENOENT;
	}

	/* check if there is at least one valid mode */
	if (conn->count_modes == 0) {
		fprintf(stderr, "no valid mode for connector %u\n",
			conn->connector_id);
		return -EFAULT;
	}

	/* copy the mode information into our device structure */
	memcpy(&dev->mode, &conn->modes[0], sizeof(dev->mode));
	dev->width = conn->modes[0].hdisplay;
	dev->height = conn->modes[0].vdisplay;
	fprintf(stderr, "mode for connector %u is %ux%u\n",
		conn->connector_id, dev->width, dev->height);

	/* find a crtc for this connector */
	ret = modeset_find_crtc(fd, res, conn, dev);
	if (ret) {
		fprintf(stderr, "no valid crtc for connector %u\n",
			conn->connector_id);
		return ret;
	}

	/* create a framebuffer for this CRTC */
	ret = modeset_create_fb(fd, dev);
	if (ret) {
		fprintf(stderr, "cannot create framebuffer for connector %u\n",
			conn->connector_id);
		return ret;
	}

	return 0;
}

static int modeset_find_crtc(int fd, drmModeRes *res, drmModeConnector *conn,
			     struct modeset_dev *dev)
{
	drmModeEncoder *enc;
	unsigned int i, j;
	int32_t crtc;
	struct modeset_dev *iter;

	/* first try the currently conected encoder+crtc */
	if (conn->encoder_id)
		enc = drmModeGetEncoder(fd, conn->encoder_id);
	else
		enc = NULL;

	if (enc) {
		if (enc->crtc_id) {
			crtc = enc->crtc_id;
			for (iter = modeset_list; iter; iter = iter->next) {
				if (iter->crtc == crtc) {
					crtc = -1;
					break;
				}
			}

			if (crtc >= 0) {
				drmModeFreeEncoder(enc);
				dev->crtc = crtc;
				return 0;
			}
		}

		drmModeFreeEncoder(enc);
	}

	/* If the connector is not currently bound to an encoder or if the
	 * encoder+crtc is already used by another connector (actually unlikely
	 * but lets be safe), iterate all other available encoders to find a
	 * matching CRTC. */
	for (i = 0; i < conn->count_encoders; ++i) {
		enc = drmModeGetEncoder(fd, conn->encoders[i]);
		if (!enc) {
			fprintf(stderr, "cannot retrieve encoder %u:%u (%d): %m\n",
				i, conn->encoders[i], errno);
			continue;
		}

		/* iterate all global CRTCs */
		for (j = 0; j < res->count_crtcs; ++j) {
			/* check whether this CRTC works with the encoder */
			if (!(enc->possible_crtcs & (1 << j)))
				continue;

			/* check that no other device already uses this CRTC */
			crtc = res->crtcs[j];
			for (iter = modeset_list; iter; iter = iter->next) {
				if (iter->crtc == crtc) {
					crtc = -1;
					break;
				}
			}

			/* we have found a CRTC, so save it and return */
			if (crtc >= 0) {
				drmModeFreeEncoder(enc);
				dev->crtc = crtc;
				return 0;
			}
		}

		drmModeFreeEncoder(enc);
	}

	fprintf(stderr, "cannot find suitable CRTC for connector %u\n",
		conn->connector_id);
	return -ENOENT;
}

static int modeset_create_fb(int fd, struct modeset_dev *dev)
{
	struct drm_mode_create_dumb creq;
	struct drm_mode_destroy_dumb dreq;
	struct drm_mode_map_dumb mreq;
	int ret;

	/* create dumb buffer */
	memset(&creq, 0, sizeof(creq));
	creq.width = dev->width;
	creq.height = dev->height;
	creq.bpp = 24;
	ret = drmIoctl(fd, DRM_IOCTL_MODE_CREATE_DUMB, &creq);
	if (ret < 0) {
		fprintf(stderr, "cannot create dumb buffer (%d): %m\n",
			errno);
		return -errno;
	}
	dev->stride = creq.pitch;
	dev->size = creq.size;
	dev->handle = creq.handle;

	/* create framebuffer object for the dumb-buffer */
	ret = drmModeAddFB(fd, dev->width, dev->height, 24, 24, dev->stride,
			   dev->handle, &dev->fb);
	if (ret) {
		fprintf(stderr, "cannot create framebuffer (%d): %m\n",
			errno);
		ret = -errno;
		goto err_destroy;
	}

	/* prepare buffer for memory mapping */
	memset(&mreq, 0, sizeof(mreq));
	mreq.handle = dev->handle;
	ret = drmIoctl(fd, DRM_IOCTL_MODE_MAP_DUMB, &mreq);
	if (ret) {
		fprintf(stderr, "cannot map dumb buffer (%d): %m\n",
			errno);
		ret = -errno;
		goto err_fb;
	}

	/* perform actual memory mapping */
	dev->map = mmap(0, dev->size, PROT_READ | PROT_WRITE, MAP_SHARED,
		        fd, mreq.offset);
	if (dev->map == MAP_FAILED) {
		fprintf(stderr, "cannot mmap dumb buffer (%d): %m\n",
			errno);
		ret = -errno;
		goto err_fb;
	}

	/* clear the framebuffer to 0 */
	memset(dev->map, 0, dev->size);

	return 0;

err_fb:
	drmModeRmFB(fd, dev->fb);
err_destroy:
	memset(&dreq, 0, sizeof(dreq));
	dreq.handle = dev->handle;
	drmIoctl(fd, DRM_IOCTL_MODE_DESTROY_DUMB, &dreq);
	return ret;
}

int main(int argc, char **argv)
{
	int ret;
	const char *card;
	struct modeset_dev *iter;
    sig_t sig_ret =NULL;

	//LCD屏默认使用/dev/dri/card0设备
	if (2 != argc) {
		printf("Usage: drm_test lcd|hdmi\n");
        card = "/dev/dri/card0";
	}
	else if (!strcmp(argv[1], "hdmi")) card = "/dev/dri/card1";
    else card = "/dev/dri/card0";
	
	fprintf(stderr, "using card '%s'\n", card);

    sig_ret = signal(SIGINT, (sig_t)sig_handler);
    if(SIG_ERR == sig_ret){
        perror("signal error");
        exit(-1);
    }

	//打开drm设备
	ret = modeset_open(&fd, card);
	if (ret)
		goto out_return;

	/* prepare all connectors and CRTCs */
	ret = modeset_prepare(fd);
	if (ret)
		goto out_close;

	/* perform actual modesetting on each found connector+CRTC */
	for (iter = modeset_list; iter; iter = iter->next) {
		iter->saved_crtc = drmModeGetCrtc(fd, iter->crtc);
		ret = drmModeSetCrtc(fd, iter->crtc, iter->fb, 0, 0,
				     &iter->conn, 1, &iter->mode);
		if (ret)
			fprintf(stderr, "cannot set CRTC for connector %u (%d): %m\n",
				iter->conn, errno);
	}

	/* draw some colors for 5seconds */
	modeset_draw();

	/* cleanup everything */
	modeset_cleanup(fd);

	ret = 0;

out_close:
	close(fd);
out_return:
	if (ret) {
		errno = -ret;
		fprintf(stderr, "modeset failed with error %d: %m\n", errno);
	} else {
		fprintf(stderr, "exiting\n");
	}
	return ret;
}

static void display_demo_1 (unsigned char *frame, unsigned int width, unsigned int height, unsigned int stride)
{
	unsigned int xcoi, ycoi;
	unsigned char wRed, wBlue, wGreen;
	unsigned int iPixelAddr = 0;

	for(ycoi = 0; ycoi < height; ycoi++) {

		for(xcoi = 0; xcoi < (width * 3); xcoi += 3) {

			if (((xcoi / 3) & 0x20) ^ (ycoi & 0x20)) {
				wRed = 255;
				wGreen = 255;
				wBlue = 255;
			} else {
				wRed = 0;
				wGreen = 0;
				wBlue = 0;
			}

			frame[xcoi + iPixelAddr + 0] = wBlue;
			frame[xcoi + iPixelAddr + 1] = wGreen;
			frame[xcoi + iPixelAddr + 2] = wRed;
		}

		iPixelAddr += stride;
	}
}

static void display_demo_2 (unsigned char *frame, unsigned int width, unsigned int height, unsigned int stride)
{
	unsigned int xcoi, ycoi;
	unsigned int iPixelAddr = 0;
	unsigned char wRed, wBlue, wGreen;
	unsigned int xInt;

	xInt = width * 3 / 8;
	for(ycoi = 0; ycoi < height; ycoi++) {

		for(xcoi = 0; xcoi < (width*3); xcoi+=3) {

			if (xcoi < xInt) {                                   //RED color
				wRed = 255;
				wGreen = 0;
				wBlue = 0;
			}
			else if ((xcoi >= xInt) && (xcoi < xInt*2)) {         //GREEN color
				wRed = 0;
				wGreen = 255;
				wBlue = 0;
			}
			else if ((xcoi >= xInt * 2) && (xcoi < xInt * 3)) {        //BLUE color
				wRed = 0;
				wGreen = 0;
				wBlue = 255;
			}
			else if ((xcoi >= xInt * 3) && (xcoi < xInt * 4)) {        //YELLOW color
				wRed = 255;
				wGreen = 255;
				wBlue = 0;
			}
			else if ((xcoi >= xInt * 4) && (xcoi < xInt * 5)) {        //MAGENTA color
				wRed = 255;
				wGreen = 0;
				wBlue = 255;
			}
			else if ((xcoi >= xInt * 5) && (xcoi < xInt * 6)) {        //CYAN color
				wRed = 0;
				wGreen = 255;
				wBlue = 255;
			}
			else if ((xcoi >= xInt * 6) && (xcoi < xInt * 7)) {        //White  color
				wRed = 255;
				wGreen = 255;
				wBlue = 255;
			}
			else {                                                //BLACK color
				wRed = 0;
				wGreen = 0;
				wBlue = 0;
			}

			frame[xcoi+iPixelAddr + 0] = wRed;
			frame[xcoi+iPixelAddr + 1] = wGreen;
			frame[xcoi+iPixelAddr + 2] = wBlue;
		}

		iPixelAddr += stride;
	}
}

static void display_demo_3 (unsigned char *frame, unsigned int width, unsigned int height, unsigned int stride)
{
	unsigned int xcoi, ycoi;
	unsigned int iPixelAddr = 0;

	for(ycoi = 0; ycoi < height; ycoi++) {

		for(xcoi = 0; xcoi < (width * 3); xcoi+=3) {

			frame[xcoi + iPixelAddr + 0] = xcoi/3;
			frame[xcoi + iPixelAddr + 1] = xcoi/3;
			frame[xcoi + iPixelAddr + 2] = xcoi/3;
		}

		iPixelAddr += stride;
	}
}


//在帧缓冲区中绘制3中纯色显示画面，每3秒切换不同画面
static void modeset_draw(void)
{
	struct modeset_dev *iter;

	iter = modeset_list;
	/* 循环显示不同颜色 */
	display_demo_2(iter->map, iter->width, iter->height, iter->stride);
	while(1){
		display_demo_1(iter->map, iter->width, iter->height, iter->stride);//方块
		sleep(3);

		display_demo_2(iter->map, iter->width, iter->height, iter->stride);//彩条
		sleep(3);

		display_demo_3(iter->map, iter->width, iter->height, iter->stride);//渐变色
		sleep(3);
	}
}

//清除modeset_prepare函数创建的设备，复位CRTC并释放内存
static void modeset_cleanup(int fd)
{
	struct modeset_dev *iter;
	struct drm_mode_destroy_dumb dreq;

	while (modeset_list) {
		/* remove from global list */
		iter = modeset_list;
		modeset_list = iter->next;

		/* restore saved CRTC configuration */
		drmModeSetCrtc(fd,
			       iter->saved_crtc->crtc_id,
			       iter->saved_crtc->buffer_id,
			       iter->saved_crtc->x,
			       iter->saved_crtc->y,
			       &iter->conn,
			       1,
			       &iter->saved_crtc->mode);
		drmModeFreeCrtc(iter->saved_crtc);

		/* unmap buffer */
		munmap(iter->map, iter->size);

		/* delete framebuffer */
		drmModeRmFB(fd, iter->fb);

		/* delete dumb buffer */
		memset(&dreq, 0, sizeof(dreq));
		dreq.handle = iter->handle;
		drmIoctl(fd, DRM_IOCTL_MODE_DESTROY_DUMB, &dreq);

		/* free allocated memory */
		free(iter);
	}
}
