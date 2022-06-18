/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:41:07 by user42            #+#    #+#             */
/*   Updated: 2022/06/18 19:20:08 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_input *input, t_sh *sh)
{
	token_expand(input->token_list, sh->env);
	complete_types(input->token_list);
	#ifdef DEBUG
	ft_lstiter(input->token_list, display_token_list);
	#endif

	token_to_cmd_lst(sh, input->token_list);
	return (SUCCESS);
}
