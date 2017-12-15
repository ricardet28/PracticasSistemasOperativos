/*
 * The below are header files provided by the kernel which are
 * required for all modules.  They include things like the definition
 * of the module_init() macro.
 */
#include <linux/init.h>
#include <linux/module.h>

/*
 * This is the init function, which is run when the module is first
 * loaded.  The __init keyword tells the kernel that this code will
 * only be run once, when the module is loaded.
 */

static int __init hola_init(void) {
	printk("Hola Mundo!\n");
	return 0;
}

/*
 * The below macro informs the kernel as to which function to use as
 * the init function.
 */



/*
 * Similary, the exit function is run once, upon module unloading, and
 * the module_exit() macro identifies which function is the exit
 * function.
 */

static void __exit hola_exit(void) {
	printk("Adios Mundo!\n");
}

module_init(hola_init);
module_exit(hola_exit);

/*
 * MODULE_LICENSE() informs the kernel what license the module source
 * code is under, which affects which symbols it may access in the
 * main kernel.  Certain module licenses will "taint" the kernel,
 * indicating that non-open or untrusted code has been loaded.
 * Modules licensed under GPLv2 do not taint the kernel and can access
 * all symbols, but declaring it so is a legal statement that the
 * source code to this module is licensed under GPLv2, and so you must
 * provide the source code if you ship a binary version of the module.
 */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Borja Mondeiorc borj@uji.es>");
MODULE_DESCRIPTION("Hola Mundo!");
MODULE_VERSION("Saludos");
