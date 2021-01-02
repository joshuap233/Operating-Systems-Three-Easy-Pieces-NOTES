#include "myaio.h"
#include "common.h"
#include <aio.h>
#include <string.h>
#include <unistd.h>

void init_aio_buf(aio_buf_t buf[], int buf_size) {
    for (int i = 0; i < buf_size; i++) {
        buf[i].op = UNUSED;
        buf[i].off = 0;
        buf[i].finish = 0;
        buf[i].aiocb.aio_sigevent.sigev_notify = SIGEV_NONE;
        buf[i].aiocb.aio_buf = buf[i].data;
    }
}

void my_aio_read(aio_buf_t buf[], int sock_fd) {
    // buf[index].data 不会被重用,所有需要创建足够大的 buf
    int off = 0; //已读取字节数
    int data_size = 0; // 总共需要读取的数据长度(包括开头四字节)
    aio_n an = 0;
    int err;


    while (1) {
        for (int i = 0; i < N_AIO; i++) {
            switch (buf[i].op) {
                case UNUSED:
                    // data_size 即还未开始或完成对 header 的读取
                    if (data_size == 0 || off < data_size) {
                        buf[i].op = READ_PENDING;
                        buf[i].aiocb.aio_fildes = sock_fd;

                        // 当前 buf 第一次读取
                        if (buf[i].finish == 0) {
                            buf[i].finish = 0;
                            buf[i].aiocb.aio_offset = off;
                            buf[i].aiocb.aio_nbytes = MAX_MSG;
                            off += MAX_MSG;
                        } else {
                            // 上次 没有读取完 MAX_MSG 字节,继续读取
                            buf[i].aiocb.aio_nbytes = buf[i].off + buf[i].finish;
                        }

                        if (aio_read(&buf[i].aiocb) < 0)
                            err_exit("aio_read");
                        an++;
                    }
                    break;
                case READ_PENDING:
                    // 正在读取
                    if ((err = aio_error(&buf[i].aiocb)) == EINPROGRESS)
                        continue;

                    // 读取错误
                    if (err != 0) {
                        if (err == -1)
                            err_exit("aio_error failed");
                        else
                            err_exit("read failed")
                    }

                    int n;
                    // 读取完成
                    // 获取读取完成结果出错或读取字节数为 0
                    if ((n = aio_return(&buf[i].aiocb)) <= 0)
                        err_exit("aio_return failed");

                    buf[i].finish += n;

                    if (i == 0) {
                        memcpy(&data_size, buf[i].data, HEADER_LEN);
                    }

                    an--;
                    buf[i].op = UNUSED;
                    break;
            }
        }

        // 所有 aio 已经读取完成
        if (an == 0) {

        }
    }
}

int main() {
    aio_buf_t buf[10];
    init_aio_buf(buf, 10);
}