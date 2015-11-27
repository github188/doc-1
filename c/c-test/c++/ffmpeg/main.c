/*
 * main.c -- 100 lines ffmepg
 *
 * Copyright (C) 2015 liyunteng
 * Auther: liyunteng <li_yunteng@163.com>
 * License: GPL
 * Update time:  2015/06/04 09:11:00
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include <stdio.h>

#ifdef __cplusplus
extern "C"{
#endif
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <SDL/SDL.h>
#ifdef __cplusplus
}
#endif

#define SHOW_FULLSCREEN 0
#define OUTPUT_YUV420P 1

int main(int argc, char *argv[])
{
    /* FFMPEG */
    AVFormatContext *pFormatCtx;
    int         i, videoindex;
    AVCodecContext  *pCodecCtx;
    AVCodec         *pCodec;
    AVFrame *pFrame, *pFrameYUV;
    AVPacket *packet;
    struct SwsContext *img_covert_ctx;

    /* SDL */
    int screen_w, screen_h;
    SDL_Surface *screen;
    SDL_VideoInfo *vi;
    SDL_Overlay *bmp;
    SDL_Rect rect;


    FILE *fp_yuv;
    int ret, got_picture;
    char filepath[] = "/home/lyt/1.mkv";

    av_register_all();
    avformat_network_init();


    pFormatCtx = avformat_alloc_context();

    if(avformat_open_input(&pFormatCtx, filepath, NULL, NULL) != 0) {
        printf("Couldn't open input stream.\n");
        return -1;
    }

    if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
        printf("Couldn't find stream information.\n");
        return -1;
    }

    videoindex = -1;
    for (i=0; i<pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)  {
            videoindex = i;
            break;
        }
    }

    if (videoindex == -1) {
        printf("Didn't find a video stream.\n");
        return -1;
    }

    pCodecCtx = pFormatCtx->streams[videoindex]->codec;
    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
    if (pCodec == NULL) {
        printf("Codec not found.\n");
        return -1;
    }

    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
        printf("Could not open codec.\n");
        return -1;
    }

    pFrame = av_frame_alloc();
    pFrameYUV = av_frame_alloc();
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
        printf("Could not initialize SDL - %s\n", SDL_GetError());
        return -1;
    }

    vi = SDL_GetVideoInfo();
#if SHOW_FULLSCREEN
    screen_w = vi->current_w;
    screen_h = vi->current_h;
    screen = SDL_SetVideoMode(screen_w, screen_h, 0, SDL_FULLSCREEN);
#else
    screen_w = pCodecCtx->width;
    screen_h = pCodecCtx->height;
    screen = SDL_SetVideoMode(screen_w, screen_h, 0, 0);
#endif

    if (!screen) {
        printf("SDL: could not set video mode - exiting: %s\n", SDL_GetError());
        return -1;
    }

    bmp = SDL_CreateYUVOverlay(pCodecCtx, pCodecCtx, SDL_YV12_OVERLAY, screen);

    rect.x = 0;
    rect.y = 0;
    rect.w = screen_w;
    rect.h = screen_h;
    /* SDL END */

    packet = (AVPacket *)av_malloc(sizeof(AVPacket));
    printf("----------File Information----------\n");
    av_dump_format(pFormatCtx, 0, filepath, 0);
    printf("------------------------------------\n");

#if OUTPUT_YUV420P
    fp_yuv = fopen("output.yuv", "wb+");
#endif

    SDL_WM_SetCaption("Simplest FFmpeg Player", NULL);

    img_covert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height,pCodecCtx->pix_fmt, pCodecCtx->width*3, pCodecCtx->height*3,pCodecCtx->pix_fmt, 0, NULL, NULL, NULL);

    while(av_read_frame(pFormatCtx, packet) >= 0) {
        if (packet->stream_index == videoindex) {
            ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
            if (ret  < 0 ){
                printf("Decode Error\n");
                return -1;
            }
            if (got_picture) {
                SDL_LockYUVOverlay(bmp);
                pFrameYUV->data[0] = bmp->pixels[0];
                pFrameYUV->data[1] = bmp->pixels[2];
                pFrameYUV->data[2] = bmp->pixels[1];
                pFrameYUV->linesize[0] = bmp->pitches[0];
                pFrameYUV->linesize[1] = bmp->pitches[2];
                pFrameYUV->linesize[2] = bmp->pitches[1];
                sws_scale(img_covert_ctx, (const uint8_t * const*)pFrame->data,
                          pFrame->linesize, 0, pCodecCtx->height, pFrameYUV->data,
                          pFrameYUV->linesize);

#if OUTPUT_YUV420P
                int y_size=pCodecCtx->width * pCodecCtx->height;
                fwrite(pFrameYUV->data[0], 1, y_size, fp_yuv); /* y */
                fwrite(pFrameYUV->data[1], 1, y_size/4, fp_yuv); /* U */
                fwrite(pFrameYUV->data[2], 1, y_size/4, fp_yuv); /* V
                                                                    */
#endif

                SDL_UnlockYUVOverlay(bmp);
                SDL_DisplayYUVOverlay(bmp, &rect);
                /* delay 40ms */
                SDL_Delay(40);
            }
        }
        av_free_packet(packet);
    }
    /* fix: flush frames remainded in codec */
    /*
 *     while(1) {
 *         ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
 *         if (ret < 0)
 *             break;
 *         if (!got_picture)
 *             break;
 *
 *         sws_scale(img_covert_ctx, (const uint8_t* const *)pFrame->data,
 *                   pFrame->linesize, 0, pCodecCtx->height, pFrameYUV->data,
 *                   pFrameYUV->linesize);
 *         SDL_LockYUVOverlay(bmp);
 *         pFrameYUV->data[0] = bmp->pixels[0];
 *         pFrameYUV->data[1] = bmp->pixels[2];
 *         pFrameYUV->data[2] = bmp->pixels[1];
 *         pFrameYUV->linesize[0] = bmp->pitches[0];
 *         pFrameYUV->linesize[1] = bmp->pitches[2];
 *         pFrameYUV->linesize[2] = bmp->pitches[1];
 * #if OUTPUT_YUV420P
 *         int y_size=pCodecCtx->width * pCodecCtx->height;
 *         fwrite(pFrameYUV->data[0], 1, y_size, fp_yuv); /\* y *\/
 *         fwrite(pFrameYUV->data[1], 1, y_size/4, fp_yuv); /\* U *\/
 *         fwrite(pFrameYUV->data[2], 1, y_size/4, fp_yuv); /\* V *\/
 * #endif
 *
 *         SDL_UnlockYUVOverlay(bmp);
 *         SDL_DisplayYUVOverlay(bmp, &rect);
 *         SDL_Delay(40);
 *
 *     }
 */
    sws_freeContext(img_covert_ctx);

#if OUTPUT_YUV420P
    fclose(fp_yuv);
#endif

    SDL_Quit();

    av_free(pFrameYUV);
    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);

    return 0;
}
