.PHONY: clean

smpt_client: *.c *.h
	gcc *.c -g -std=gnu99  -lcrypto -o smpt_client 

clean:
	rm -f smpt_client
