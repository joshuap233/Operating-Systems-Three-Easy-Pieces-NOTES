//
// Created by pjs on 2020/12/20.
//

#ifndef OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_MYAIO_H
#define OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_MYAIO_H

// 如何判断 socket 是否读到末尾呢?
// 这里规定前发送端发送的四字节必须为接下来需要发送的数据长度
// 前四字节称为 header
// 规定双方一次发送(一次write或send)的字节数为 MAX_MSG

#define BUF_SIZE 4096
#define N_AIO 10
#define MAX_MSG 4096
#define HEADER_LEN 4

#include <aio.h>


// aiocb 状态
enum aio_op {
    UNUSED = 0,
    READ_PENDING = 1,
//    WAITE_PENDING = 2
};

// 记录 aiocb 状态
typedef struct aio_buf {
    enum aio_op op;
    int finish; // 已经读取的数据量, finish == MAX_MSG 时,则读取完成,初始为 0
    int off;
    // 记录第一次 buf 的读取偏移量,下次需要读取的偏移量为 off+finish
    // 从网络中读取时,网络中的缓存机制可能造成返回值小于所要求的字节数
    struct aiocb aiocb;
    unsigned char data[MAX_MSG];
} aio_buf_t;

typedef int aio_n; //记录正在进行的 aio 数量

void my_aio_read(aio_buf_t buf[], int sock_fd);

void init_aio_buf(aio_buf_t buf[], int buf_size);

#endif //OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_MYAIO_H
