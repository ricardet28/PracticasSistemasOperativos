#include <linux/init.h>
#include <lnux/module.h>

static int __init hola_init(void){

	printk("Hola mundo!\n");
	retrn 0;
}

static void __exit hola_exit(void){
	printk("Adiós mundo! \n");
}


