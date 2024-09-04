# ................... VARIABLES ................................

NAME        = ircserv

SRC_DIR     = ./srcs
INCLUDE_DIR = ./includes
OBJ_DIR     = ./objs

SRC_FILES   = main.cpp \
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

SRCS        = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS        = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.cpp=.o))

CPP         = c++
CPP_FLAGS   = -std=c++98 -Wall -Wextra -Werror -g3
INCLUDES    = -I$(INCLUDE_DIR)


$(NAME): $(OBJS)
	@$(CPP) $(CPP_FLAGS) $(OBJS) -o $(NAME)
	@echo "Compilation success!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@$(CPP) $(CPP_FLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

all: $(NAME)

clean:
	@rm -f $(OBJS)
	@echo "Object files removed."

fclean: clean
	@rm -f $(NAME)
	@echo "Executable removed."

re: fclean all

.PHONY: all clean fclean re
