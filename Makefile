NAME = avm

SRC =	main \
		AbstractVM \
		Token \

INC = -I inc \

LDFLAGS = -pthread

VPATH = src
OBJ_DIR = obj
BIN_DIR = bin

OBJ = $(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(SRC)))
DEP = $(OBJ:%.o=%.d)

CC = g++
CFLAGS = $(INC)
MAKEOPTS = -j4

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@printf "\033[32mCreating : Object Directory\033[0m\n"
	@mkdir -p $(OBJ_DIR)

-include $(DEP)

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	@printf "\e[32mCompiling:\e[0m %s\n" $<
	@$(CC) $(CFLAGS) -MMD -c $< -o $@

$(NAME): $(OBJ)
	@printf "\e[32mCompiling:\e[0m %s\n" $(NAME)
	@$(CC) $^ -o $(BIN_DIR)/$@ $(LDFLAGS)

clean:
	@printf "\e[33mDeleting : Objects\e[0m\n"
	@rm -f $(OBJ)

fclean: clean
	@printf "\e[33mDeleting : %s\e[0m\n" $(NAME)
	@rm -f $(NAME)
	@printf "\e[33mDeleting : Object Directory\e[0m\n"
	@rm -rf $(OBJ_DIR)

re: fclean all

test: all
	@./$(BIN_DIR)/$(NAME) test_file.txt

.PHONY: all clean fclean re test