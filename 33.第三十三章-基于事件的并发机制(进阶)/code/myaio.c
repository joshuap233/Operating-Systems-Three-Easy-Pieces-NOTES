#include "myaio.h"
#include <aio.h>

#define BUF_SIZE 4096
#define N_AIO 10

// 如何判断 socket 是否读到末尾呢?
// 这里规定前发送端发送的四字节必须为接下来需要发送的数据长度

// aiocb 状态
enum aio_op {
    UNUSED = 0,
    READ_PENDING = 1,
    WAITE_PENDING = 2
};

// 记录 aiocb 状态
typedef struct aio_buf {
    enum aio_op op;
    int last; // 是否读取到末尾
    struct aiocb aiocb;
    unsigned char data[MAX_MSG];
} aio_buf_t;

typedef int aio_n; //记录正在进行的 aio 数量

void init_aio_buf(aio_buf_t buf[], int buf_size) {
    for (int i = 0; i < buf_size; i++) {
        buf[i].op = UNUSED;
        buf[i].last = 0;
        buf[i].aiocb.aio_sigevent.sigev_notify = SIGEV_NONE;
        buf[i].aiocb.aio_buf = buf[i].data;
    }
}

void my_aio_read(aio_buf_t buf[], int fd) {
    off_t off = 0; //已读取字节数
    int data_size = 0; // 需要读取的数据长度(包括开头四字节)

    while (1) {
        for (int i = 0; i < N_AIO; i++) {
            switch (buf[i].op) {
                case UNUSED:
                    if (data_size != 0 && off < data_size) {
                        buf[i].op = READ_PENDING;
//                        buf[i].aiocb.aio_fildes =
                    }
            }
        }
    }

}

int main() {
    aio_buf_t buf[10];
    init_aio_buf(buf, 10);
}