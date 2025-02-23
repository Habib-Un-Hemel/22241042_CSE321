#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msg {
    long int type;
    char txt[6];
};


int main()
{
	char buff[200];
	printf("Please enter the workspace name:\n");
    	scanf("%s", buff);
    	int msg_id = msgget((key_t)12, 0666|IPC_CREAT);
    	
    	
    	if (strcmp(buff, "cse321") == 0) 
    	{
		struct msg s_data;
		struct msg r_data;
		s_data.type = 2;
		strcpy(s_data.txt, buff);
		int snt = msgsnd(msg_id, (void *)&s_data, sizeof(s_data.txt), 0);
        	printf("Workspace name sent to OTP generator from login: %s\n", buff);
        	
        	pid_t pid = fork();
        	if (pid == 0)
        	{	
        		
        		pid_t c_pid = getpid();
        		int rcv = msgrcv(msg_id, (void*)&r_data, sizeof(r_data.txt), 2, IPC_NOWAIT);
           		 printf("OTP generator received workspace name from login: %s\n", r_data.txt);
            
			s_data.type = 3;
			snprintf(s_data.txt, sizeof(s_data.txt), "%d", c_pid);
			int snt = msgsnd(msg_id, (void *)&s_data, sizeof(s_data.txt), 0);
        		printf("OTP sent to login from OTP generator: %s\n", s_data.txt);
        	
        		struct msg s_data2, r_data2;
        		s_data2.type = 4;
			snprintf(s_data2.txt, sizeof(s_data2.txt), "%d", c_pid);
			int snt1 = msgsnd(msg_id, (void *)&s_data2, sizeof(s_data2.txt), 0);
        		printf("OTP sent to mail from OTP generator: %s\n", s_data2.txt);
        	
			pid_t pid2 = fork();
			if (pid2 == 0)
			{
				int rcv1 = msgrcv(msg_id, (void*)&r_data2, sizeof(r_data2.txt), 4, IPC_NOWAIT);
			    	printf("Mail received OTP from OTP generator: %s\n", r_data2.txt);
			    	
			    	
			    	struct msg s_data3;
				s_data3.type = 5;
				strcpy(s_data3.txt, r_data2.txt);
				int snt2 = msgsnd(msg_id, (void *)&s_data3, sizeof(s_data3.txt), 0);
				printf("OTP sent to log in from mail: %s\n", s_data3.txt);	
			}
        	
        	}
        	else
		{
			wait(NULL);
			int rcv = msgrcv(msg_id, (void*)&r_data, sizeof(r_data.txt), 3, IPC_NOWAIT);
		    	printf("Log in received OTP from OTP generator: %s\n", r_data.txt);
		    	
		    	struct msg r_data3;
		    	int rcv2 = msgrcv(msg_id, (void*)&r_data3, sizeof(r_data3.txt), 5, IPC_NOWAIT);
		    	printf("Log in received OTP from mail: %s\n", r_data3.txt);
		    	
		    	if (strcmp(r_data.txt , r_data3.txt) == 0)
		    	{
		    	printf("OTP Verified\n");	
		    	
		    	}
		    	else
		    	{
		    	
		    	printf("OTP Incorrect\n");
		    	}
		    	msgctl(msg_id,IPC_RMID,0);
        	
        	
        	}
        	
	}
	else
	{
		
		printf("Invalid workspace name\n");
	}

}

