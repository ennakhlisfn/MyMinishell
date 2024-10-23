/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:39:56 by sennakhl          #+#    #+#             */
/*   Updated: 2024/09/02 18:22:11 by sennakhl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

extern int			g_status;

typedef struct s_free
{
	void			*elm;
	struct s_free	*next;
}					t_free;

typedef struct s_redi
{
	char			*dir;
	char			*file;
	int				co;
	int				exp;
	struct s_redi	*next;

}					t_redi;

typedef struct s_arg
{
	char			*arg;
	int				co;
	int				exp;
	struct s_arg	*next;
}					t_arg;

typedef struct s_ne
{
	t_arg			*en;
	t_arg			*expo;
	pid_t			lpi;
	int				n_here;
	int				prenth;
	int				he;
	int				stin;
	int				stout;
	int				to;
	int				p;
	int				nfd[2];
	int				ofd[2];
	int				fen;
	int				exi;
	int				inf;
	int				outf;
	int				status;
	int				l_here;
	int				ili;
	char			*cmpa;
	char			**env;
	char			**cm;
	char			*pa;
	char			*pwd;
	char			*oldpwd;
	char			*larc;
	char			**buf;
}					t_ne;

typedef struct s_list
{
	char			*token;
	t_arg			*args;
	t_redi			*redi;
	int				her;
	int				i;
	int				j;
	int				n_redi;
	struct s_list	*prt;
	struct s_list	*next;
}					t_list;

t_free				*ft_new_elm(void *elmt);
t_redi				*ft_new_redi(void);
t_arg				*ft_new_arg(void);
t_list				*ft_lstnew(void);

size_t				ft_strlen(const char *str);

void				endm(char *tmp, char *line, t_list *list, t_ne *l);
void				exfr(char *line, t_list *list, t_ne *l);
void				handle_sig(int s);
void				parent_sig(int s);
void				ge_line(char **line, t_ne *l, t_list *list);
void				general_redi(t_redi *redi, t_list *l, t_arg *new_args,
						t_ne *ne);
void				skip_qoat(char *line, int *j);
void				ft_free_args(t_arg *args);
void				ft_free_redi(t_redi *redi);
void				ft_free_list(t_list *list);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				init(t_ne *l, char **e);
void				f_env(t_ne *l);
void				f_pwd(t_ne *l);
void				f_cd(t_ne *l);
void				f_exit(t_ne *l);
void				f_echo(t_ne *l);
void				f_unse(t_ne *l);
void				f_expo(t_ne *l);
void				subshel(t_list *lst, t_ne *l);
void				getv(char **tem, char *st);
void				onecmd(t_list *lst, t_ne *l);
void				filcmd(t_list *lst, t_ne *l);
void				fpipe(t_list *lst, t_ne *l);
void				clof(t_ne *l);
void				clos(int *i);
void				wrerr(char *c, char *er, int s, t_ne *l);
void				conver(t_ne *l);
void				iniexpo(t_ne *l);
void				ft_free(char *str);
void				ftexec(t_list *lt, t_ne *l);
void				f_varscore(t_ne *l);
void				update(t_ne *l);
void				ft_frestr(char **str);
void				ft_frecmd(t_ne *l);
void				f_freex(t_ne *l);
void				f_dup(int *i, int s);
void				check_sig(int st, t_ne *l);
void				checkpwd(char *h, t_ne *l);
void				child_sig(int s);
void				gename(char **buf);
void				realbuf(char *name, t_ne *l);
void				expoadd(t_arg *e, char **tem);
void				subpipe(t_list *lst, t_ne *l);
void				check_pwd(char **tem, int p, t_ne *l);

char				*check_empty(char *s);
char				*ft_last_arg(t_list list);
char				*ft_itoa(int n);
char				*ft_separate(char *line, char sep);
char				*ft_strnjoin(char *s1, char *s2, size_t n);
char				*ft_memchr(char *s, char c);
char				*ft_strncopy(char *src, int n);
char				*ft_strdup(const char *s1);
char				*ft_strnstr(const char *str, const char *fd, size_t len);
char				*ft_strjoin(char const *s1, char *s2, int f);
char				*ft_getenv(char *str, t_ne *l);
char				**ft_split(char const *s, char c);
char				**fcreate(int s);
char				*generate(int co, char *lim, t_ne *l);
char				*checklin(char *line, t_ne *l);

int					check_logic(char *line, t_ne *l);
int					check_free(char **line, t_ne *l, t_list *list);
int					synt_prt(char *line);
int					last_pa(char *line, int j, t_list *list, t_ne *l);
int					check_white(char *line);
int					parenthes(t_list *list, char *line, t_ne *l);
int					main_expand(char *line, t_list *ls, t_arg **args, t_ne *l);
int					ft_redirection(char *line, t_ne *l, t_arg *args,
						t_list *list);
int					main_redi(t_redi *redi, t_list *l, t_ne *ne);
int					check_expand(char *line, t_list *list, t_arg **args,
						t_ne *l);
int					duble_qoat(char *line, t_arg *args, t_ne *l, int *k);
int					check_qoat(char *line, t_arg *args, int j, t_ne *l);
int					fill_args(char *line, t_arg *args, t_list *list, t_ne *l);
int					l_par(char *line);
int					first_skip(char *line, int *i, t_list *list, t_ne *l);
int					skip_parenthese(char *line, t_ne *l, int *j, int *s);
int					skip(char *line, t_ne *l);
int					unclosed(char *line, t_ne *l, int *j);
int					ft_expand_nsplit(char *line, t_arg *args, t_arg *en,
						t_ne *l);
int					ft_expand(char *line, t_arg *args, t_arg *en, t_ne *l);
int					fill_lst(char *line, t_list *list, t_ne *l);
int					parsing(char *line, t_list *list, t_ne *l);
int					syntax_error(t_ne *l);
int					ft_strncmp(char *s1, char *s2, int n);
int					ft_strcmp(char *s1, char *s2);
int					ft_lstsize(t_arg *lst);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_sizecm(t_arg *lst);
int					ft_atol(char *str, unsigned long *n);
int					ft_atoi(const char *str);
int					isvalid(char *st, t_ne *l);
int					check_builtin(t_ne *l);
int					oor(t_list *lst, t_ne *l);
int					oand(t_list *lst, t_ne *l);
int					addexpo(char *st, t_ne *l);
int					isexist(char *st, t_ne *l);
int					isther(char *st, char c);
int					checktem(char **tem, t_ne *l, int *p);
int					get_cmd(t_list *lst, t_ne *l);
int					nopa(char *a, char *path, t_ne *l);
int					parlen(char **par);
int					redire(t_list *lst, t_ne *l);
int					checksla(char *path, t_ne *l);
int					checkdir(t_ne *l, t_redi *head, int *err);
int					checkam(t_redi *head, t_ne *l, int *err);
int					check_char(char c);
int					check_pth(char **tem, t_ne *l, int *p);
int					check_export(char *line, t_list *list, t_arg **args,
						t_ne *l);
int					isdire(char *f);

#endif
