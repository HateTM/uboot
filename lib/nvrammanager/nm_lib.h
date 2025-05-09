
/*! Copyright(c) 1996-2009 Shenzhen TP-LINK Technologies Co. Ltd.
 * \file    nm_lib.h
 * \brief   Protos for NVRAM manager's library functions.
 * \author  Meng Qing
 * \version 1.0
 * \date    25/04/2009
 */

#ifndef __NM_LIB_H__
#define __NM_LIB_H__

#ifdef __cplusplus
extern "C"{
#endif

/**************************************************************************************************/
/*                                      CONFIGURATIONS                                            */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                      INCLUDE_FILES                                             */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                      DEFINES                                                   */
/**************************************************************************************************/

#ifndef OK
#define OK (0)
#endif
#ifndef ERROR
#define ERROR (-1)
#endif

#ifndef	NULL
#define NULL            0
#endif
#ifndef	TRUE
#define TRUE            1
#endif
#ifndef FALSE
#define FALSE           0
#endif


/* ========= Global Configure Parameters ================== */
#ifndef NM_FLASH_SIZE
#define NM_FLASH_SIZE 0x2000000
#endif

#ifndef NM_PTN_TABLE_BASE
/* #define NM_PTN_TABLE_BASE 0xe50000 */
#elif NM_PTN_TABLE_BASE%0x10000
	#error "NM_PTN_TABLE_BASE IS NOT FLASH BLOCK ALIGNED!"
#elif NM_PTN_TABLE_BASE<0 || NM_PTN_TABLE_BASE>0x1000000
	#error "NM_PTN_TABLE_BASE IS INVALID!"
#endif

#define NM_PTN_TABLE_SIZE 0x002000


#define NM_OS_IMAGE_BASE 0x40000

#define NM_NVRAM_BASE 	0x000000  //0x9F000000

#define NM_PTN_NUM_MAX 64
#define NM_PTN_INDEX_SIZE 4096
#define NM_FWUP_PTN_INDEX_SIZE 2048 /* 0x800 */

#define USE_LOCK      0

#if USE_LOCK 
#define NM_SEM_TAKE semTake
#define NM_SEM_GIVE semGive
#else
#define NM_SEM_TAKE(lock, until)
#define NM_SEM_GIVE(lock)
#endif

#define WAIT_FOREVER	(-1)

/* ========= Generic Defines ============================== */
#define NM_UINT32 unsigned int
#define NM_PTN_NAME_LEN 32
#define NM_PTN_INDEX_ARG_NUM_MAX (NM_PTN_NUM_MAX*8)
#define NM_FWUP_PTN_INDEX_ARG_NUM_MAX (NM_PTN_NUM_MAX*8)

/* ========= Debug Info =================================== */
#define NM_DEBUG(fmt, ...) \
    printf("[NM_Debug](%s) %05d: "fmt"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define NM_ERROR(fmt, ...)  \
	printf("[NM_Error](%s) %05d: "fmt"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define NM_INFO(fmt, ...)  \
    printf(fmt, ##__VA_ARGS__)


/**************************************************************************************************/
/*                                      TYPES                                                     */
/**************************************************************************************************/

/* --------- Enum Defines ---------------- */
typedef enum nm_partition_index_para_id
{
    NM_PTN_INDEX_FILE_ID_VOID = -1, 
    NM_PTN_INDEX_PARA_ID_NAME, 
    NM_PTN_INDEX_PARA_ID_BASE, 
    NM_PTN_INDEX_PARA_ID_TAIL, 
    NM_PTN_INDEX_PARA_ID_SIZE, 
    NM_PTN_INDEX_PARA_ID_MAX,
} NM_PTN_INDEX_PARA_ID;

typedef enum nm_fwup_partition_index_para_id
{
    NM_FWUP_PTN_INDEX_FILE_ID_VOID = -1, 
    NM_FWUP_PTN_INDEX_PARA_ID_NAME, 
    NM_FWUP_PTN_INDEX_PARA_ID_BASE, 
    NM_FWUP_PTN_INDEX_PARA_ID_SIZE, 
    NM_FWUP_PTN_INDEX_PARA_ID_MAX,
} NM_FWUP_PTN_INDEX_PARA_ID;

typedef enum nm_fwup_upgrade_date_type
{
    NM_FWUP_UPGRADE_DATA_TYPE_VOID = -1, 
    NM_FWUP_UPGRADE_DATA_TYPE_BLANK, 
    NM_FWUP_UPGRADE_DATA_FROM_FWUP_FILE, 
    NM_FWUP_UPGRADE_DATA_FROM_NVRAM, 
	NM_FWUP_UPGRADE_DATA_TYPE_NO_CHANGE, 
    NM_FWUP_UPGRADE_DATA_TYPE_MAX,
} NM_FWUP_UPGRADE_DATA_TYPE;


/* --------- Data Structure ---------------- */
typedef struct nm_up_tbl_entry
{
    char name[NM_PTN_NAME_LEN];
    int base;
    int size;
    int content_type;
}NM_UP_PTN_ENTRY;

typedef struct nm_up_ptn_tbl
{
    int rootSize;
    int ptnNum;
    int isManu;
    NM_UP_PTN_ENTRY entries[NM_PTN_NUM_MAX];
}NM_UP_PTN_TBL_STRUCT;

typedef struct nm_str_map
{
    int key;
    char *str;
}NM_STR_MAP;

typedef struct nm_upgrade_info
{
    NM_UINT32 dataStart;
    NM_UINT32 dataLen;
    int dataType;
} NM_UPGRADE_INFO;

typedef struct nm_partition_entry
{
    char name[NM_PTN_NAME_LEN];
    NM_UINT32 base;
    NM_UINT32 tail;
    NM_UINT32 size;
    unsigned int usedFlag;
    NM_UINT32 usedSize;
    NM_UPGRADE_INFO upgradeInfo;
} NM_PTN_ENTRY;

typedef struct nm_partition_list
{
    NM_PTN_ENTRY entries[NM_PTN_NUM_MAX];
} NM_PTN_STRUCT;



/**************************************************************************************************/
/*                                      FUNCTIONS                                                 */
/**************************************************************************************************/
int nm_lib_parseU32(NM_UINT32 *val, const char *arg);
int nm_lib_makeArgs(char *string, char *argv[], int maxArgs);
int nm_lib_strToKey(NM_STR_MAP *map, char *str);
NM_PTN_ENTRY *nm_lib_ptnNameToEntry(NM_PTN_STRUCT *ptnStruct, char *name);


NM_PTN_ENTRY *nm_lib_ptnNameToEntry(NM_PTN_STRUCT *ptnStruct, char *name);
int nm_lib_readPtnFromNvram(char *base, char *buf, int len);
int nm_lib_readHeadlessPtnFromNvram(char *base, char *buf, int len);
int nm_lib_writePtnToNvram(char *base, char *buf, int len);
int nm_lib_writeHeadlessPtnToNvram(char *base, char *buf, int len);
void nm_lib_showPtn(void);
int nm_lib_eraseNandNvram(loff_t off, loff_t size);
int nm_lib_writeNandNvram(char *buf, loff_t off, loff_t len, loff_t max_size);

extern int nm_flashOpPortInit(void);
extern int nm_flashOpPortFree(void);
extern int nm_flashOpPortErase(unsigned int off, unsigned int len);
extern int nm_flashOpPortRead(unsigned int off, unsigned char *in, unsigned int len);
extern int nm_flashOpPortWrite(unsigned int off, unsigned char *in, unsigned int len);


extern int nvram_emmc_write(unsigned int *address, const void *data, int len);
extern unsigned int nvram_emmc_getsize(void);

/**************************************************************************************************/
/*                                      VARIABLES                                                 */
/**************************************************************************************************/

extern NM_PTN_STRUCT *g_nmPtnStruct;
#if USE_LOCK
extern SEM_ID g_nmReadWriteLock;
#endif



#ifdef __cplusplus 
}
#endif

#endif /* __NM_LIB_H__ */

