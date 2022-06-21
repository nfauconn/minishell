/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:11:25 by user42            #+#    #+#             */
/*   Updated: 2022/06/21 16:50:34 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/* PARSING */
# define BLANK 32
# define QUOTE 39
# define DB_QUOTE 34
# define PIPE 124
# define IN_REDIR 60
# define OUT_REDIR 62
# define HEREDOC 129
# define APPEND_REDIR 130
# define WORD 131
# define INFILE_PATH 133
# define TRUNC_OUTFILE_PATH 134
# define DELIMITER 135
# define APPEND_OUTFILE_PATH 136

/* REDIRECTIONS */
# define NO_REDIR -42
# define REDIR_FAIL -1

/* EXEC */
# define NOT_FOUND 127
# define NOT_EXECUTABLE 126
# define WRONG_REDIR 1
# define EMPTY_CMD 127

#endif
