◦ write
◦ ft_printf and any equivalent YOU coded
◦ signal
◦ sigemptyset
◦ sigaddset
◦ sigaction
◦ kill
◦ getpid
◦ malloc
◦ free
◦ pause
◦ sleep
◦ usleep
◦ exit

## usleep

## sleep

## pause

## free

## malloc

## getpid

## kill
```c
#include <sys/types.h>
#include <signal.h>
int kill(pid_t pid, int sig);
```
The kill() system call can be used to send any signal to any process group or process.
If pid is positive, then signal sig is sent to the process with the ID specified by pid.
If pid equals 0, then sig is sent to every process in the process group of the calling process.
If pid equals -1, then sig is sent to every process for which the calling process has permission to send signals, except for process 1 (init), but see below.
If pid is less than -1, then sig is sent to every process in the process group whose ID is -pid.
If sig is 0, then no signal is sent, but error checking is still performed; this can be used to check for the existence of a process ID or process group ID.




## signal
```c
#include <signal.h>
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
```
The behavior of signal() varies across UNIX versions, and has also varied historically across different versions of Linux. Avoid its use: use sigaction(2) instead.

signal() sets the disposition of the signal signum to handler, which is either SIG_IGN, SIG_DFL, or the address of a programmer-defined function (a "signal handler").
If the signal signum is delivered to the process, then one of the following happens:
* If the disposition is set to SIG_IGN, then the signal is ignored.
* If the disposition is set to SIG_DFL, then the default action associated with the signal (see signal(7)) occurs.
* If the disposition is set to a function, then first either the disposition is reset to SIG_DFL, or the signal is blocked 
(see Portability below), and then handler is called with argument signum. If invocation of the handler caused the signal to be blocked, then the signal is unblocked upon return from the handler.
The signals SIGKILL and SIGSTOP cannot be caught or ignored.

signal() returns the previous value of the signal handler, or SIG_ERR on error.

## sigaction
```c
#include <signal.h>
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
```
The sigaction() system call is used to change the action taken by a process on receipt of a specific signal.
signum specifies the signal and can be any valid signal except SIGKILL and SIGSTOP.
If act is non-NULL, the new action for signal signum is installed from act. If oldact is non-NULL, the previous action is saved in oldact.
The sigaction structure is defined as something like:
```c
struct sigaction {
    void     (*sa_handler)(int);
    void     (*sa_sigaction)(int, siginfo_t *, void *);
    sigset_t   sa_mask;
    int        sa_flags;
    void     (*sa_restorer)(void);
};
```
The sa_restorer element is obsolete and should not be used. POSIX does not specify a sa_restorer element.
On some architectures a union is involved: do not assign to both sa_handler and sa_sigaction.
sa_handler specifies the action to be associated with signum and may be SIG_DFL for the default action, SIG_IGN to ignore this signal, or a pointer to a signal handling function. This function receives the signal number as its only argument.
If SA_SIGINFO is specified in sa_flags, then sa_sigaction (instead of sa_handler) specifies the signal-handling function for signum. This function receives the signal number as its first argument, a pointer to a siginfo_t as its second argument and a pointer to a ucontext_t (cast to void *) as its third argument. 
```c
siginfo_t {
    int      si_signo;    /* Signal number */
    int      si_errno;    /* An errno value */
    int      si_code;     /* Signal code */
    int      si_trapno;   /* Trap number that caused
                             hardware-generated signal
                             (unused on most architectures) */
    pid_t    si_pid;      /* Sending process ID */
    uid_t    si_uid;      /* Real user ID of sending process */
    int      si_status;   /* Exit value or signal */
    clock_t  si_utime;    /* User time consumed */
    clock_t  si_stime;    /* System time consumed */
    sigval_t si_value;    /* Signal value */
    int      si_int;      /* POSIX.1b signal */
    void    *si_ptr;      /* POSIX.1b signal */
    int      si_overrun;  /* Timer overrun count; POSIX.1b timers */
    int      si_timerid;  /* Timer ID; POSIX.1b timers */
    void    *si_addr;     /* Memory location which caused fault */
    long     si_band;     /* Band event (was int in
                             glibc 2.3.2 and earlier) */
    int      si_fd;       /* File descriptor */
    short    si_addr_lsb; /* Least significant bit of address
                             (since kernel 2.6.32) */
}
```
sigaction() returns 0 on success and -1 on error.


## sigaddset
```c
#include <signal.h>
int sigaddset(sigset_t *set);
```
sigaddset() and sigdelset() add and delete respectively signal signum from set.
return 0 on success and -1 on error.

## sigemptyset
```c
#include <signal.h>
int sigemptyset(sigset_t *set);
```
sigemptyset() initializes the signal set given by set to empty, with all signals excluded from the set.
return 0 on success and -1 on error.