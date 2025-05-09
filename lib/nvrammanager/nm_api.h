
/*! Copyright(c) 1996-2009 Shenzhen TP-LINK Technologies Co. Ltd.
 * \file    nm_lib.h
 * \brief   Protos for NVRAM manager's api functions.
 * \author  Meng Qing
 * \version 1.0
 * \date    25/04/2009
 */

#ifndef NM_API_H
#define NM_API_H

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

#define TP_BOOT_IDX     "tp_boot_idx"

#define NM_PTN_NAME_FS_UBOOT "fs-uboot"
	
#define NM_PTN_NAME_PTN_TABLE "partition-table"

#define NM_PTN_NAME_DEFAULT_MAC "default-mac"
#define NM_PTN_NAME_PIN	"pin"
#define NM_PTN_NAME_PRODUCT_INFO "product-info"
#define NM_PTN_NAME_SOFT_VERSION "soft-version"

#define NM_PTN_NAME_SUPPORT_LIST "support-list"
	
#define NM_PTN_NAME_OS_IMAGE "os-image"

#define NM_PTN_NAME_FILE_SYSTEM "file-system"

#define NM_PTN_NAME_USER_CFG "user-config"

#define NM_PTN_NAME_DEFAULT_CFG "default-config"
	
#define NM_PTN_NAME_RADIO "radio"

#define NM_PTN_NAME_LOG "log"


/* end add */



/**************************************************************************************************/
/*                                      FUNCTIONS                                                 */
/**************************************************************************************************/


int nm_api_getOSoffset(char * pAppBuf);

/**************************************************************************************************/
/*                                      VARIABLES                                                 */
/**************************************************************************************************/
typedef struct 
{
    char name[32];
    unsigned int start_addr;
	unsigned int next_offset;
    unsigned int size;
}nflash_partitions;

#ifdef __cplusplus 
}
#endif

#endif /* NM_API_H */

