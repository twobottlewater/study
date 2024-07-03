#include <linux/module.h> //内核模块接口头文件
#include <linux/printk.h> //printk函数头文件
#include <linux/cdev.h> // struct cdev
#include <linux/fs.h>  //struct file_operations
#include <linux/device.h> //struct class
#include <linux/err.h> //#define	ENOMEM		12
#include <linux/io.h> //ioremap
#include <linux/ioport.h> //request_mem_region
#include <linux/uaccess.h> //copy_from_user

static dev_t gec6818led_dev;//定义一个设备号
static unsigned int major = 0; //主设备号表示该设备是哪一类设备
static unsigned int minor = 0; //次设备号表示这类设备中哪一个设备

static struct class *gec6818led_class = NULL;
static struct device *gec6818led_device = NULL;
//D7 物理内存区
static struct resource *gec6818led_res = NULL;
//D10 D8 D9 物理内存区
static struct resource *gec6818led_cres = NULL;

//D7虚拟地址:
static void __iomem *gec6818led_va_base = NULL;
//GPIOEOUT ----0xC001E000
static void __iomem *gec6818led_va_eout = NULL;
//GPIOEOUTENB --- 0xC001E004
static void __iomem *gec6818led_va_eoutenb = NULL;
//GPIOEALTFN0 ---- 0xC001E020
static void __iomem *gec6818led_va_ealtfn0 = NULL;

//D8--GPIOC17 D10--GPIOC7 D9--GPIOC8 虚拟地址

//GPIOCOUT ----0xC001C000
static void __iomem *gec6818led_va_cout = NULL;
//GPIOCOUTENB --- 0xC001C004
static void __iomem *gec6818led_va_coutenb = NULL;
//GPIOCALTFN0 ---- 0xC001C020
static void __iomem *gec6818led_va_caltfn0 = NULL;
//GPIOCALTFN1 ---- 0xC001C024
static void __iomem *gec6818led_va_caltfn1 = NULL;

static void __iomem *gec6818led_va_cbase = NULL;
int gec6818led_open (struct inode *node, struct file *file)
{

	return 0;
}

/*
驱动程序与应用程序之间的数据传输：
问题一：
  数据协议：系统调用(open write ) ----> struct file_operations --- write
问题二：
    数据格式：控灯：一个灯  定义一个数组：char kbuf[1]  --- kbuf[0] --->表示控制灯的命令：1 ---开灯 0 --- 关灯 
	                 多个灯  定义一个数组：char kbuf[2] ---- kbuf[0] --->表示控制灯的命令，kbuf[1] --- 表示灯的编号
  驱动程序和应用程序之间的数据协议+数据格式要保持 一致
  
  对于驱动程序使用的内核空间，而应用程序使用的是用户空间，两个空间之间不能直接相互访问，只能通过特定的接口：
  copy_to_user
  copy_from_user
*/
ssize_t gec6818led_write(struct file *file, const char __user *buf, size_t size, loff_t *offset)
{
	 printk(KERN_WARNING "gec6818led_write\n");
	//[1]因为是多个灯，所以定义数据格式
	char kbuf[2]; //kbuf[0] --->表示控制灯的命令 kbuf[1] --- 表示灯的编号
	int ret;
	//int copy_from_user(void *to, const void __user *from, int n)
	ret = copy_from_user(kbuf,buf,size); //从用户空间把数据获取出来存放在kbuf中
	//[2] 根据数据的命令来实现控制硬件

	switch(kbuf[1])
	{
		case 7: //D7
			if(kbuf[0] == 1) //开灯
			{
				 *((volatile unsigned int*)gec6818led_va_eout) &= ~(1<<13);
			}else if(kbuf[0] == 0)//关灯
			{
				 *((volatile unsigned int*)gec6818led_va_eout) |= (1<<13);
			}
		break;
		case 8: //D8
			if(kbuf[0] == 1) //开灯
			{
				 *((volatile unsigned int*)gec6818led_va_cout) &= ~(1<<17);
			}else if(kbuf[0] == 0)//关灯
			{
				 *((volatile unsigned int*)gec6818led_va_cout) |= (1<<17);
			}
		break;
		case 9: //D9
			if(kbuf[0] == 1) //开灯
			{
				 *((volatile unsigned int*)gec6818led_va_cout) &= ~(1<<8);
			}else if(kbuf[0] == 0)//关灯
			{
				 *((volatile unsigned int*)gec6818led_va_cout) |= (1<<8);
			}
		break;
		case 10: //D10
			if(kbuf[0] == 1) //开灯
			{
				 *((volatile unsigned int*)gec6818led_va_cout) &= ~(1<<7);
			}else if(kbuf[0] == 0)//关灯
			{
				 *((volatile unsigned int*)gec6818led_va_cout) |= (1<<7);
			}
		break;
	}
	return size;
}
//2.定义一个普通字符设备的文件操作集对象
static struct file_operations gec6818led_fops = {
	.owner = THIS_MODULE,
	.open = gec6818led_open,
	.write = gec6818led_write,
};

//1.定义一个普通字符设备对象
static struct cdev  gec6818led_cdev;





static int __init gec6818led_init(void)
{
	int ret;
    printk(KERN_WARNING "gec6818led_init\n");
	
	//3.申请一个设备号，设备号就相当于一个人的身份证号码一样，在Linux它是唯一，设备号还要注册到linux内核中，
	//如果内核中没有，则说明设备号可用，否则，不行
	if(major == 0)//动态注册
	{
		//int alloc_chrdev_region(dev_t *dev, unsigned baseminor, unsigned count,
			//const char *name)
		ret = alloc_chrdev_region(&gec6818led_dev,minor,1,"gec6818led_number");
	}else //静态注册
	{
		//先由主设备号和次设备号生成一个设备号
		gec6818led_dev = MKDEV(major,minor);
		//再将设备号注册到内核中 int register_chrdev_region(dev_t from, unsigned count, const char *name)
		ret = register_chrdev_region(gec6818led_dev,1,"gec6818led_number");
	}
	
	  if(ret != 0)
	  {
		  printk(KERN_WARNING "register_device_number error\n");
		  goto register_device_number_error;
	  }
	//4.初始化普通字符设备 void cdev_init(struct cdev *, const struct file_operations *);
	cdev_init(&gec6818led_cdev,&gec6818led_fops); //在初始化函数中，对普通字符设备与文件操作集进行了关联
	
	//5. 增加字符设备到内核中 int cdev_add(struct cdev *p, dev_t dev, unsigned count)
	ret = cdev_add(&gec6818led_cdev,gec6818led_dev,1);
	 if(ret != 0)
	  {
		  printk(KERN_WARNING "cdev_add error\n");
		  goto cdev_add_error;
	  }
	  //6.创建一个class struct class * class_create(struct module *owner, const char *name)
	  gec6818led_class = class_create(THIS_MODULE,"gec6818led_class");
	  if(gec6818led_class == NULL)
	  {
		   printk(KERN_WARNING "class_create error\n");
		   //如果函数返回的值不是整型，但是，总函数中的返回值为整型 ，所以，要重新给ret设置一个返回值
		   ret =  -ENOMEM; // #define	ENOMEM		12	/* Out of memory */ 这个宏常量的头文件引用进来
		   goto class_create_error;
	  }
	  //7.创建device struct device *device_create(struct class *class, struct device *parent,
			   //  dev_t devt, void *drvdata, const char *fmt, ...)
	  gec6818led_device = device_create(gec6818led_class,NULL,gec6818led_dev,NULL,"led_drv");
	  if(gec6818led_device == NULL)
	  {
		   printk(KERN_WARNING "device_create error\n");
		   ret = -ENOMEM;
		   goto device_create_error;
	  }
	  
	  //8.申请物理内存区
	  //struct resource *request_mem_region(resource_size_t start, resource_size_t n,
		//		   const char *name)
		//该函数的参数的传递，要根据具体的硬件的地址来确定，以D7 --- GPIOE13  0XC001E000
		//申请物理内存区的大小，最好跟GPIO口分组：A组的大小：0XC001A000 B：0xc001b000 ---> B-A --0x1000--4kb
		gec6818led_res = request_mem_region(0XC001E000,0x1000,"GPIOE_MEM");
		if(gec6818led_res == NULL)
		{
			 printk(KERN_WARNING "request_mem_region error\n");
			 ret =  -EBUSY; //#define	EBUSY		16	/* Device or resource busy */
			 goto request_mem_region_error;
		}
		//9.Io动态映射 void __iomem *ioremap(unsigned long phys_addr, size_t size)
		gec6818led_va_base = ioremap(0XC001E000,0x1000);
		
	     if(gec6818led_va_base == NULL)
		{
			 printk(KERN_WARNING "ioremap error\n");
			 ret =  -EBUSY; //#define	EBUSY		16	/* Device or resource busy */
			 goto ioremap_error;
		}
		gec6818led_va_eout = gec6818led_va_base + 0x00;
		gec6818led_va_eoutenb = gec6818led_va_base + 0x04;
		gec6818led_va_ealtfn0 = gec6818led_va_base + 0x20;
		
		//[1] 设置引脚的功能
		 *((volatile unsigned int*)gec6818led_va_ealtfn0) &= ~(3<<26);
		 //[2]设置引脚的工作模式:输出
		  *((volatile unsigned int*)gec6818led_va_eoutenb) |= (1<<13);
		   //[3] 默认设置LED灯为灭
		   *((volatile unsigned int*)gec6818led_va_eout) |= (1<<13);
		 
		//D8 D9 D10 ,他们跟D7一样，先进行物理内存区申请和IO动态映射
		gec6818led_cres = request_mem_region(0XC001C000,0x1000,"GPIOC_MEM");
		if(gec6818led_res == NULL)
		{
			 printk(KERN_WARNING "request_mem_region error\n");
			 ret =  -EBUSY; //#define	EBUSY		16	/* Device or resource busy */
			 goto request_cmem_region_error;
		}
		//9.Io动态映射 void __iomem *ioremap(unsigned long phys_addr, size_t size)
		gec6818led_va_cbase = ioremap(0XC001C000,0x1000);
		
	     if(gec6818led_va_cbase == NULL)
		{
			 printk(KERN_WARNING "ioremap error\n");
			 ret =  -EBUSY; //#define	EBUSY		16	/* Device or resource busy */
			 goto cioremap_error;
		}
		
		gec6818led_va_cout = gec6818led_va_cbase + 0x00;
		gec6818led_va_coutenb = gec6818led_va_cbase + 0x04;
		gec6818led_va_caltfn0 = gec6818led_va_cbase + 0x20;
		gec6818led_va_caltfn1 = gec6818led_va_cbase + 0x24;
		//[1] 设置引脚的功能 GPIOC17 GPIOC8   GPIOC7
		 *((volatile unsigned int*)gec6818led_va_caltfn1) &= ~(1<<3);
         *((volatile unsigned int*)gec6818led_va_caltfn1) |= (1<<2);
		 
		 *((volatile unsigned int*)gec6818led_va_caltfn0) &= ~(1<<17);
		 *((volatile unsigned int*)gec6818led_va_caltfn0) |= (1<<16);
	     *((volatile unsigned int*)gec6818led_va_caltfn0) &= ~(1<<15);
         *((volatile unsigned int*)gec6818led_va_caltfn0) |= (1<<14);
		 //[2] 设置引脚的工作模式:输出
		 *((volatile unsigned int*)gec6818led_va_coutenb) |= (1<<17) | (1<<8) | (1<<7);
		 //[3] 设置灯的状态：灭
		 *((volatile unsigned int*)gec6818led_va_cout) |= (1<<17) | (1<<8) | (1<<7);
	return 0;
	cioremap_error:
	release_mem_region(0XC001C000,0x1000);
	request_cmem_region_error:
	iounmap(gec6818led_va_base);
	ioremap_error:
	release_mem_region(0XC001E000,0x1000);
	request_mem_region_error:
	device_destroy(gec6818led_class,gec6818led_dev);
	device_create_error:
	class_destroy(gec6818led_class);
	 gec6818led_class = NULL;
	class_create_error:
	cdev_del(&gec6818led_cdev);
	cdev_add_error:
	unregister_chrdev_region(gec6818led_dev,1);
	register_device_number_error:
	return ret;
	
}

static void __exit gec6818led_exit(void)
{
    printk(KERN_WARNING "gec6818led_exit\n");
	//进行资源的释放 
	iounmap(gec6818led_va_cbase);
	gec6818led_va_cbase = NULL;
	release_mem_region(0XC001C000,0x1000);
	
	iounmap(gec6818led_va_base);
	gec6818led_va_base = NULL;
	release_mem_region(0XC001E000,0x1000);
	//void device_destroy(struct class *class, dev_t devt)
	device_destroy(gec6818led_class,gec6818led_dev);
	//void class_destroy(struct class *cls)
	 class_destroy(gec6818led_class);
	 gec6818led_class = NULL;
	//void cdev_del(struct cdev *p)
	cdev_del(&gec6818led_cdev);
	
	//void unregister_chrdev_region(dev_t from, unsigned count)
	
	unregister_chrdev_region(gec6818led_dev,1);
}

module_init(gec6818led_init);
module_exit(gec6818led_exit);

MODULE_AUTHOR("gec.zhang3");//驱动作者
MODULE_DESCRIPTION("GEC6818 Led driver");//驱动的描述
MODULE_LICENSE("GPL"); //module所遵守的协议许可,GPL---->公共通用许可证