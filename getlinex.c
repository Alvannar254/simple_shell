#include "mainx.h"

/**
 * bufft - buffers chained commands
 * @ifo: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */


getlt bufft(t_get *ifo, char **buf, xtsize *len)
{
	getlt r = 0;
	xtsize len_p = 0;

	if (!*len) 
	{
		
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);

#if USE_GETLINE
		r = getline(buf, &len_p, stdin);

#else
		r = _getline(ifo, buf, &len_p);

#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; 
				r--;
			}
			ifo->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(ifo, *buf, ifo->histcount++);
			
			{
				*len = r;
				ifo->cmd_buf = buf;
			}
		}
	}
	return (r);
}



/**
 * get_input - gets a line minus the newline
 *
 * Return: bytes read
 */


getlt get_input(t_get *ifo)
{
	static char *buf; 
	static xtsize i, j, len;
	getlt r = 0;
	char **buf_p = &(ifo->arg), *p;

	_putchar(BUF_FLUSH);
	r = bufft(ifo, &buf, &len);
	if (r == -1) 
		return (-1);
	if (len)	
	{
		j = i; 
		p = buf + i; 

		check_chain(ifo, buf, &j, i, len);
		while (j < len) 
		{
			if (is_chain(ifo, buf, &j))
				break;
			j++;
		}

		i = j + 1; 
		if (i >= len) 
		{
			i = len = 0; 
			ifo->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; 
		return (_strlen(p)); 
	}

	*buf_p = buf;
	return (r); 
}



/**
 * read_buf - reads a buffer
 * @ifo: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */


getlt read_buf(t_get *ifo, char *buf, xtsize *i)
{
	getlt r = 0;

	if (*i)
		return (0);
	r = read(ifo->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}



/**
 * _getline - gets the next line of input from STDIN
 * @ifo: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(t_get *ifo, char **ptr, xtsize *length)
{
	static char buf[READ_BUF_SIZE];
	static xtsize i, len;
	xtsize k;
	getlt r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(ifo, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) 
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}



/**
 * sigintHandler - blocks ctrl-C
 * @sig: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
