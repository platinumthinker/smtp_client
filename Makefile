.PHONY: clean

smpt_client: *.c *.h
	gcc *.c -g -std=c99 -o smpt_client 

clean:
	rm -f smpt_client
