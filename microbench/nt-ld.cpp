#include "uarch.h"

int main() {
    int i;
    long long aggregated = 0, aggregated2 = 0;
    long seed = 0xdeadbeef1245678;
    uint64_t a = 0xfc0;
    int access_size = 64;
    int stride_size = 64;
    int delay = 64;
    int count = 32;
    uint64_t *cindex;
    uint64_t csize;
    int ret;

    //    for (i = 0; i < 100000; i++) {
    //        char *buf = malloc(4096 * 1024);
    //        buf = buf + 64 - (((long)buf) % 64);
    //        // Separate RaW job
    //        RAW_BEFORE_WRITE
    //        stride_storeclwb(buf, access_size, stride_size, delay, count);
    //        asm volatile("mfence \n" :::);
    //        RAW_BEFORE_READ
    //        stride_nt(buf, access_size, stride_size, delay, count);
    //        asm volatile("mfence \n" :::);
    //        RAW_FINAL("raw-separate")
    //
    //        aggregated += diff;
    //        aggregated2 += c_ntload_end - c_store_start;
    //    }
    //
    //    printf("Separate RaW job %lld %lld\n", aggregated / 100000 / count, aggregated2 / 100000 / count);
    aggregated = 0;
    aggregated2 = 0;
    for (i = 0; i < 100000; i++) {
        char *buf = static_cast<char *>(malloc(4096 * 1024));
        buf = buf + 64 - (((long)buf) % 64);
        // Naive RaW job
        RAW_BEFORE_WRITE
        RAW_BEFORE_READ
        stride_read_after_write(buf, access_size, stride_size, delay, count);
        asm volatile("mfence \n" :::);
        RAW_FINAL("raw-combined")
        aggregated += diff;
        aggregated2 += c_ntload_end - c_store_start;
    }
    printf("Naive RaW job %lld %lld\n", aggregated / 100000 / count, aggregated2 / 100000 / count);
    aggregated = 0;
    aggregated2 = 0;

    //    for (i = 0; i < 100000; i++) {
    //        char *buf = malloc(4096 * 1024);
    //        buf = buf + 64 - (((long)buf) % 64);
    //        RAW_BEFORE_WRITE
    //        sizebw_storeclwb(buf, access_size, count, &seed, a);
    //        asm volatile("mfence \n" :::);
    //        RAW_FINAL("sizebw_storeclwb")
    //        aggregated += diff;
    //        aggregated2 += c_ntload_end - c_store_start;
    //    }
    //    printf("sizebw_storeclwb %lld %lld\n", aggregated / 100000 / count, aggregated2 / 100000 / count);
    //
    //    aggregated = 0;
    //    aggregated2 = 0;
    //    for (i = 0; i < 100000; i++) {
    //        char *buf = malloc(4096 * 1024);
    //        buf = buf + 64 - (((long)buf) % 64);
    //        char *virt_addr = malloc(4096 * 1024);
    //        virt_addr = virt_addr + 64 - (((long)virt_addr) % 64);
    //        // Pointer chasing RaW job
    //        // No need to fill report fs page table, init_chasing_index will do that
    //        csize = access_size / CACHELINE_SIZE;
    //        cindex = (uint64_t *)(virt_addr);
    //        ret = init_chasing_index(cindex, csize);
    //
    //        RAW_BEFORE_WRITE
    //        chasing_storeclwb(buf, access_size, stride_size, count, cindex);
    //        asm volatile("mfence \n" :::);
    //        RAW_BEFORE_READ
    //        chasing_loadnt(buf, access_size, stride_size, count, cindex);
    //        asm volatile("mfence \n" :::);
    //        RAW_FINAL("raw-chasing")
    //
    //        aggregated += diff;
    //        aggregated2 += c_ntload_end - c_store_start;
    //    }
    //    printf("pointer chasing 2 hop %lld %lld\n", aggregated / 100000 / count, aggregated2 / 100000 / count);
    //
    //    aggregated = 0;
    //    aggregated2 = 0;
    //    for (i = 0; i < 100000; i++) {
    //        char *buf = malloc(4096 * 1024);
    //        buf = buf + 64 - (((long)buf) % 64);
    //        char *virt_addr = malloc(4096 * 1024);
    //        virt_addr = virt_addr + 64 - (((long)virt_addr) % 64);
    //        // Pointer chasing RaW job
    //        // No need to fill report fs page table, init_chasing_index will do that
    //        csize = access_size / CACHELINE_SIZE;
    //        cindex = (uint64_t *)(virt_addr);
    //        ret = init_chasing_index(cindex, csize);
    //
    //        RAW_BEFORE_WRITE
    //        chasing_storeclwb(buf, access_size, stride_size, count, cindex);
    //        asm volatile("mfence \n" :::);
    //        RAW_BEFORE_READ
    //        chasing_loadnt(buf, access_size, stride_size, count, cindex);
    //        asm volatile("mfence \n" :::);
    //        chasing_storeclwb(buf, access_size, stride_size, count, cindex);
    //        asm volatile("mfence \n" :::);
    //        chasing_loadnt(buf, access_size, stride_size, count, cindex);
    //        asm volatile("mfence \n" :::);
    //        RAW_FINAL("raw-chasing")
    //
    //        aggregated += diff;
    //        aggregated2 += c_ntload_end - c_store_start;
    //    }
    //    printf("pointer chasing 4 hop %lld %lld\n", aggregated / 100000 / count, aggregated2 / 100000 / count);
    return 0;
}
