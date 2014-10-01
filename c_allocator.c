#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "c_allocator.h"

typedef struct {
unsigned int fullSize;   // メモリブロック総サイズ
void *freeMemPtr;        // フリーメモリブロックへのポインタ
}AllocInfo;

typedef struct {
  unsigned int size;   // 貸し出しメモリサイズ
  char mem[0];         // メモリブロック
}MemInfo;

/* mthod prototype declaration */
void info_logger(AllocInfo *info);
void memi_logger(MemInfo *memInfo);

/* field */
void *mem_block;
AllocInfo *info;

void m_create(){
  size_t per_ptr_size = 1;
  int alloc_mem_num = 1000;
  size_t total_mem_block_size = per_ptr_size * alloc_mem_num;

  // 元となるメモリブロックを確保する
  mem_block = malloc(total_mem_block_size);
  // printf(" m_blk adr : %p\n",mem_block);

  // 管理情報をメモリブロックの先頭に配置
  info = (AllocInfo *)mem_block;
  info->fullSize = total_mem_block_size;
  info->freeMemPtr = mem_block;
  // info_logger(info);
  
  // メモリブロックの先頭アドレスを管理情報分進める
  info->freeMemPtr += sizeof(AllocInfo);
  // printf(" m_blk adr : %p\n",mem_block);
  // info_logger(info);

  return;
  //  free(mem_block);
}

void *m_allocate(size_t mem_size){
  printf("/********* allocate *********/\n");
  info_logger(info);

  // 貸し出しメモリの管理情報を作成
  printf("貸し出しメモリの管理情報を作成\n"); 
  MemInfo *memInfo = (MemInfo *)info->freeMemPtr;
  memInfo->size = mem_size;
  memi_logger(memInfo);

  printf("管理情報のサイズ分ポインタを進める\n"); 
  info->freeMemPtr += sizeof(MemInfo);
  info_logger(info);

  // 現在のフリーメモリブロックの先頭ポインタを取得
  void *ptr = info->freeMemPtr;
  printf(" ptr adr   : %p\n",ptr);

  printf("貸し出しサイズ分ポインタを進める\n");
  info->freeMemPtr += mem_size;
  info_logger(info);

  printf("貸し出しサイズ分ポインタを進める前のポインタを返す\n");
  return ptr;
}

void m_free(void* ptr){
  printf("/********* free *********/\n");

  void *tmp = ptr;
  ptr -= sizeof(MemInfo);
  printf(" ptr adr   : %p\n",ptr);
  printf(" tmp adr   : %p\n",tmp);
  // 貸し出しメモリの管理情報を抽出
  printf("貸し出しメモリの管理情報を抽出\n"); 
  MemInfo *memInfoAdr = (MemInfo *)ptr;
  MemInfo memInfo = *memInfoAdr;
  memset(&memInfo,0,sizeof(MemInfo));
  memi_logger(memInfoAdr);
  ptr = NULL;
  tmp = NULL;
  printf(" ptr adr   : %p\n",ptr);
  printf(" tmp adr   : %p\n",tmp);
}


void info_logger(AllocInfo *info){
  printf("/********* info logger *********/\n");
  printf(" i adr     : %p\n",info);
  printf(" i fll     : %d\n",info->fullSize);
  printf(" i fll adr : %p\n",&info->fullSize);
  printf(" i ptr adr : %p\n",info->freeMemPtr);
  printf("/*******************************/\n");
}

void memi_logger(MemInfo *memInfo){
  printf("/********* memi logger *********/\n");
  printf("mi adr     : %p\n",memInfo);
  printf("mi sz      : %d\n",memInfo->size);
  printf("mi sz adr  : %p\n",&memInfo->size);
  printf("mi mem     : %p\n",memInfo->mem);
  printf("/*******************************/\n");
}
