

if (isspace((unsigned char)buffer[0]))
			continue;

		if (buffer[0] == '\0' || buffer[0] == ' ')
			continue;
		execute_command(buffer, env);
	}
	if (path_variable)
	{
		printf("the PATH value: %s\n", path_variable);
		free(path_variable);
	}
	free(buffer);
	return (0);
