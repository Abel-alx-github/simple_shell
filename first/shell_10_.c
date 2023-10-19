#include "shell.h"

/**
 *inputbuf - buf chained commands
 * @bufer: address of buffer
 * @para: parameter struct
 * @len: address of len var
 * Return: bytes read
 */
ssize_t inputbuf(para_t *para, char **bufer, size_t *len)
{
	ssize_t re = 0;
	size_t len_p = 0;



	if (!*len)
	{
		free(*bufer);
		*bufer = NULL;
		signal(SIGINT, sigintHandler_);
#if USE_GETLINE
		re = getline(bufer, &len_p, stdin);
#else
		re = getline_(para, bufer, &len_p);
#endif
		if (re > 0)
		{
			if ((*bufer)[re - 1] == '\n')
			{
				(*bufer)[re - 1] = '\0';
				re--;
			}
			para->linecountflag = 1;
			removecomments(*bufer);
			buildhistorylist(para, *bufer, para->histcount++);
			{
				*len = re;
				para->cmdbuf = bufer;
			}
		}
	}
	return (re);
}

/**
 * getinput - reads an input rom user
 * @para: parameter struct
 * Return: bytes read
 */
ssize_t getinput(para_t *para)
{
	static char *bufer;
	static size_t i, j, len;
	ssize_t re = 0;
	char **buf_p = &(para->arg), *po;

	putcha_r(BUF_FLUSH);
	re = inputbuf(para, &bufer, &len);
	if (re == -1)
		return (-1);
	if (len)
	{
		j = i;
		po = bufer + i;

		checkchain(para, bufer, &j, i, len);
		while (j < len)
		{
			if (ischain(para, bufer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			para->cmdbuftype = CMD_NORM;
		}

		*buf_p = po;
		return (str_len(po));
	}

	*buf_p = bufer;
	return (re);
}

/**
 * readbuf - gets or reads a buffer
 * @bufer: buffer
 * @para: parameter struct
 * @i: size
 * Return: r
 */
ssize_t readbuf(para_t *para, char *bufer, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(para->read_fd, bufer, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 *getline_ - read the next line of input from STDIN
 * @para: parameter struct
 * @length: size of preallocated ptr buffer if not NULL
 * @ptr: address of pointer to buffer, preallocated or NULL
 * Return: s
 */
int getline_(para_t *para, char **ptr, size_t *length)
{
	static char bufer[READ_BUF_SIZE];
	static size_t i, len;
	size_t m;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = readbuf(para, bufer, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = str_chr(bufer + i, '\n');
	m = c ? 1 + (unsigned int)(c - bufer) : len;
	new_p = re_alloc(p, s, s ? s + m : m + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		strn_cat(new_p, bufer + i, m - i);
	else
		strn_cpy(new_p, bufer + i, m - i + 1);

	s += m - i;
	i = m;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}
