/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2021 MediaTek Inc. All Rights Reserved.
 *
 * Author: Weijie Gao <weijie.gao@mediatek.com>
 *
 * OpenWrt UBI image upgrading & booting helper
 */

#ifndef _UBI_HELPER_H_
#define _UBI_HELPER_H_

void ubi_probe_mtd_devices(void);
int ubi_upgrade_image(const void *data, size_t size);
int ubi_boot_image(void);

#define FIRST_IMAGE_NAME "ubi0"

#define SECOND_IMAGE_NAME "ubi1"


#endif /* _UBI_HELPER_H_ */
