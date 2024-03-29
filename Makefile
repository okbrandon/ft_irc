# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/12 17:45:22 by bsoubaig          #+#    #+#              #
#    Updated: 2024/03/11 18:00:40 by bsoubaig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors constants
PURPLE			= \033[38;5;141m
GREEN			= \033[38;5;46m
RED				= \033[0;31m
GREY			= \033[38;5;240m
RESET			= \033[0m
BOLD			= \033[1m
CLEAR			= \r\033[K

# Executable and compilation
NAME			= ircserv

SRC_DIR			= ./srcs/
SRCS			= entities/User.cpp \
				  entities/Server.cpp \
				  entities/Channel.cpp \
				  commands/ACommand.cpp \
				  commands/PassCommand.cpp \
				  commands/NickCommand.cpp \
				  commands/UserCommand.cpp \
				  commands/PingCommand.cpp \
				  commands/KickCommand.cpp \
				  commands/InviteCommand.cpp \
				  commands/TopicCommand.cpp \
				  commands/ModeCommand.cpp \
				  commands/CapCommand.cpp \
				  commands/JoinCommand.cpp \
				  commands/PrivmsgCommand.cpp \
				  commands/PartCommand.cpp \
				  commands/QuitCommand.cpp \
				  Executor.cpp \
				  IRCLogger.cpp \
				  Utils.cpp \
				  main.cpp \

OBJ_DIR			= ./objs/
OBJS			= ${addprefix ${OBJ_DIR}, ${SRCS:.cpp=.o}}

CC				= c++
CFLAGS			= -Wall -Wextra -Werror -std=c++98 -pedantic -ggdb3
RM				= rm -rf

# Checking OS type
UNAME_S := $(shell uname -s)

ifneq ($(UNAME_S),Linux)
ifneq ($(UNAME_S),Darwin)
	$(error Unsupported OS $(UNAME_S))
endif
endif

# Adding a specific flag for MacOS not Intel based
ifeq ($(UNAME_S),Darwin)
	CFLAGS += -arch x86_64
endif

# Debug compilation is launched
ifdef DEBUG
ifeq ($(UNAME_S),Linux)
	CFLAGS += -fsanitize=leak -g
endif
endif

# Compile with logs
ifdef WLOGS
	CFLAGS += -D LOGS=true
endif

${OBJ_DIR}%.o:	${SRC_DIR}%.cpp
	@printf "${CLEAR}${RESET}${GREEN}»${RESET} [${PURPLE}${BOLD}${NAME}${RESET}]: Compiling ${GREEN}%s${RESET}...${GREY}" ${notdir $<}
	@${CC} ${CFLAGS} -I${SRC_DIR} -c $< -o $@

all: 			$(NAME)

$(NAME): 		$(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@clear
	@printf "${CLEAR}${RESET}${GREY}────────────────────────────────────────────────────────────────────────────\n${RESET}${GREEN}»${RESET} [${PURPLE}${BOLD}${NAME}${RESET}]: ${RED}${BOLD}${NAME} ${RESET}compiled ${GREEN}successfully${RESET}.${GREY}\n${RESET}${GREY}────────────────────────────────────────────────────────────────────────────\n${RESET}"

${OBJS}:		| ${OBJ_DIR}

${OBJ_DIR}:
	@mkdir -p ${OBJ_DIR}/entities
	@mkdir -p ${OBJ_DIR}/commands

debug:
	@make DEBUG=1 re

logs:
	@make WLOGS=true re

clean:
	@${RM} ${OBJ_DIR}
	@printf "${CLEAR}${RESET}${GREEN}»${RESET} [${PURPLE}${BOLD}${NAME}${RESET}]: Objects were cleaned ${GREEN}successfully${RESET}.\n${RESET}"

fclean: 		clean
	@${RM} ${NAME}
	@printf "${CLEAR}${RESET}${GREY}────────────────────────────────────────────────────────────────────────────\n${RESET}${GREEN}»${RESET} [${PURPLE}${BOLD}${NAME}${RESET}]: Project cleaned ${GREEN}successfully${RESET}.${GREY}\n${RESET}${GREY}────────────────────────────────────────────────────────────────────────────\n${RESET}"

re: fclean all

.SILENT: all clean fclean re
.PHONY: all clean fclean re
