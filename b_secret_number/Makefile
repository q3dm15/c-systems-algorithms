# Настройки компилятора и флагов
CC          := gcc
CFLAGS      := -Wall -Werror -Wextra -std=c17 -MMD -MP
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
	@echo "🚀 Running Tests..."
	@echo "-----------------------------------"
	@echo "Test 1 (Пример 1)"
	@echo "Input:"
	@echo "3\n21 35 28"
	@echo "Output:"
	@if echo "3\n21 35 28" | ./$(TARGET); then \
		echo "Status: ✅ DONE"; \
	else \
		echo "Status: ❌ FAILED"; \
	fi
	@echo "-----------------------------------"
	@echo "Test 2 (Пример 2)"
	@echo "Input:"
	@echo "4\n6 10 14 18"
	@echo "Output:"
	@if echo "4\n6 10 14 18" | ./$(TARGET); then \
		echo "Status: ✅ DONE"; \
	else \
		echo "Status: ❌ FAILED"; \
	fi
	@echo "-----------------------------------"


