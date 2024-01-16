numToBits: numToBits.c
	gcc -o numToBits -pedantic -std=gnu99 -Wall -Werror numToBits.c
test: numToBits
	@diff <(./numToBits) ./bits_ans.txt || (echo "Test Failed"; exit 1)
	@echo "Success"
