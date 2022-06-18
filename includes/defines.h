/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:11:25 by user42            #+#    #+#             */
/*   Updated: 2022/06/18 16:07:50 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define BLANK 32
# define QUOTE 39
# define DB_QUOTE 34
# define PIPE 124
# define IN_REDIR 60
# define OUT_REDIR 62
# define HEREDOC 129
# define APPEND_REDIR 130
# define WORD 131
# define TO_EXPAND 132
# define INFILE_PATH 133
# define TRUNC_OUTFILE_PATH 134
# define DELIMITER 135
# define APPEND_OUTFILE_PATH 136
# define FILE_NOT_USED -42
# define FILE_OPEN_FAIL -1

#endif
