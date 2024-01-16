reverse: reverse.c
	gcc -o reverse -pedantic -std=gnu99 -Wall -Werror reverse.c
test: reverse
	@diff <(./reverse) ./reverse_ans.txt || (echo "Test Failed"; exit 1)
	@echo "Success"
