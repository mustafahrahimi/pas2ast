CC = gcc
CFLAGS = -Wall -std=c99 -g
TARGET = parser
SOURCES = driver.c keytoktab.c lexer.c optab.c parser.c symtab.c
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all clean test test-single test-all

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Test with a single file 
# (usage: make test-single FILE=TestSuite/testok1.pas)
test-single: $(TARGET)
	@if [ -z "$(FILE)" ]; then \
		echo "Usage: make test-single FILE=TestSuite/testok1.pas"; \
		exit 1; \
	fi
	@echo "Testing $(FILE)"
	@./$(TARGET) < $(FILE)

# Test with a specific file by name 
# (usage: make test TEST=testok1)
test: $(TARGET)
	@if [ -z "$(TEST)" ]; then \
		echo "Usage: make test TEST=testok1"; \
		exit 1; \
	fi
	@echo "Testing TestSuite/$(TEST).pas"
	@./$(TARGET) < TestSuite/$(TEST).pas

# Run all tests
test-all: $(TARGET)
	@echo "Running all tests..."
	@for i in TestSuite/*.pas; do \
		echo "=== Testing $$i ==="; \
		./$(TARGET) < $$i; \
		echo ""; \
	done

clean:
	@ rm -f $(OBJECTS) $(TARGET)
