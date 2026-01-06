/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 11:02:49 by gaeducas          #+#    #+#             */
/*   Updated: 2026/01/06 13:54:19 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int parse_map(char *filename, t_data *data)
{
    int     fd;
    char    *line;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (0); // Erreur d'ouverture

    data->map.height = 0;
    data->map.width = 0;

    line = get_next_line(fd);
    if (!line)
        return (0); // Fichier vide
    
    // On définit la largeur de référence avec la première ligne
    // Attention: GNL garde souvent le \n, pense à le gérer !
    data->map.width = ft_strlen(line) - 1; // -1 pour ignorer le \n
    
    while (line)
    {
        // Vérification rectangulaire
        if ((int)ft_strlen(line) - 1 != data->map.width && line[0] != '\n')
        {
            free(line);
            // close(fd) + free tout le reste...
            return (0); // Erreur: lignes de longueurs différentes
        }
        
        // Ici, idéalement, tu ajoutes la ligne dans data->map.grid
        // data->map.grid[data->map.height] = ft_strdup(line); (à faire avec un tableau dynamique)
        
        data->map.height++;
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (1);
}