#include <iostream>
#include "src/iris.h"
#include <signal.h>
#include <execinfo.h>

char *randstring(size_t length) {
  int n;
  static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
  char *randomString = NULL;
  if (length) {
    randomString = (char *) malloc(sizeof(char) * (length + 1));
    if (randomString) {
      for (n = 0; n < length; n++) {
        int key = rand() % (int) (sizeof(charset) - 1);
        randomString[n] = charset[key];
      }
      randomString[length] = '\0';
    }
  }
  return randomString;
}
/*
void bt_sighandler(int sig, struct sigcontext ctx) {

  void *trace[16];
  char **messages = (char **)NULL;
  int i, trace_size = 0;

  if (sig == SIGSEGV)
    printf("Got signal %d, faulty address is %p, "
                   "from %p\n", sig, ctx.cr2, ctx.eip);
  else
    printf("Got signal %d\n", sig);

  trace_size = backtrace(trace, 16);
  */
/* overwrite sigaction with caller's address *//*

  trace[1] = (void *)ctx.eip;
  messages = backtrace_symbols(trace, trace_size);
  */
/* skip first stack frame (points here) *//*

  printf("[bt] Execution path:\n");
  for (i=1; i<trace_size; ++i)
  {
    printf("[bt] #%d %s\n", i, messages[i]);

    */
/* find first occurence of '(' or ' ' in message[i] and assume
     * everything before that is the file name. (Don't go beyond 0 though
     * (string terminator)*//*

    size_t p = 0;
    while(messages[i][p] != '(' && messages[i][p] != ' '
          && messages[i][p] != 0)
      ++p;

    char syscom[256];
    sprintf(syscom,"addr2line %p -e %.*s", trace[i], p, messages[i]);
    //last parameter is the file name of the symbol
    system(syscom);
  }

  exit(0);
}
*/
int basic();
int firstTest();
int main(int argc, char *args[]) {
/*
  struct sigaction sa;
  sa.sa_handler = (void *)bt_sighandler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;

  sigaction(SIGSEGV, &sa, NULL);
*/
  std::cout << "Main" << std::endl;
  basic();
  return 0;
}
int firstTest(){
  FILE* fh;
  fh = iris::fopen("file0.dat", "w");
  iris::fclose(fh);
  return 0;
}
int basic(){
  char * write_buf;
  size_t op_size = 2*MAX_OBJ_SIZE;
  write_buf = randstring(op_size);
  char * read_buf = (char *)malloc(FILE_BUFFER_CAPACITY);
  size_t bytes_read=0;
  size_t bytes_written =0;

  FILE* fh;
  fh = iris::fopen("file0.dat", "w");
  iris::fwrite(write_buf, 1, 100, fh);
  iris::fread(read_buf, 1, 100, fh);
  iris::fclose(fh);

  return 0;
}
