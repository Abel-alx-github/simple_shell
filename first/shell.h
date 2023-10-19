#ifndef _SHELL_H_
#define _SHELL_H_
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#define READ_BUF_SIZE 1024
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define CMD_NORM	0
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

#define NULL_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}
extern char **environ;
typedef struct liststring
{
	int num;
	char *str;
	struct liststring *next;
} catalog_t;
typedef struct parameter
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int linecount;
	int errornum;
	int linecountflag;
	char *filename;
	catalog_t *env;
	catalog_t *history;
	catalog_t *alias;
	char **environ;
	int envchanged;
	int status;

	char **cmdbuf;
	int cmdbuftype; 
	int read_fd;
	int histcount;
} para_t;
typedef struct built_in
{
	char *type;
	int (*func)(para_t *);
} builtintable;

int sh(para_t *, char **);
int findbuiltin(para_t *);
void findcmd(para_t *);
void forkcmd(para_t *);
int iscmd(para_t *, char *);
char *dupchars(char *, int, int);
char *findpath(para_t *, char *, char *);

int loopsh(char **);

void e_puts(char *);
int e_putchar(char);
int put_fd(char c, int );
int puts_fd(char *str, int );

int str_len(char *);
int str_cmp(char *, char *);
char *startswith(const char *, const char *);
char *str_cat(char *, char *);

char *str_cpy(char *, char *);
char *str_dup(const char *);
void put_s(char *);
int putcha_r(char);

char *strn_cpy(char *, char *, int);
char *strn_cat(char *, char *, int);
char *str_chr(char *, char);

char **str_tow(char *, char *);
char **str_tow2(char *, char);

char *mem_set(char *, char, unsigned int);
void f_free(char **);
void *re_alloc(void *, unsigned int, unsigned int);

int b_free(void **);

int is_interactive(para_t *);
int isdelimter(char, char *);
int is_alpha(int);
int a_toi(char *);

void printerror(para_t *, char *);
int printd(int, int);
char *convertnumber(long int, int, int);
void removecomments(char *);
int exit_(para_t *);
int cd_(para_t *);
int help_(para_t *);
int history_(para_t *);
int alias_(para_t *);
ssize_t getinput(para_t *);
int getline_(para_t *, char **, size_t *);
void sigintHandler_(int);
void clear_para(para_t *);
void set_para(para_t *, char **);
void free_para(para_t *, int);
char *getenv_(para_t *, const char *);
int env_(para_t *);
int setenv_(para_t *);
int unsetenv_(para_t *);
int env_list(para_t *);
char **getenviron_(para_t *);
int unsetenv__(para_t *, char *);
int setenv__(para_t *, char *, char *);
char *gethistoryfile(para_t *para);
int writehistory(para_t *para);
int readhistory(para_t *para);
int erra_toi(char *);
int buildhistorylist(para_t *para, char *bufer, int linecount);
int renumberhistory(para_t *para);
catalog_t *addnode(catalog_t **, const char *, int);
catalog_t *addnodeend(catalog_t **, const char *, int);
size_t printliststr(const catalog_t *);
int deletenodeatindex(catalog_t **, unsigned int);
void freelist(catalog_t **);
size_t listlen(const catalog_t *);
char **listtostrings(catalog_t *);
size_t printlist(const catalog_t *);
catalog_t *nodestartswith(catalog_t *, char *, char);
ssize_t getnodeindex(catalog_t *, catalog_t *);
int ischain(para_t *, char *, size_t *);
void checkchain(para_t *, char *, size_t *, size_t, size_t);
int replacealias(para_t *);
int replacevars(para_t *);
int replacestring(char **, char *);
#endif
