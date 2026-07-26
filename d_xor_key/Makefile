# Настройки компилятора и флагов
CC          := gcc
CFLAGS      := -Wall -Werror -Wextra -lm -O2 -fno-stack-limit -std=c23 -MMD -MP
# LDFLAGS — флаги для финальной сборки (сейчас тут пусто, но они разделены)
LDFLAGS     := 
VALGRIND_F  := --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1

# Имя конечного исполняемого файла
TARGET      := program

# Директории проекта
SRC_DIR     := src
OBJ_DIR     := obj

# Поиск всех исходных файлов .c в директории SRC_DIR
SRCS        := $(wildcard $(SRC_DIR)/*.c)
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS        := $(OBJS:.o=.d)

# Основные цели (интерфейс Makefile)
.PHONY: all clean rebuild cppcheck valgrind format-check format-fix

all: $(TARGET)

# Сборка исполняемого файла (теперь БЕЗ лишних флагов CFLAGS)
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

# Компиляция объектных файлов (здесь CFLAGS на своем месте)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Подключение файлов зависимостей (.d), чтобы реагировать на изменения в .h
-include $(DEPS)

# Очистка проекта
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Пересборка с нуля
rebuild: clean all

# Статический анализ кода
cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem $(SRC_DIR)/

# Проверка на утечки памяти (запуск вашей программы под Valgrind)
valgrind: rebuild
	valgrind $(VALGRIND_F) ./$(TARGET)

# Проверка стиля кода без изменения файлов
format-check:
	clang-format -n $(SRC_DIR)/*.c

# Автоматическое исправление стиля кода по правилам .clang-format
format-fix:
	clang-format -i $(SRC_DIR)/*.c
	
test: $(TARGET)
	@echo "🚀 Running Tests for Agent Decryptor..."
	@echo "-----------------------------------"
	@echo "📝 Test 1 (Примеры из задания)"
	@echo "📥 Input:"
	@printf "6 3\\nAGENT-HELLO\\n1274263c67591b762f3e7c4e73550606501c7346101741542156001d411020\\n1274263c67591b762f3e7c4e73561011521832470652471b7352071f5a1a\\n1274263c67591b762f3e7c4e73561b145a18274102065654275b06525715275201134011\\n"
	@echo "📤 Output:"
	@if printf "6 3\\nAGENT-HELLO\\n1274263c67591b762f3e7c4e73550606501c7346101741542156001d411020\\n1274263c67591b762f3e7c4e73561011521832470652471b7352071f5a1a\\n1274263c67591b762f3e7c4e73561b145a18274102065654275b06525715275201134011\\n" | ./$(TARGET); then \
		echo "\\n✅ Status: DONE"; \
	else \
		echo "\\n❌ Status: FAILED"; \
	fi
	@echo "-----------------------------------"
	@echo "📝 Test 2 (Примеры из задания)"
	@echo "📥 Input:"
	@printf "3 1\\nkey\\n0000005145180811101d040d0e4509190a0d0406160745170412\\n"
	@echo "📤 Output:"
	@if printf "3 1\\nkey\\n0000005145180811101d040d0e4509190a0d0406160745170412\\n" | ./$(TARGET); then \
		echo "\\n✅ Status: DONE"; \
	else \
		echo "\\n❌ Status: FAILED"; \
	fi
	@echo "-----------------------------------"
