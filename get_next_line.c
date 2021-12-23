/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekim <jeekim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:33:45 by jeekim            #+#    #+#             */
/*   Updated: 2021/12/23 13:33:53 by jeekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*for_next(char *save)
{
	char	*temp;
	long	i;
	long	j;

	if (!save)
		return(NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	temp = (char *)malloc(sizeof(char) * (strlen(save) - i));
	if (!temp)
		return (NULL);
	j = 0;
	while (save[i + 1])
		temp[j++] = save[i++ + 1];
	temp[j] = 0;
	ft_strcpy(save, temp);
	free(temp);
	return (save);
}

char	*rtg(char *save) // 개행문자 뒤의 문자열 다 떼내고 바로 반환할수있게 만들어
//ready to go
{
	char	*temp;
	long	i;

	i = 0;
	if (!save)
		return (NULL);
	while (save[i] && save[i] != '\n')//개행문자+널문자까지 담을 공간 만들려고
		i++;
	temp = (char *)malloc(sizeof(char) * (i + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')//차곡차곡 넣어줘
	{
		temp[i] = save[i];
		i++;
	}//조건문에 i++넣어도 되는지 확인
	if (save[i] == '\n')//개행문자있으면
		temp[i] = save[i]; // 개행문자 넣어줘
	temp[i + 1] = 0;
	return (temp);
}//여기서 save 안건들임

char	*read_and_save(int fd, char *save)//파일내용 다 읽고 그 데이터를 저장한 문자열 반환
{
	char	*buf;//read함수로 B_S만큼 읽은걸 저장하는 공간.
	long	rd; //read함수 반환값. read함수로 읽은 바이트 수
//strchr 없으면 NULL 반환
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	rd = 1;//save에 개행이 있는지 없는지 무조건 검사를 시키려는것같아
	while (!(ft_strchr(save, '\n')) && rd != 0)//여기에서 개행문자 구분은 왜하는거지? 쨌든 개행문자가 없고 
//만약 파일에 널문자만 있다면 e 함수에따르면 save고대로 반환된다
	{
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd == -1)//읽는걸 실패했을때
		{
			free (buf);
			return (NULL);
		}
		buf[rd] = 0;
		save = ft_strjoin(save, buf);
	}//개행 문자 없으면 save에 파일내용 다 넣어
	free (buf);
	return (save);//개행문자 있으면 바로 반환. 개행문자가 포함된 문자열 반환. 개행문자 1개 포함한 문자열 반환해야하지. <-왜지
}

char	*get_next_line(int fd)
{
	static char	*save; //개행문자 다음 내용을 저장할 정적 공간
	char		*line;// 반환해야할 읽은 line

	if (fd < 0 || BUFFER_SIZE <= 0)//파일열기에 실패하거나
		//읽지 못할때
		return (NULL);//
	save = read_and_save(fd, save);
	if (!save)//에러났을때
		return (NULL);
	line = rtg(save);
	save = for_next(save);//개행문자 다음 문자열을 담아야해
	return (line);
}
