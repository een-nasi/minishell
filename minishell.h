/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:                                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29                              #+#    #+#             */
/*   Updated: 2025/04/29                             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <limits.h>

# define STDIN_FILENO 0
# define STDOUT_FILENO 1
# define STDERR_FILENO 2

/**
 * @brief Structure pour stocker les variables d'environnement
 */
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/**
 * @brief Structure pour les redirections d'une commande
 */
typedef struct s_redir
{
	char			*file;
	int				type;
	struct s_redir	*next;
}	t_redir;

/**
 * @brief Structure pour représenter une commande
 */
typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	int				pipe_out;
	struct s_cmd	*next;
}	t_cmd;

/**
 * @brief Structure principale du shell
 */
typedef struct s_shell
{
	t_env			*env_list;
	t_cmd			*cmd_list;
	char			*input_line;
	int				exit_status;
	int				running;
}	t_shell;

/* Constantes pour les types de redirection */
# define REDIR_IN 1
# define REDIR_OUT 2
# define REDIR_APPEND 3
# define REDIR_HEREDOC 4

/* Prototypes des fonctions principales */
t_shell	*init_shell(char **envp);
void	free_shell(t_shell *shell);
int		parse_input(t_shell *shell);
int		execute_commands(t_shell *shell);

/* Prototypes des fonctions de gestion d'environnement */
t_env	*create_env_list(char **envp);
char	*get_env_value(t_env *env, char *key);
int		set_env_value(t_env *env, char *key, char *value);
void	free_env_list(t_env *env);

/* Prototypes des fonctions builtin */
int		cd_builtin(t_shell *shell, t_cmd *cmd);
int		echo_builtin(t_shell *shell, t_cmd *cmd);
int		env_builtin(t_shell *shell, t_cmd *cmd);
int		exit_builtin(t_shell *shell, t_cmd *cmd);
int		export_builtin(t_shell *shell, t_cmd *cmd);
int		pwd_builtin(t_shell *shell, t_cmd *cmd);
int		unset_builtin(t_shell *shell, t_cmd *cmd);

/* Fonctions utilitaires */
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);

#endif