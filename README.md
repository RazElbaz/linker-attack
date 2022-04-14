# linker-attack
Attack scanf in the following code to steal the password the user entered and send it to remote server


# Introduction:
We wrote the secret.c code in which we replaced the original scanf code and replaced it with our scanf code in order to steal the password that the user enters and print it on the TCP server we created with the address 127.0.0.1 (localhost).


## Tasks:
1. the hacked binary and libs

2. any extra sourcecode

    a) hacked library

    b) any extra server used - for example to receive the password

3. at least one screen shot of how it works

4. a short readme.txt explaining how to start it

5. any reasonable assumption (on ports, communication protocol (IPv4, IPv6, TCP, UDP etc.) is acceptable

6. for testing purposes - demonstrate connection to localhost (127.0.0.1)


##  Run:
1. make attack
2. make secret
3. make server
4. From another terminal run run_server
5. From a different terminal from the server terminal: readelf  -a secret | less 
   explain: For find the digger and the dynamic library in the dynamic section to know where they are and what their offset is 
6.   From another terminal run hexedit ./secret
    explain: Change their offset
7. We moved the libc.so.6 pointer from 1 to 5 to increase the 4-character pointer to leave only .so.6
8. Type in the terminal again readelf -a secret | less to see the changes
9. make run_secret
10. You can see the password that the user entered is printed on our server

## Pictures from the run:

1. ```make attack```
 
![alt text](https://github.com/RazElbaz/linker-attack/blob/main/Pictures%20from%20the%20run/make_attack.png)

2. ```make secret```

![alt text](https://github.com/RazElbaz/linker-attack/blob/main/Pictures%20from%20the%20run/make_secret.png)

3. ```make server```

![alt text](https://github.com/RazElbaz/linker-attack/blob/main/Pictures%20from%20the%20run/make_server.png)

4. ```make run_server```

![alt text](https://github.com/RazElbaz/linker-attack/blob/main/Pictures%20from%20the%20run/run_server.png)

5. ```readelf  -a secret | less```

![alt text](https://github.com/RazElbaz/linker-attack/blob/main/Pictures%20from%20the%20run/find_bit.png)

6. run hexedit ./secret: 


![alt text](https://github.com/RazElbaz/linker-attack/blob/main/Pictures%20from%20the%20run/befor.png)

7. Change their offset:


![alt text](https://github.com/RazElbaz/linker-attack/blob/main/Pictures%20from%20the%20run/after.png)

8. Type in the terminal again ```readelf -a secret | less``` to see the changes

![alt text](https://github.com/RazElbaz/linker-attack/blob/main/Pictures%20from%20the%20run/readelf_result.png)

9+10.   ```make run_secret``` and see the password that the user entered is printed on our server:

![alt text](https://github.com/RazElbaz/linker-attack/blob/main/Pictures%20from%20the%20run/end.png)


