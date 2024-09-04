# .................. COLORS ...................................

_BOLD      =\e[1m

# RESET list
_R          =\e[0m

# Colors
_RED      =\e[91m
_GREEN    =\e[92m
_YELLOW   =\e[93m
_BLUE     =\e[94m
_MAGENTA  =\e[35m
_CYAN     =\e[96m
_WHITE    =\e[97m

NAME		= ircserv

# ................... CONTENT .................................
INCLUDES		=	./includes

SRC_DIR			=	./srcs
SRC				=	$(shell find $(SRC_DIR) -type d)
SRC_FILES		= 	main.cpp \
					Server.cpp \
					Client.cpp \
					Channel.cpp \
					tools.cpp \
					command_capls.cpp \
					command_nick.cpp \
					command_user.cpp \
					command_whois.cpp \
					command_pass.cpp \
					command_ping.cpp \
					command_join.cpp \
					command_privmsg.cpp \
					command_kick.cpp \
					command_topic.cpp \
					command_quit.cpp \
					command_oper.cpp \
					command_mode.cpp \
					command_invite.cpp \
					command_part.cpp

# ................... OBJECT ..................................

OBJ_DIR			= objs/
vpath %.cpp $(SRC)
OBJS			= $(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.o))
$(OBJ_DIR)%.o	: 	%.cpp $(INCLUDES)/ft_irc.hpp $(INCLUDES)/Client.hpp $(INCLUDES)/Defines.hpp $(INCLUDES)/Server.hpp $(INCLUDES)/Channel.hpp $(INCLUDES)/Commandes.hpp
					@mkdir -p $(OBJ_DIR)
					@$(CPP) $(CPP_FLAG) $(FLAGS) -c $< -o $@

# ................... COMPILER ................................

CPP				= c++
CPP_FLAG		= -std=c++98
FLAGS			= -Wall -Wextra -Werror -g3
$(NAME)			: $(OBJS)
					@$(CPP) $(CPP_FLAG) $(FLAGS) $(OBJS) -o $(NAME)
					@printf "$(_BOLD)$(_GREEN)................. Compilation success .................$(_R)\n\n"

all				: $(NAME)

clean			:
					@rm -rf $(OBJ_DIR)
					@printf "\n$(_MAGENTA)Removed : $(_WHITE)./$(OBJ_DIR)\n"

fclean			: clean
					@rm -f $(NAME)
					@printf "$(_MAGENTA)Removed : $(_WHITE)./$(NAME)\n"
					@printf "$(_GREEN)All is clean now !\n$(_R)"

re				: fclean
					@make all

.PHONY			= all clean fclean re
