/* TinyELF example file | Spencer Tipping */
/* Licensed under the terms of the MIT source code license */

/* See README.md for compilation instructions */
#include <asm/unistd.h>

/* Function definition order matters because this program will never be linked.
 * As a result, we forward-define syscall() and make _start() the first
 * concrete definition. */

long syscall(long n,
             long a1, long a2, long a3, long a4, long a5, long a6);

/* ELF entry point will point straight into the body of _start(), as it is the
 * first concrete function in this file. */
void _start() {
  /* Must be declared as a locally-allocated variable. If we made it a pointer
   * to a global (e.g. const char *message = "hello world\n"), then the text
   * "hello world" would be lost during the objcopy conversion. */
  const char message[12] = "hello world\n";
  syscall(__NR_write, 1, message, 12, 0, 0, 0);
  syscall(__NR_exit, 0, 0, 0, 0, 0, 0);
}

long syscall(long n, long a1, long a2, long a3, long a4, long a5, long a6) {
  /* x86-64 kernel syscall convention:
   * %rax = syscall number
   * 6 arguments in %rdi, %rsi, %rdx, %r10, %r8, %r9 */
  asm volatile ("movq %4, %%r10;"
                "movq %5, %%r8;"
                "movq %6, %%r9;"
                "syscall;"

               : "=a"(n)
               : "a"(n), "D"(a1), "S"(a2), "d"(a3),
                         "r"(a4), "r"(a5), "r"(a6)
               : "%r10", "%r8", "%r9");
  return n;
}

