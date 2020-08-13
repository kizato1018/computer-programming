 #include <linux/kernel.h>
 #include <sys/syscall.h>
 #include <unistd.h>

 int main() {
     syscall(1, 1, "Hello, world\n", 14);
     return 0;
 }