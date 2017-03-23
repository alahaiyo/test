/*
*      daifs
*      daikunhai@hikvision.com
*
*/


#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/blkdev.h>
#include <linux/vfs.h>
#include "daifs.h"

#define DAIFS_MAGIC "daikunhai"


/*
void *daifs_read_super(struct super_block *sb, unsigned int offset, unsigned int len)
{
	return 0;
}
*/
static int daifs_fill_super(struct super_block *sb, void *data, int silent)
{
	struct daifs_super *super = NULL;

	super = kmalloc(sizeof(struct daifs_super), GFP_KERNEL);
	if(!super) {
		return -ENOMEM;
	}

//	memcpy(super, daifs_read_super(sb, 0, sizeof(struct daifs_super)), sizeof(struct daifs_super));

	return 0;
}

static int daifs_mount(struct file_system_type *fs_type,
	int flags, const char *dev_name, void *data, struct vfsmount *mnt)
{
	return get_sb_bdev(fs_type, flags, dev_name, data, daifs_fill_super, mnt);
}

static void daifs_kill_super(struct super_block *sb)
{
	
}

static struct file_system_type daifs_fs_type = {
	.owner		= THIS_MODULE,
	.name		= "daifs",
	.get_sb		= daifs_mount,
	.kill_sb	= daifs_kill_super,
	.fs_flags	= FS_REQUIRES_DEV,
};

static int __init init_daifs(void)
{
	int ret;

	ret = register_filesystem(&daifs_fs_type);
	if(ret < 0) {
		printk("Can't register daifs!\n");
	}

	return 0;
}
static void __exit exit_daifs(void)
{

}

module_init(init_daifs);
module_exit(exit_daifs);
MODULE_LICENSE("GPL");
