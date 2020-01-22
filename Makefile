NAME = avm

SRC =	main \
		AbstractVM \
		Token \
		Operand \
		OperandFactory \
		util \
		exe \

INC = -I inc \

LDFLAGS = -pthread

VPATH = src
OBJ_DIR = obj
BIN_DIR = bin

OBJ = $(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(SRC)))
DEP = $(OBJ:%.o=%.d)

CC = g++
CFLAGS = -Wall -Wextra -Werror $(INC)
MAKEOPTS = -j4

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@printf "\033[32mCreating : Object Directory\033[0m\n"
	@mkdir -p $(OBJ_DIR)

-include $(DEP)

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	@printf "\033[32mCompiling:\033[0m %s\n" $<
	@$(CC) $(CFLAGS) -MMD -c $< -o $@

$(NAME): $(OBJ)
	@printf "\033[32mCompiling:\033[0m %s\n" $(NAME)
	@$(CC) $^ $(LDFLAGS) -o $(BIN_DIR)/$@

clean:
	@printf "\033[33mDeleting : Objects\033[0m\n"
	@rm -f $(OBJ) $(DEP)

fclean: clean
	@printf "\033[33mDeleting : %s\033[0m\n" $(NAME)
	@rm -f $(NAME)
	@printf "\033[33mDeleting : Object Directory\033[0m\n"
	@rm -rf $(OBJ_DIR)

re: fclean all

test: all
	@./$(BIN_DIR)/$(NAME) test_file.txt

.PHONY: all clean fclean re test