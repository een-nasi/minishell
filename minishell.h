/* Structure pour représenter une commande */
typedef struct s_cmd
{
    char        **args;          // Tableau d'arguments (args[0] est la commande)
    char        *input_file;     // Redirection d'entrée (<)
    char        *output_file;    // Redirection de sortie (>)
    char        *append_file;    // Redirection en mode append (>>)
    char        *heredoc;        // Contenu du heredoc (<<)
    int         pipe_out;        // Si la commande a un pipe de sortie (|)
    struct s_cmd *next;          // Commande suivante dans le pipeline
} t_cmd;

/* Structure pour gérer l'environnement */
typedef struct s_env
{
    char        *key;            // Nom de la variable
    char        *value;          // Valeur de la variable
    struct s_env *next;          // Variable suivante
} t_env;

/* Structure principale du shell */
typedef struct s_shell
{
    t_env       *env_list;       // Liste chaînée des variables d'environnement
    t_cmd       *cmd_list;       // Liste des commandes à exécuter
    char        *input_line;     // Ligne de commande brute
    char        **tokens;        // Tokens après le parsing
    int         exit_status;     // Code de retour de la dernière commande
    int         running;         // Flag pour savoir si le shell tourne encore
    int         in_heredoc;      // Flag pour savoir si on est en mode heredoc
    pid_t       *child_pids;     // Tableau des PIDs des processus enfants
    int         child_count;     // Nombre de processus enfants actifs
} t_shell;

/* Structure pour le parsing et le lexer */
typedef struct s_token
{
    char        *value;          // Valeur du token
    int         type;            // Type de token (CMD, ARG, PIPE, REDIR, etc.)
    struct s_token *next;        // Token suivant
} t_token;

/* Structure pour les signaux */
typedef struct s_sig
{
    int         sigint;          // Ctrl+C
    int         sigquit;         // Ctrl+\
    int         sigtstp;         // Ctrl+Z
} t_sig;