/**
 * File: capture.h
 * Author: Joe Shang
 * Brief: The camera capture program with v4l2 framework
 * Capturing Process:
 *  1. camera_open_device(): Open camera
 *  2. camera_query_cap(): Query camera's capability.
 *  3. camera_query_stream(): Query camera's output format.
 *  4. camera_query_support_format(): Query camera's output format.
 *  5. camera_set_format(): Set the output format of camera.
 *  6. camera_req_buf_and_mmap(): Request camera data buffers in kernel space and mmap buffers to user space.
 *  7. camera_start_capture(): Device begin to capture camera.
 *  8. camera_is_read_ready(): Query whether the camera data is ready or not.
 *  9. camera_read_frame(): Read frame of camera and handle it in callback function(VideoCallBack).
 *  10.camera_stop_capture(): Camera stop to capture video.
 *  11.camera_deinit_device(): Deinitialize camera.
 *  12.camera_close_device(): Close camera.
 */

#ifndef _CAPTURE_H_
#define _CAPTURE_H_

typedef enum _CameraFormat
{
    PIX_FMT_YUYV,
    PIX_FMT_MJPEG
}CameraFormat;

struct _CameraDevice;
typedef struct _CameraDevice CameraDevice;

typedef void (*VideoCallBack)(void *ctx, void *buf_start, int buf_size);

CameraDevice *camera_create(void);
void camera_open_device(CameraDevice *thiz, char *dev_name);
void camera_query_cap(CameraDevice *thiz);
void camera_query_stream(CameraDevice *thiz);
void camera_query_support_format(CameraDevice *thiz);
void camera_set_format(CameraDevice *thiz,
        int width,
        int height,
        CameraFormat format);
void camera_req_buf_and_mmap(CameraDevice *thiz, int req_buf_cnt);
void camera_start_capture(CameraDevice *thiz);
void camera_read_frame(CameraDevice *thiz, 
        VideoCallBack video_data_callback,
        void *ctx );
int  camera_is_read_ready(CameraDevice *thiz);
void camera_stop_capture(CameraDevice *thiz);
void camera_deinit_device(CameraDevice *thiz);
void camera_close_device(CameraDevice *thiz);
void camera_destroy(CameraDevice *thiz);

#endif