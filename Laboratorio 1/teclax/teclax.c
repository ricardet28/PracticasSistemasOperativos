#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <asm/io.h>

/**********************************************/
/* This function services keyboard interrupts */
/**********************************************/

irq_handler_t irq_handler (int irq, void *dev_id, struct pt_regs *regs) {
	static unsigned char scancode;
	static char * const shutdown_argv[] = { "/sbin/shutdown", "-h", "-P", "now", NULL };
	scancode = inb (0x60); /* Read keyboard status */
	if (scancode == 0x2D) {
		printk ("You pressed key X\n");

		
		call_usermodehelper(shutdown_argv[0], shutdown_argv, NULL, UMH_NO_WAIT);

	}			
	return (irq_handler_t) IRQ_HANDLED;
}

/*====================================================*/
/* Initialize the module and Register the IRQ handler */
/*====================================================*/
static int __init keybrd_int_register(void) {
	int result;
	printk(KERN_INFO "Init key module\n");
	/* Request IRQ 1, the keyboard IRQ */
	result   =   request_irq   (1,   (irq_handler_t)   irq_handler,   IRQF_SHARED,
"keyboard_stats_irq", (void *)(irq_handler));
	if (result)
		printk(KERN_INFO "can't get shared interrupt for keyboard\n");
	return result;
}
/********************************/
/* Remove the interrupt handler */
/********************************/
static void __exit keybrd_int_unregister(void) {
	printk(KERN_INFO "Exit key module\n");
	free_irq (1, (void *)(irq_handler));
}



/********************************/
/* Module init/exit             */
/********************************/
module_init(keybrd_int_register);
module_exit(keybrd_int_unregister);
