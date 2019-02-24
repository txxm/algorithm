环形队列的实现：
1.创建环形队列，以数组形式创建。
	int32_t ringbuf_create(size_t count, size_t nbyte). 参数count表示环形数组的元素数量，参数nbyte表示每个元素的大小。
2.向环形队列添加数据
	int32_t ringbuf_snd(int32_t data). 参数data表示要添加的数据。
3.从环形队列读取数据
	int32_t ringbuf_rcv(int32_t *pval).参数pval表示指向环形队列元素的指针。

ringbuf.h和ringbuf.c文件为封装的函数，main.c文件为测试用例，输出0-999的数。
